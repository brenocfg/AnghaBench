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
typedef  scalar_t__ zprop_type_t ;
typedef  int /*<<< orphan*/  zfs_prop_t ;
typedef  char uint64_t ;
typedef  int /*<<< orphan*/  numval ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 scalar_t__ PROP_TYPE_INDEX ; 
 scalar_t__ PROP_TYPE_STRING ; 
 int ZAP_MAXVALUELEN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int dsl_prop_get_ds (int /*<<< orphan*/ *,char const*,int,int,char*,char*) ; 
 int /*<<< orphan*/  get_prop_src (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_temporary_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 char* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ zfs_prop_get_type (int /*<<< orphan*/ ) ; 
 int zfs_prop_index_to_string (int /*<<< orphan*/ ,char,char const**) ; 
 char* zfs_prop_to_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_zap_prop(lua_State *state, dsl_dataset_t *ds, zfs_prop_t zfs_prop)
{
	int error = 0;
	char setpoint[ZFS_MAX_DATASET_NAME_LEN];
	char *strval = kmem_alloc(ZAP_MAXVALUELEN, KM_SLEEP);
	uint64_t numval;
	const char *prop_name = zfs_prop_to_name(zfs_prop);
	zprop_type_t prop_type = zfs_prop_get_type(zfs_prop);

	if (prop_type == PROP_TYPE_STRING) {
		/* Push value to lua stack */
		error = dsl_prop_get_ds(ds, prop_name, 1,
		    ZAP_MAXVALUELEN, strval, setpoint);
		if (error == 0)
			(void) lua_pushstring(state, strval);
	} else {
		error = dsl_prop_get_ds(ds, prop_name, sizeof (numval),
		    1, &numval, setpoint);

		/* Fill in temorary value for prop, if applicable */
		(void) get_temporary_prop(ds, zfs_prop, &numval, setpoint);

		/* Push value to lua stack */
		if (prop_type == PROP_TYPE_INDEX) {
			const char *propval;
			error = zfs_prop_index_to_string(zfs_prop, numval,
			    &propval);
			if (error == 0)
				(void) lua_pushstring(state, propval);
		} else {
			if (error == 0)
				(void) lua_pushnumber(state, numval);
		}
	}
	kmem_free(strval, ZAP_MAXVALUELEN);
	if (error == 0)
		get_prop_src(state, setpoint, zfs_prop);
	return (error);
}