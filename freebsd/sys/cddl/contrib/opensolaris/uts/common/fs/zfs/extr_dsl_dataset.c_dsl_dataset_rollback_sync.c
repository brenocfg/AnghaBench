#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_10__ {int /*<<< orphan*/  ds_prev; int /*<<< orphan*/  ds_dir; } ;
typedef  TYPE_1__ dsl_dataset_t ;
struct TYPE_11__ {int /*<<< orphan*/  ddra_result; int /*<<< orphan*/  ddra_fsname; } ;
typedef  TYPE_2__ dsl_dataset_rollback_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS_CREATE_FLAG_NODIRTY ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/ * dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_clone_swap_sync_impl (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_create_sync (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dsl_dataset_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_zero_zil (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_destroy_head_sync_impl (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  kcred ; 

void
dsl_dataset_rollback_sync(void *arg, dmu_tx_t *tx)
{
	dsl_dataset_rollback_arg_t *ddra = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *ds, *clone;
	uint64_t cloneobj;
	char namebuf[ZFS_MAX_DATASET_NAME_LEN];

	VERIFY0(dsl_dataset_hold(dp, ddra->ddra_fsname, FTAG, &ds));

	dsl_dataset_name(ds->ds_prev, namebuf);
	fnvlist_add_string(ddra->ddra_result, "target", namebuf);

	cloneobj = dsl_dataset_create_sync(ds->ds_dir, "%rollback",
	    ds->ds_prev, DS_CREATE_FLAG_NODIRTY, kcred, tx);

	VERIFY0(dsl_dataset_hold_obj(dp, cloneobj, FTAG, &clone));

	dsl_dataset_clone_swap_sync_impl(clone, ds, tx);
	dsl_dataset_zero_zil(ds, tx);

	dsl_destroy_head_sync_impl(clone, tx);

	dsl_dataset_rele(clone, FTAG);
	dsl_dataset_rele(ds, FTAG);
}