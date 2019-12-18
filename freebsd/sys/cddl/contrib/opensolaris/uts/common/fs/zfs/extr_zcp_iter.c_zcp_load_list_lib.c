#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * gc; } ;
typedef  TYPE_1__ zcp_list_info_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_newmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ zcp_children_list_info ; 
 TYPE_1__ zcp_clones_list_info ; 
 int /*<<< orphan*/  zcp_list_func ; 
 TYPE_1__ zcp_props_list_info ; 
 TYPE_1__ zcp_snapshots_list_info ; 
 TYPE_1__ zcp_system_props_list_info ; 

int
zcp_load_list_lib(lua_State *state)
{
	int i;
	zcp_list_info_t *zcp_list_funcs[] = {
		&zcp_children_list_info,
		&zcp_snapshots_list_info,
		&zcp_props_list_info,
		&zcp_clones_list_info,
		&zcp_system_props_list_info,
		NULL
	};

	lua_newtable(state);

	for (i = 0; zcp_list_funcs[i] != NULL; i++) {
		zcp_list_info_t *info = zcp_list_funcs[i];

		if (info->gc != NULL) {
			/*
			 * If the function requires garbage collection, create
			 * a metatable with its name and register the __gc
			 * function.
			 */
			(void) luaL_newmetatable(state, info->name);
			(void) lua_pushstring(state, "__gc");
			lua_pushcfunction(state, info->gc);
			lua_settable(state, -3);
			lua_pop(state, 1);
		}

		lua_pushlightuserdata(state, info);
		lua_pushcclosure(state, &zcp_list_func, 1);
		lua_setfield(state, -2, info->name);
		info++;
	}

	return (1);
}