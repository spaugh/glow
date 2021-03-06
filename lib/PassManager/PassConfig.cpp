/**
 * Copyright (c) Glow Contributors. See CONTRIBUTORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "glow/PassManager/Pipeline.h"

using namespace glow;

static constexpr char const *tab = "  ";

void PassConfigBase::dump(llvm::raw_ostream &os,
                          llvm::StringRef passName) const {
  os << tab << "PassName: " << passName << ",\n";

  os << tab << "ConvergenceMode: ";
  switch (getConvergenceMode()) {
  case ConvergenceMode::OnePass:
    os << "OnePass,";
    break;
  case ConvergenceMode::UntilFixedPoint:
    os << "UntilFixedPoint,";
    break;
  }
  os << "\n";

  os << tab << "CompilationModes: {";
  if (isEnabledForCompilationMode(CompilationMode::Infer)) {
    os << "[Infer]";
  }
  if (isEnabledForCompilationMode(CompilationMode::Train)) {
    os << "[Train]";
  }
  os << "},\n";
}

bool PassConfigBase::equals(const PassConfigBase &other) const {
  return convergenceMode_ == other.convergenceMode_ &&
         enabledCompModes_ == other.enabledCompModes_ &&
         passID_ == other.passID_;
}
