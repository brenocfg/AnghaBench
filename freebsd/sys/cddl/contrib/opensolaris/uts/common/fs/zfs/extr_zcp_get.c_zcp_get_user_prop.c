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
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  ZAP_MAXVALUELEN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_prop_get_ds (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,char*,char*) ; 
 char* kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * zcp_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int zcp_handle_error (int /*<<< orphan*/ *,char const*,char const*,int) ; 

__attribute__((used)) static int
zcp_get_user_prop(lua_State *state, dsl_pool_t *dp, const char *dataset_name,
    const char *property_name)
{
	int error;
	char *buf;
	char setpoint[ZFS_MAX_DATASET_NAME_LEN];
	/*
	 * zcp_dataset_hold will either successfully return the requested
	 * dataset or throw a lua error and longjmp out of the zfs.get_prop call
	 * without returning.
	 */
	dsl_dataset_t *ds = zcp_dataset_hold(state, dp, dataset_name, FTAG);
	if (ds == NULL)
		return (1); /* not reached; zcp_dataset_hold() longjmp'd */

	buf = kmem_alloc(ZAP_MAXVALUELEN, KM_SLEEP);
	error = dsl_prop_get_ds(ds, property_name, 1, ZAP_MAXVALUELEN,
	    buf, setpoint);
	dsl_dataset_rele(ds, FTAG);

	if (error != 0) {
		kmem_free(buf, ZAP_MAXVALUELEN);
		return (zcp_handle_error(state, dataset_name, property_name,
		    error));
	}
	(void) lua_pushstring(state, buf);
	(void) lua_pushstring(state, setpoint);
	kmem_free(buf, ZAP_MAXVALUELEN);
	return (2);
}