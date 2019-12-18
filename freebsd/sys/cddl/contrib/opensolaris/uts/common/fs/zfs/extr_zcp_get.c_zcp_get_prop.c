#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zfs_prop_t ;
struct TYPE_4__ {int /*<<< orphan*/  kwargs; int /*<<< orphan*/  pargs; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zcp_lib_info_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/ * zri_pool; } ;

/* Variables and functions */
 scalar_t__ ZPROP_INVAL ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ zcp_get_prop_info ; 
 int zcp_get_system_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int zcp_get_user_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*) ; 
 int zcp_get_userquota_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*) ; 
 int zcp_get_written_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  zcp_parse_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* zcp_run_info (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_name_to_prop (char const*) ; 
 scalar_t__ zfs_prop_user (char const*) ; 
 scalar_t__ zfs_prop_userquota (char const*) ; 
 scalar_t__ zfs_prop_written (char const*) ; 

__attribute__((used)) static int
zcp_get_prop(lua_State *state)
{
	const char *dataset_name;
	const char *property_name;
	dsl_pool_t *dp = zcp_run_info(state)->zri_pool;
	zcp_lib_info_t *libinfo = &zcp_get_prop_info;

	zcp_parse_args(state, libinfo->name, libinfo->pargs, libinfo->kwargs);

	dataset_name = lua_tostring(state, 1);
	property_name = lua_tostring(state, 2);

	/* User defined property */
	if (zfs_prop_user(property_name)) {
		return (zcp_get_user_prop(state, dp,
		    dataset_name, property_name));
	}
	/* userspace property */
	if (zfs_prop_userquota(property_name)) {
#ifdef _KERNEL
		return (zcp_get_userquota_prop(state, dp,
		    dataset_name, property_name));
#else
		return (luaL_error(state,
		    "user quota properties only supported in kernel mode",
		    property_name));
#endif
	}
	/* written@ property */
	if (zfs_prop_written(property_name)) {
		return (zcp_get_written_prop(state, dp,
		    dataset_name, property_name));
	}

	zfs_prop_t zfs_prop = zfs_name_to_prop(property_name);
	/* Valid system property */
	if (zfs_prop != ZPROP_INVAL) {
		return (zcp_get_system_prop(state, dp, dataset_name,
		    zfs_prop));
	}

	/* Invalid property name */
	return (luaL_error(state,
	    "'%s' is not a valid property", property_name));
}