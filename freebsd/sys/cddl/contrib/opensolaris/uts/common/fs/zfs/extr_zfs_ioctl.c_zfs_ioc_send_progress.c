#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_11__ {int /*<<< orphan*/  ds_sendstream_lock; int /*<<< orphan*/  ds_sendstreams; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_12__ {scalar_t__ dsa_proc; int /*<<< orphan*/ * dsa_off; int /*<<< orphan*/  dsa_outfd; } ;
typedef  TYPE_3__ dmu_sendarg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ curproc ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int dsl_pool_hold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_3__* list_next (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_ioc_send_progress(zfs_cmd_t *zc)
{
	dsl_pool_t *dp;
	dsl_dataset_t *ds;
	dmu_sendarg_t *dsp = NULL;
	int error;

	error = dsl_pool_hold(zc->zc_name, FTAG, &dp);
	if (error != 0)
		return (error);

	error = dsl_dataset_hold(dp, zc->zc_name, FTAG, &ds);
	if (error != 0) {
		dsl_pool_rele(dp, FTAG);
		return (error);
	}

	mutex_enter(&ds->ds_sendstream_lock);

	/*
	 * Iterate over all the send streams currently active on this dataset.
	 * If there's one which matches the specified file descriptor _and_ the
	 * stream was started by the current process, return the progress of
	 * that stream.
	 */
	for (dsp = list_head(&ds->ds_sendstreams); dsp != NULL;
	    dsp = list_next(&ds->ds_sendstreams, dsp)) {
		if (dsp->dsa_outfd == zc->zc_cookie &&
		    dsp->dsa_proc == curproc)
			break;
	}

	if (dsp != NULL)
		zc->zc_cookie = *(dsp->dsa_off);
	else
		error = SET_ERROR(ENOENT);

	mutex_exit(&ds->ds_sendstream_lock);
	dsl_dataset_rele(ds, FTAG);
	dsl_pool_rele(dp, FTAG);
	return (error);
}