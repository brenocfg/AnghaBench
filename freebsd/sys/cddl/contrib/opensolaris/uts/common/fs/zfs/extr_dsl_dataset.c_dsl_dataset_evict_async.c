#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ds_bp_rwlock; int /*<<< orphan*/  ds_longholds; int /*<<< orphan*/  ds_remap_deadlist_lock; int /*<<< orphan*/  ds_sendstream_lock; int /*<<< orphan*/  ds_opening_lock; int /*<<< orphan*/  ds_lock; int /*<<< orphan*/  ds_prop_cbs; int /*<<< orphan*/  ds_synced_link; scalar_t__ ds_dir; int /*<<< orphan*/  ds_remap_deadlist; int /*<<< orphan*/  ds_deadlist; int /*<<< orphan*/  ds_pending_deadlist; int /*<<< orphan*/ * ds_prev; int /*<<< orphan*/ * ds_objset; int /*<<< orphan*/ * ds_dbuf; int /*<<< orphan*/ * ds_owner; } ;
typedef  TYPE_1__ dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  bplist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_evict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_deadlist_close (int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_deadlist_is_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_async_rele (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_link_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_dataset_evict_async(void *dbu)
{
	dsl_dataset_t *ds = dbu;

	ASSERT(ds->ds_owner == NULL);

	ds->ds_dbuf = NULL;

	if (ds->ds_objset != NULL)
		dmu_objset_evict(ds->ds_objset);

	if (ds->ds_prev) {
		dsl_dataset_rele(ds->ds_prev, ds);
		ds->ds_prev = NULL;
	}

	bplist_destroy(&ds->ds_pending_deadlist);
	if (dsl_deadlist_is_open(&ds->ds_deadlist))
		dsl_deadlist_close(&ds->ds_deadlist);
	if (dsl_deadlist_is_open(&ds->ds_remap_deadlist))
		dsl_deadlist_close(&ds->ds_remap_deadlist);
	if (ds->ds_dir)
		dsl_dir_async_rele(ds->ds_dir, ds);

	ASSERT(!list_link_active(&ds->ds_synced_link));

	list_destroy(&ds->ds_prop_cbs);
	if (mutex_owned(&ds->ds_lock))
		mutex_exit(&ds->ds_lock);
	mutex_destroy(&ds->ds_lock);
	if (mutex_owned(&ds->ds_opening_lock))
		mutex_exit(&ds->ds_opening_lock);
	mutex_destroy(&ds->ds_opening_lock);
	mutex_destroy(&ds->ds_sendstream_lock);
	mutex_destroy(&ds->ds_remap_deadlist_lock);
	zfs_refcount_destroy(&ds->ds_longholds);
	rrw_destroy(&ds->ds_bp_rwlock);

	kmem_free(ds, sizeof (dsl_dataset_t));
}