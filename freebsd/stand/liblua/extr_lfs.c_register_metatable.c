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
 int /*<<< orphan*/  DIR_METATABLE ; 
 int /*<<< orphan*/  luaL_newmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_dir_iter_close ; 
 int /*<<< orphan*/  lua_dir_iter_next ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void
register_metatable(lua_State *L)
{
	/*
	 * Create so-called metatable for iterator object returned by
	 * lfs.dir().
	 */
	luaL_newmetatable(L, DIR_METATABLE);

	lua_newtable(L);
	lua_pushcfunction(L, lua_dir_iter_next);
	lua_setfield(L, -2, "next");
	lua_pushcfunction(L, lua_dir_iter_close);
	lua_setfield(L, -2, "close");

	/* Magically associate anonymous method table with metatable. */
	lua_setfield(L, -2, "__index");
	/* Implement magic destructor method */
	lua_pushcfunction(L, lua_dir_iter_close);
	lua_setfield(L, -2, "__gc");

	lua_pop(L, 1);
}