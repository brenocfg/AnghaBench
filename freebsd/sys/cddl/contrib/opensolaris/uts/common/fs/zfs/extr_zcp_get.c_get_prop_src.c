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
typedef  scalar_t__ zfs_prop_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ ZFS_PROP_VERSION ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ zfs_prop_readonly (scalar_t__) ; 

__attribute__((used)) static void
get_prop_src(lua_State *state, const char *setpoint, zfs_prop_t prop)
{
	if (zfs_prop_readonly(prop) || (prop == ZFS_PROP_VERSION)) {
		lua_pushnil(state);
	} else {
		const char *src;
		if (strcmp("", setpoint) == 0) {
			src = "default";
		} else {
			src = setpoint;
		}
		(void) lua_pushstring(state, src);
	}
}