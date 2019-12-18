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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  b_uint ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkunsigned (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trim (int /*<<< orphan*/ ) ; 

__attribute__((used)) static b_uint andaux (lua_State *L) {
  int i, n = lua_gettop(L);
  b_uint r = ~(b_uint)0;
  for (i = 1; i <= n; i++)
    r &= luaL_checkunsigned(L, i);
  return trim(r);
}