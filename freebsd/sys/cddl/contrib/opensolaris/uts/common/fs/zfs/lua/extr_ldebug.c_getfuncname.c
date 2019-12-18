#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int /*<<< orphan*/ * tmname; } ;
struct TYPE_6__ {TYPE_1__* p; } ;
struct TYPE_5__ {int /*<<< orphan*/ * code; } ;
typedef  size_t TMS ;
typedef  TYPE_1__ Proto ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  int /*<<< orphan*/  CallInfo ;

/* Variables and functions */
 TYPE_4__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GETARG_A (int /*<<< orphan*/ ) ; 
 int GET_OPCODE (int /*<<< orphan*/ ) ; 
#define  OP_ADD 147 
#define  OP_CALL 146 
#define  OP_CONCAT 145 
#define  OP_DIV 144 
#define  OP_EQ 143 
#define  OP_GETTABLE 142 
#define  OP_GETTABUP 141 
#define  OP_LE 140 
#define  OP_LEN 139 
#define  OP_LT 138 
#define  OP_MOD 137 
#define  OP_MUL 136 
#define  OP_POW 135 
#define  OP_SELF 134 
#define  OP_SETTABLE 133 
#define  OP_SETTABUP 132 
#define  OP_SUB 131 
#define  OP_TAILCALL 130 
#define  OP_TFORCALL 129 
#define  OP_UNM 128 
 size_t TM_ADD ; 
 size_t TM_CONCAT ; 
 size_t TM_DIV ; 
 size_t TM_EQ ; 
 size_t TM_INDEX ; 
 size_t TM_LE ; 
 size_t TM_LEN ; 
 size_t TM_LT ; 
 size_t TM_MOD ; 
 size_t TM_MUL ; 
 size_t TM_NEWINDEX ; 
 size_t TM_POW ; 
 size_t TM_SUB ; 
 size_t TM_UNM ; 
 TYPE_3__* ci_func (int /*<<< orphan*/ *) ; 
 int currentpc (int /*<<< orphan*/ *) ; 
 char const* getobjname (TYPE_1__*,int,int /*<<< orphan*/ ,char const**) ; 
 char* getstr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *getfuncname (lua_State *L, CallInfo *ci, const char **name) {
  TMS tm;
  Proto *p = ci_func(ci)->p;  /* calling function */
  int pc = currentpc(ci);  /* calling instruction index */
  Instruction i = p->code[pc];  /* calling instruction */
  switch (GET_OPCODE(i)) {
    case OP_CALL:
    case OP_TAILCALL:  /* get function name */
      return getobjname(p, pc, GETARG_A(i), name);
    case OP_TFORCALL: {  /* for iterator */
      *name = "for iterator";
       return "for iterator";
    }
    /* all other instructions can call only through metamethods */
    case OP_SELF:
    case OP_GETTABUP:
    case OP_GETTABLE: tm = TM_INDEX; break;
    case OP_SETTABUP:
    case OP_SETTABLE: tm = TM_NEWINDEX; break;
    case OP_EQ: tm = TM_EQ; break;
    case OP_ADD: tm = TM_ADD; break;
    case OP_SUB: tm = TM_SUB; break;
    case OP_MUL: tm = TM_MUL; break;
    case OP_DIV: tm = TM_DIV; break;
    case OP_MOD: tm = TM_MOD; break;
    case OP_POW: tm = TM_POW; break;
    case OP_UNM: tm = TM_UNM; break;
    case OP_LEN: tm = TM_LEN; break;
    case OP_LT: tm = TM_LT; break;
    case OP_LE: tm = TM_LE; break;
    case OP_CONCAT: tm = TM_CONCAT; break;
    default:
      return NULL;  /* else no useful name can be found */
  }
  *name = getstr(G(L)->tmname[tm]);
  return "metamethod";
}