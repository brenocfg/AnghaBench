#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_9__ {int /*<<< orphan*/  ds_opening_lock; int /*<<< orphan*/ * ds_objset; int /*<<< orphan*/  ds_lock; int /*<<< orphan*/  ds_bp_rwlock; TYPE_1__* ds_dir; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_8__ {int /*<<< orphan*/  dd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int dmu_objset_open_impl (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_get_blkptr (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dataset_get_spa (TYPE_2__*) ; 
 scalar_t__ dsl_dataset_long_held (TYPE_2__*) ; 
 scalar_t__ dsl_pool_config_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dmu_objset_from_ds(dsl_dataset_t *ds, objset_t **osp)
{
	int err = 0;

	/*
	 * We shouldn't be doing anything with dsl_dataset_t's unless the
	 * pool_config lock is held, or the dataset is long-held.
	 */
	ASSERT(dsl_pool_config_held(ds->ds_dir->dd_pool) ||
	    dsl_dataset_long_held(ds));

	mutex_enter(&ds->ds_opening_lock);
	if (ds->ds_objset == NULL) {
		objset_t *os;
		rrw_enter(&ds->ds_bp_rwlock, RW_READER, FTAG);
		err = dmu_objset_open_impl(dsl_dataset_get_spa(ds),
		    ds, dsl_dataset_get_blkptr(ds), &os);
		rrw_exit(&ds->ds_bp_rwlock, FTAG);

		if (err == 0) {
			mutex_enter(&ds->ds_lock);
			ASSERT(ds->ds_objset == NULL);
			ds->ds_objset = os;
			mutex_exit(&ds->ds_lock);
		}
	}
	*osp = ds->ds_objset;
	mutex_exit(&ds->ds_opening_lock);
	return (err);
}