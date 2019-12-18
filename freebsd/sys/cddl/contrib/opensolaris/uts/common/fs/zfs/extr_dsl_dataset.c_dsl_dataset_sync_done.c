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
struct TYPE_6__ {int /*<<< orphan*/ * os_synced_dnodes; } ;
typedef  TYPE_1__ objset_t ;
struct TYPE_7__ {int /*<<< orphan*/  ds_dbuf; int /*<<< orphan*/  ds_deadlist; int /*<<< orphan*/  ds_pending_deadlist; TYPE_1__* ds_objset; } ;
typedef  TYPE_2__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  bplist_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deadlist_enqueue_cb ; 
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dmu_objset_is_dirty (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_get_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multilist_destroy (int /*<<< orphan*/ *) ; 

void
dsl_dataset_sync_done(dsl_dataset_t *ds, dmu_tx_t *tx)
{
	objset_t *os = ds->ds_objset;

	bplist_iterate(&ds->ds_pending_deadlist,
	    deadlist_enqueue_cb, &ds->ds_deadlist, tx);

	if (os->os_synced_dnodes != NULL) {
		multilist_destroy(os->os_synced_dnodes);
		os->os_synced_dnodes = NULL;
	}

	ASSERT(!dmu_objset_is_dirty(os, dmu_tx_get_txg(tx)));

	dmu_buf_rele(ds->ds_dbuf, ds);
}