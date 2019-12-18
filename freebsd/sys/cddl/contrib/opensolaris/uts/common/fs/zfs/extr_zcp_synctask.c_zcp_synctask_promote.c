#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  zri_cred; } ;
typedef  TYPE_1__ zcp_run_info_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {char const* ddpa_clonename; int /*<<< orphan*/  cr; int /*<<< orphan*/ * err_ds; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ dsl_dataset_promote_arg_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  dsl_dataset_promote_check ; 
 int /*<<< orphan*/  dsl_dataset_promote_sync ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* zcp_run_info (int /*<<< orphan*/ *) ; 
 int zcp_sync_task (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
zcp_synctask_promote(lua_State *state, boolean_t sync, nvlist_t *err_details)
{
	int err;
	dsl_dataset_promote_arg_t ddpa = { 0 };
	const char *dsname = lua_tostring(state, 1);
	zcp_run_info_t *ri = zcp_run_info(state);

	ddpa.ddpa_clonename = dsname;
	ddpa.err_ds = err_details;
	ddpa.cr = ri->zri_cred;

	/*
	 * If there was a snapshot name conflict, then err_ds will be filled
	 * with a list of conflicting snapshot names.
	 */
	err = zcp_sync_task(state, dsl_dataset_promote_check,
	    dsl_dataset_promote_sync, &ddpa, sync, dsname);

	return (err);
}