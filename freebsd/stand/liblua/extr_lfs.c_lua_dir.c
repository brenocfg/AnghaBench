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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_METATABLE ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_dir_iter_next ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 

__attribute__((used)) static int
lua_dir(lua_State *L)
{
	const char *path;
	DIR *dp;

	if (lua_gettop(L) != 1) {
		lua_pushnil(L);
		return 1;
	}

	path = luaL_checkstring(L, 1);
	dp = opendir(path);
	if (dp == NULL) {
		lua_pushnil(L);
		return 1;
	}

	lua_pushcfunction(L, lua_dir_iter_next);
	*(DIR **)lua_newuserdata(L, sizeof(DIR **)) = dp;
	luaL_getmetatable(L, DIR_METATABLE);
	lua_setmetatable(L, -2);
	return 2;
}