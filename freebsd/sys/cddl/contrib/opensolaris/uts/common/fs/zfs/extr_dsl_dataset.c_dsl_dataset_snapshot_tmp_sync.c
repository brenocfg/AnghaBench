#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  ds_prev; } ;
typedef  TYPE_1__ dsl_dataset_t ;
struct TYPE_7__ {int /*<<< orphan*/  ddsta_cleanup_minor; int /*<<< orphan*/  ddsta_htag; int /*<<< orphan*/  ddsta_snapname; int /*<<< orphan*/  ddsta_fsname; } ;
typedef  TYPE_2__ dsl_dataset_snapshot_tmp_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_snapshot_sync_impl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_user_hold_sync_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_destroy_snapshot_sync_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gethrestime_sec () ; 

__attribute__((used)) static void
dsl_dataset_snapshot_tmp_sync(void *arg, dmu_tx_t *tx)
{
	dsl_dataset_snapshot_tmp_arg_t *ddsta = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *ds;

	VERIFY0(dsl_dataset_hold(dp, ddsta->ddsta_fsname, FTAG, &ds));

	dsl_dataset_snapshot_sync_impl(ds, ddsta->ddsta_snapname, tx);
	dsl_dataset_user_hold_sync_one(ds->ds_prev, ddsta->ddsta_htag,
	    ddsta->ddsta_cleanup_minor, gethrestime_sec(), tx);
	dsl_destroy_snapshot_sync_impl(ds->ds_prev, B_TRUE, tx);

	dsl_dataset_rele(ds, FTAG);
}