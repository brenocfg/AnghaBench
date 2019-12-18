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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DATA_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/ *) ; 
 int zcp_nvpair_value_to_lua (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

int
zcp_nvlist_to_lua(lua_State *state, nvlist_t *nvl,
    char *errbuf, int errbuf_len)
{
	nvpair_t *pair;
	lua_newtable(state);
	boolean_t has_values = B_FALSE;
	/*
	 * If the list doesn't have any values, just convert it to a string
	 * array.
	 */
	for (pair = nvlist_next_nvpair(nvl, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(nvl, pair)) {
		if (nvpair_type(pair) != DATA_TYPE_BOOLEAN) {
			has_values = B_TRUE;
			break;
		}
	}
	if (!has_values) {
		int i = 1;
		for (pair = nvlist_next_nvpair(nvl, NULL);
		    pair != NULL; pair = nvlist_next_nvpair(nvl, pair)) {
			(void) lua_pushinteger(state, i);
			(void) lua_pushstring(state, nvpair_name(pair));
			(void) lua_settable(state, -3);
			i++;
		}
	} else {
		for (pair = nvlist_next_nvpair(nvl, NULL);
		    pair != NULL; pair = nvlist_next_nvpair(nvl, pair)) {
			int err = zcp_nvpair_value_to_lua(state, pair,
			    errbuf, errbuf_len);
			if (err != 0) {
				lua_pop(state, 1);
				return (err);
			}
			(void) lua_setfield(state, -2, nvpair_name(pair));
		}
	}
	return (0);
}