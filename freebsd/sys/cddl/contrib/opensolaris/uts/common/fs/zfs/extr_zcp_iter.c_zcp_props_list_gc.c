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
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
zcp_props_list_gc(lua_State *state)
{
	nvlist_t **props = lua_touserdata(state, 1);
	if (*props != NULL)
		fnvlist_free(*props);
	return (0);
}