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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zcp_lua_to_nvlist (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
zcp_lua_to_nvlist_helper(lua_State *state)
{
	nvlist_t *nv = (nvlist_t *)lua_touserdata(state, 2);
	const char *key = (const char *)lua_touserdata(state, 1);
	zcp_lua_to_nvlist(state, 3, nv, key);
	return (0);
}