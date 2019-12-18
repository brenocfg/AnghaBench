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
 int LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NULL_META ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_ucl_null_mt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_ucl_object_mt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_ucl_parser_init ; 
 int /*<<< orphan*/  lua_ucl_parser_mt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_ucl_to_config ; 
 int /*<<< orphan*/  lua_ucl_to_format ; 
 int /*<<< orphan*/  lua_ucl_to_json ; 
 int /*<<< orphan*/  ucl_null ; 

int
luaopen_ucl (lua_State *L)
{
	lua_ucl_parser_mt (L);
	lua_ucl_null_mt (L);
	lua_ucl_object_mt (L);

	/* Create the refs weak table: */
	lua_createtable (L, 0, 2);
	lua_pushliteral (L, "v"); /* tbl, "v" */
	lua_setfield (L, -2, "__mode");
	lua_pushvalue (L, -1); /* tbl, tbl */
	lua_setmetatable (L, -2); /* tbl */
	lua_setfield (L, LUA_REGISTRYINDEX, "ucl.refs");

	lua_newtable (L);

	lua_pushcfunction (L, lua_ucl_parser_init);
	lua_setfield (L, -2, "parser");

	lua_pushcfunction (L, lua_ucl_to_json);
	lua_setfield (L, -2, "to_json");

	lua_pushcfunction (L, lua_ucl_to_config);
	lua_setfield (L, -2, "to_config");

	lua_pushcfunction (L, lua_ucl_to_format);
	lua_setfield (L, -2, "to_format");

	ucl_null = lua_newuserdata (L, 0);
	luaL_getmetatable (L, NULL_META);
	lua_setmetatable (L, -2);

	lua_pushvalue (L, -1);
	lua_setfield (L, LUA_REGISTRYINDEX, "ucl.null");

	lua_setfield (L, -2, "null");

	return 1;
}