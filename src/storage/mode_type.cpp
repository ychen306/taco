#include <string>
#include <memory>
#include <vector>

#include "taco/storage/mode_type.h"
#include "taco/util/collections.h"
#include "taco/util/strings.h"

using namespace std;
using namespace taco::ir;

namespace taco {


Mode::Mode(const ir::Expr tensor, const size_t mode, const Dimension size,
           const ModePack* const pack, const size_t pos, 
           const ModeType prevModeType) :
    tensor(tensor), mode(mode), size(size), pack(pack), pos(pos), 
    prevModeType(prevModeType) {
}

std::string Mode::getName() const {
  return util::toString(tensor) + std::to_string(mode + 1);
}

ir::Expr Mode::getVar(const std::string varName) const {
  taco_iassert(hasVar(varName));
  return vars.at(varName);
}

bool Mode::hasVar(const std::string varName) const {
  return util::contains(vars, varName);
}

void Mode::addVar(const std::string varName, Expr var) {
  taco_iassert(isa<Var>(var));
  vars[varName] = var;
}


// class ModePack
size_t ModePack::getSize() const {
  taco_iassert(modes.size() == modeTypes.size());
  return modes.size();
}

Expr ModePack::getArray(size_t idx) const {
  for (size_t i = 0; i < getSize(); ++i) {
    const auto arr = modeTypes[i].impl->getArray(idx, modes[i]);
    if (arr.defined()) {
      return arr;
    }
  }
  return Expr();
}

// class ModeTypeImpl
ModeTypeImpl::ModeTypeImpl(const std::string name,
                           bool isFull, bool isOrdered, bool isUnique,
                           bool isBranchless, bool isCompact,
                           bool hasCoordValIter, bool hasCoordPosIter,
                           bool hasLocate, bool hasInsert, bool hasAppend) :
    name(name), isFull(isFull), isOrdered(isOrdered),
    isUnique(isUnique), isBranchless(isBranchless), isCompact(isCompact), 
    hasCoordValIter(hasCoordValIter), hasCoordPosIter(hasCoordPosIter), 
    hasLocate(hasLocate), hasInsert(hasInsert), hasAppend(hasAppend) {
}

std::tuple<Stmt,Expr,Expr> ModeTypeImpl::getCoordIter(
    const std::vector<Expr>& i, Mode& mode) const {
  return std::tuple<Stmt,Expr,Expr>(Stmt(), Expr(), Expr());
}

std::tuple<Stmt,Expr,Expr> ModeTypeImpl::getCoordAccess(const Expr& pPrev, 
    const std::vector<Expr>& i, Mode& mode) const {
  return std::tuple<Stmt,Expr,Expr>(Stmt(), Expr(), Expr());
}

std::tuple<Stmt,Expr,Expr> ModeTypeImpl::getPosIter(const Expr& pPrev, 
    Mode& mode) const {
  return std::tuple<Stmt,Expr,Expr>(Stmt(), Expr(), Expr());
}

std::tuple<Stmt,Expr,Expr> ModeTypeImpl::getPosAccess(const Expr& p, 
    const std::vector<Expr>& i, Mode& mode) const {
  return std::tuple<Stmt,Expr,Expr>(Stmt(), Expr(), Expr());
}

std::tuple<Stmt,Expr,Expr> ModeTypeImpl::getLocate(const Expr& pPrev, 
    const std::vector<Expr>& i, Mode& mode) const {
  return std::tuple<Stmt,Expr,Expr>(Stmt(), Expr(), Expr());
}
  
Stmt ModeTypeImpl::getInsertCoord(const ir::Expr& p, 
    const std::vector<ir::Expr>& i, Mode& mode) const {
  return Stmt();
}

Expr ModeTypeImpl::getSize(Mode& mode) const {
  return Expr();
}

Stmt ModeTypeImpl::getInsertInitCoords(const ir::Expr& pBegin, 
    const ir::Expr& pEnd, Mode& mode) const {
  return Stmt();
}

Stmt ModeTypeImpl::getInsertInitLevel(const ir::Expr& szPrev, 
    const ir::Expr& sz, Mode& mode) const {
  return Stmt();
}

Stmt ModeTypeImpl::getInsertFinalizeLevel(const ir::Expr& szPrev, 
    const ir::Expr& sz, Mode& mode) const {
  return Stmt();
}

Stmt ModeTypeImpl::getAppendCoord(const ir::Expr& p, const ir::Expr& i, 
    Mode& mode) const {
  return Stmt();
}

Stmt ModeTypeImpl::getAppendEdges(const ir::Expr& pPrev, const ir::Expr& pBegin, 
    const ir::Expr& pEnd, Mode& mode) const {
  return Stmt();
}

Stmt ModeTypeImpl::getAppendInitEdges(const ir::Expr& pPrevBegin, 
    const ir::Expr& pPrevEnd, Mode& mode) const {
  return Stmt();
}

Stmt ModeTypeImpl::getAppendInitLevel(const ir::Expr& szPrev, 
    const ir::Expr& sz, Mode& mode) const {
  return Stmt();
}

Stmt ModeTypeImpl::getAppendFinalizeLevel(const ir::Expr& szPrev, 
    const ir::Expr& sz, Mode& mode) const {
  return Stmt();
}

}

