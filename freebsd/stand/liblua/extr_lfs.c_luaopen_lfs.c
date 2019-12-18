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

/* Variables and functions */
 int /*<<< orphan*/  fslib ; 
 int /*<<< orphan*/  luaL_newlib (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_metatable (int /*<<< orphan*/ *) ; 

int
luaopen_lfs(lua_State *L)
{
	register_metatable(L);
	luaL_newlib(L, fslib);
	return 1;
}