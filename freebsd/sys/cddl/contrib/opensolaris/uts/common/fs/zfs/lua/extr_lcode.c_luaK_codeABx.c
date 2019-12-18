#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OpCode ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ABx (int /*<<< orphan*/ ,int,unsigned int) ; 
 int MAXARG_A ; 
 unsigned int MAXARG_Bx ; 
 scalar_t__ OpArgN ; 
 scalar_t__ getCMode (int /*<<< orphan*/ ) ; 
 scalar_t__ getOpMode (int /*<<< orphan*/ ) ; 
 scalar_t__ iABx ; 
 scalar_t__ iAsBx ; 
 int luaK_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

int luaK_codeABx (FuncState *fs, OpCode o, int a, unsigned int bc) {
  lua_assert(getOpMode(o) == iABx || getOpMode(o) == iAsBx);
  lua_assert(getCMode(o) == OpArgN);
  lua_assert(a <= MAXARG_A && bc <= MAXARG_Bx);
  return luaK_code(fs, CREATE_ABx(o, a, bc));
}