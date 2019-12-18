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
 int /*<<< orphan*/  LUA_PATH ; 
 int /*<<< orphan*/  MACHINE ; 
 int /*<<< orphan*/  MACHINE_ARCH ; 
 int /*<<< orphan*/  loaderlib ; 
 int /*<<< orphan*/  luaL_newlib (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_printc ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 

int
luaopen_loader(lua_State *L)
{
	luaL_newlib(L, loaderlib);
	/* Add loader.machine and loader.machine_arch properties */
	lua_pushstring(L, MACHINE);
	lua_setfield(L, -2, "machine");
	lua_pushstring(L, MACHINE_ARCH);
	lua_setfield(L, -2, "machine_arch");
	lua_pushstring(L, LUA_PATH);
	lua_setfield(L, -2, "lua_path");
	/* Set global printc to loader.printc */
	lua_register(L, "printc", lua_printc);
	return 1;
}