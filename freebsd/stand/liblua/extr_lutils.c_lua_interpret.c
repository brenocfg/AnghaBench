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
 int /*<<< orphan*/  interp_run (char const*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lua_interpret(lua_State *L)
{
	const char	*interp_string;

	if (lua_gettop(L) != 1) {
		lua_pushnil(L);
		return 1;
	}

	interp_string = luaL_checkstring(L, 1);
	lua_pushinteger(L, interp_run(interp_string));
	return 1;
}