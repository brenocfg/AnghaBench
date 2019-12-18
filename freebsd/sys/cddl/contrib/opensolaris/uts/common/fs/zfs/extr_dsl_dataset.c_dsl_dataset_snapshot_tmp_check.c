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
struct TYPE_5__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_6__ {int /*<<< orphan*/  ddsta_htag; int /*<<< orphan*/  ddsta_snapname; int /*<<< orphan*/  ddsta_fsname; } ;
typedef  TYPE_2__ dsl_dataset_snapshot_tmp_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPA_VERSION_USERREFS ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_dataset_snapshot_check_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dsl_dataset_user_hold_check_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_dataset_snapshot_tmp_check(void *arg, dmu_tx_t *tx)
{
	dsl_dataset_snapshot_tmp_arg_t *ddsta = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *ds;
	int error;

	error = dsl_dataset_hold(dp, ddsta->ddsta_fsname, FTAG, &ds);
	if (error != 0)
		return (error);

	/* NULL cred means no limit check for tmp snapshot */
	error = dsl_dataset_snapshot_check_impl(ds, ddsta->ddsta_snapname,
	    tx, B_FALSE, 0, NULL);
	if (error != 0) {
		dsl_dataset_rele(ds, FTAG);
		return (error);
	}

	if (spa_version(dp->dp_spa) < SPA_VERSION_USERREFS) {
		dsl_dataset_rele(ds, FTAG);
		return (SET_ERROR(ENOTSUP));
	}
	error = dsl_dataset_user_hold_check_one(NULL, ddsta->ddsta_htag,
	    B_TRUE, tx);
	if (error != 0) {
		dsl_dataset_rele(ds, FTAG);
		return (error);
	}

	dsl_dataset_rele(ds, FTAG);
	return (0);
}