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
 int /*<<< orphan*/  PARSER_META ; 
 int /*<<< orphan*/  luaL_newmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_ucl_parser_gc ; 
 int /*<<< orphan*/  lua_ucl_parser_get_object ; 
 int /*<<< orphan*/  lua_ucl_parser_get_object_wrapped ; 
 int /*<<< orphan*/  lua_ucl_parser_parse_file ; 
 int /*<<< orphan*/  lua_ucl_parser_parse_string ; 
 int /*<<< orphan*/  lua_ucl_parser_validate ; 

__attribute__((used)) static void
lua_ucl_parser_mt (lua_State *L)
{
	luaL_newmetatable (L, PARSER_META);

	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	lua_pushcfunction (L, lua_ucl_parser_gc);
	lua_setfield (L, -2, "__gc");

	lua_pushcfunction (L, lua_ucl_parser_parse_file);
	lua_setfield (L, -2, "parse_file");

	lua_pushcfunction (L, lua_ucl_parser_parse_string);
	lua_setfield (L, -2, "parse_string");

	lua_pushcfunction (L, lua_ucl_parser_get_object);
	lua_setfield (L, -2, "get_object");

	lua_pushcfunction (L, lua_ucl_parser_get_object_wrapped);
	lua_setfield (L, -2, "get_object_wrapped");

	lua_pushcfunction (L, lua_ucl_parser_validate);
	lua_setfield (L, -2, "validate");

	lua_pop (L, 1);
}