#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  info; } ;
struct TYPE_17__ {TYPE_1__ u; int /*<<< orphan*/  k; int /*<<< orphan*/  t; int /*<<< orphan*/  f; } ;
typedef  TYPE_2__ expdesc ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  int BinOpr ;

/* Variables and functions */
 int /*<<< orphan*/  GETARG_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_OPCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_OPADD ; 
 int /*<<< orphan*/  NO_JUMP ; 
#define  OPR_ADD 148 
#define  OPR_AND 147 
#define  OPR_BAND 146 
#define  OPR_BOR 145 
#define  OPR_BXOR 144 
#define  OPR_CONCAT 143 
#define  OPR_DIV 142 
#define  OPR_EQ 141 
#define  OPR_GE 140 
#define  OPR_GT 139 
#define  OPR_IDIV 138 
#define  OPR_LE 137 
#define  OPR_LT 136 
#define  OPR_MOD 135 
#define  OPR_MUL 134 
#define  OPR_NE 133 
#define  OPR_OR 132 
#define  OPR_POW 131 
#define  OPR_SHL 130 
#define  OPR_SHR 129 
#define  OPR_SUB 128 
 int /*<<< orphan*/  OP_ADD ; 
 int /*<<< orphan*/  OP_CONCAT ; 
 int /*<<< orphan*/  OpCode ; 
 int /*<<< orphan*/  SETARG_B (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VRELOCABLE ; 
 int /*<<< orphan*/  cast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codebinexpval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  codecomp (int /*<<< orphan*/ *,int,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  constfolding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  freeexp (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  getinstruction (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_dischargevars (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_exp2nextreg (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_exp2val (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

void luaK_posfix (FuncState *fs, BinOpr op,
                  expdesc *e1, expdesc *e2, int line) {
  switch (op) {
    case OPR_AND: {
      lua_assert(e1->t == NO_JUMP);  /* list closed by 'luK_infix' */
      luaK_dischargevars(fs, e2);
      luaK_concat(fs, &e2->f, e1->f);
      *e1 = *e2;
      break;
    }
    case OPR_OR: {
      lua_assert(e1->f == NO_JUMP);  /* list closed by 'luK_infix' */
      luaK_dischargevars(fs, e2);
      luaK_concat(fs, &e2->t, e1->t);
      *e1 = *e2;
      break;
    }
    case OPR_CONCAT: {
      luaK_exp2val(fs, e2);
      if (e2->k == VRELOCABLE &&
          GET_OPCODE(getinstruction(fs, e2)) == OP_CONCAT) {
        lua_assert(e1->u.info == GETARG_B(getinstruction(fs, e2))-1);
        freeexp(fs, e1);
        SETARG_B(getinstruction(fs, e2), e1->u.info);
        e1->k = VRELOCABLE; e1->u.info = e2->u.info;
      }
      else {
        luaK_exp2nextreg(fs, e2);  /* operand must be on the 'stack' */
        codebinexpval(fs, OP_CONCAT, e1, e2, line);
      }
      break;
    }
    case OPR_ADD: case OPR_SUB: case OPR_MUL: case OPR_DIV:
    case OPR_IDIV: case OPR_MOD: case OPR_POW:
    case OPR_BAND: case OPR_BOR: case OPR_BXOR:
    case OPR_SHL: case OPR_SHR: {
      if (!constfolding(fs, op + LUA_OPADD, e1, e2))
        codebinexpval(fs, cast(OpCode, op + OP_ADD), e1, e2, line);
      break;
    }
    case OPR_EQ: case OPR_LT: case OPR_LE:
    case OPR_NE: case OPR_GT: case OPR_GE: {
      codecomp(fs, op, e1, e2);
      break;
    }
    default: lua_assert(0);
  }
}