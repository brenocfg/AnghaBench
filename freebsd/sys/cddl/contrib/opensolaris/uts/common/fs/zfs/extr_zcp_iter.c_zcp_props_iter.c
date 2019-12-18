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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  ZPROP_SOURCE ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 char* fnvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvpair_value_nvlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_prop_user (char*) ; 

__attribute__((used)) static int
zcp_props_iter(lua_State *state)
{
	char *source, *val;
	nvlist_t *nvprop;
	nvlist_t **props = lua_touserdata(state, lua_upvalueindex(1));
	nvpair_t *pair = lua_touserdata(state, lua_upvalueindex(2));

	do {
		pair = nvlist_next_nvpair(*props, pair);
		if (pair == NULL) {
			fnvlist_free(*props);
			*props = NULL;
			return (0);
		}
	} while (!zfs_prop_user(nvpair_name(pair)));

	lua_pushlightuserdata(state, pair);
	lua_replace(state, lua_upvalueindex(2));

	nvprop = fnvpair_value_nvlist(pair);
	val = fnvlist_lookup_string(nvprop, ZPROP_VALUE);
	source = fnvlist_lookup_string(nvprop, ZPROP_SOURCE);

	(void) lua_pushstring(state, nvpair_name(pair));
	(void) lua_pushstring(state, val);
	(void) lua_pushstring(state, source);
	return (3);
}