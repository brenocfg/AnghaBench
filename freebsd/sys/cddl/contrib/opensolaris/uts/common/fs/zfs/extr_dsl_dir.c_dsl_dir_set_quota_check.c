#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  ddsqra_value; int /*<<< orphan*/  ddsqra_source; int /*<<< orphan*/  ddsqra_name; } ;
typedef  TYPE_1__ dsl_dir_set_qr_arg_t ;
struct TYPE_10__ {TYPE_3__* ds_dir; } ;
typedef  TYPE_2__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_12__ {scalar_t__ dd_reserved; scalar_t__ dd_used_bytes; } ;
struct TYPE_11__ {int /*<<< orphan*/  dd_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ dmu_tx_is_syncing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* dsl_dir_phys (TYPE_3__*) ; 
 scalar_t__ dsl_dir_space_towrite (TYPE_3__*) ; 
 int dsl_prop_predict (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dsl_dir_set_quota_check(void *arg, dmu_tx_t *tx)
{
	dsl_dir_set_qr_arg_t *ddsqra = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *ds;
	int error;
	uint64_t towrite, newval;

	error = dsl_dataset_hold(dp, ddsqra->ddsqra_name, FTAG, &ds);
	if (error != 0)
		return (error);

	error = dsl_prop_predict(ds->ds_dir, "quota",
	    ddsqra->ddsqra_source, ddsqra->ddsqra_value, &newval);
	if (error != 0) {
		dsl_dataset_rele(ds, FTAG);
		return (error);
	}

	if (newval == 0) {
		dsl_dataset_rele(ds, FTAG);
		return (0);
	}

	mutex_enter(&ds->ds_dir->dd_lock);
	/*
	 * If we are doing the preliminary check in open context, and
	 * there are pending changes, then don't fail it, since the
	 * pending changes could under-estimate the amount of space to be
	 * freed up.
	 */
	towrite = dsl_dir_space_towrite(ds->ds_dir);
	if ((dmu_tx_is_syncing(tx) || towrite == 0) &&
	    (newval < dsl_dir_phys(ds->ds_dir)->dd_reserved ||
	    newval < dsl_dir_phys(ds->ds_dir)->dd_used_bytes + towrite)) {
		error = SET_ERROR(ENOSPC);
	}
	mutex_exit(&ds->ds_dir->dd_lock);
	dsl_dataset_rele(ds, FTAG);
	return (error);
}