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
 int /*<<< orphan*/  OBJECT_META ; 
 int /*<<< orphan*/  luaL_newmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_ucl_object_gc ; 
 int /*<<< orphan*/  lua_ucl_object_tostring ; 
 int /*<<< orphan*/  lua_ucl_object_unwrap ; 
 int /*<<< orphan*/  lua_ucl_object_validate ; 

__attribute__((used)) static void
lua_ucl_object_mt (lua_State *L)
{
	luaL_newmetatable (L, OBJECT_META);

	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	lua_pushcfunction (L, lua_ucl_object_gc);
	lua_setfield (L, -2, "__gc");

	lua_pushcfunction (L, lua_ucl_object_tostring);
	lua_setfield (L, -2, "__tostring");

	lua_pushcfunction (L, lua_ucl_object_tostring);
	lua_setfield (L, -2, "tostring");

	lua_pushcfunction (L, lua_ucl_object_unwrap);
	lua_setfield (L, -2, "unwrap");

	lua_pushcfunction (L, lua_ucl_object_unwrap);
	lua_setfield (L, -2, "tolua");

	lua_pushcfunction (L, lua_ucl_object_validate);
	lua_setfield (L, -2, "validate");

	lua_pushstring (L, OBJECT_META);
	lua_setfield (L, -2, "class");

	lua_pop (L, 1);
}