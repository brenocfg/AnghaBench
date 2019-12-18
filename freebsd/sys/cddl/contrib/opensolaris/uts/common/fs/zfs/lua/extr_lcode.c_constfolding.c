#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int lua_Number ;
struct TYPE_6__ {int nval; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
typedef  TYPE_2__ expdesc ;
typedef  scalar_t__ OpCode ;

/* Variables and functions */
 int INT64_MIN ; 
 scalar_t__ LUA_OPADD ; 
 scalar_t__ OP_ADD ; 
 scalar_t__ OP_DIV ; 
 scalar_t__ OP_MOD ; 
 int /*<<< orphan*/  isnumeral (TYPE_2__*) ; 
 int luaO_arith (scalar_t__,int,int) ; 

__attribute__((used)) static int constfolding (OpCode op, expdesc *e1, expdesc *e2) {
  lua_Number r;
  if (!isnumeral(e1) || !isnumeral(e2)) return 0;
  if ((op == OP_DIV || op == OP_MOD) && e2->u.nval == 0)
    return 0;  /* do not attempt to divide by 0 */
  /*
   * Patched: check for MIN_INT / -1
   */
  if (op == OP_DIV && e1->u.nval == INT64_MIN && e2->u.nval == -1)
    return 0;
  r = luaO_arith(op - OP_ADD + LUA_OPADD, e1->u.nval, e2->u.nval);
  e1->u.nval = r;
  return 1;
}