#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_16__ {int /*<<< orphan*/  os_dsl_dataset; int /*<<< orphan*/ ** os_dirty_dnodes; } ;
typedef  TYPE_2__ objset_t ;
typedef  int /*<<< orphan*/  multilist_t ;
typedef  int /*<<< orphan*/  multilist_sublist_t ;
struct TYPE_17__ {scalar_t__ dn_free_txg; scalar_t__ dn_datablksz; int /*<<< orphan*/  dn_dbuf; int /*<<< orphan*/  dn_object; int /*<<< orphan*/ * dn_next_bonustype; int /*<<< orphan*/ * dn_next_blksz; int /*<<< orphan*/ * dn_next_bonuslen; int /*<<< orphan*/  dn_dbufs; int /*<<< orphan*/  dn_holds; int /*<<< orphan*/ * dn_dirty_link; int /*<<< orphan*/  dn_mtx; scalar_t__ dn_allocated_txg; TYPE_1__* dn_phys; TYPE_2__* dn_objset; } ;
typedef  TYPE_3__ dnode_t ;
struct TYPE_18__ {size_t tx_txg; } ;
typedef  TYPE_4__ dmu_tx_t ;
struct TYPE_15__ {scalar_t__ dn_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DMU_OBJECT_IS_SPECIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DNODE_VERIFY (TYPE_3__*) ; 
 size_t TXG_MASK ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbuf_dirty (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  dmu_objset_userquota_get_ids (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  dnode_add_ref (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  dprintf_ds (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dsl_dataset_dirty (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ multilist_link_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multilist_sublist_insert_head (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * multilist_sublist_lock_obj (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  multilist_sublist_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_is_zero (int /*<<< orphan*/ *) ; 

void
dnode_setdirty(dnode_t *dn, dmu_tx_t *tx)
{
	objset_t *os = dn->dn_objset;
	uint64_t txg = tx->tx_txg;

	if (DMU_OBJECT_IS_SPECIAL(dn->dn_object)) {
		dsl_dataset_dirty(os->os_dsl_dataset, tx);
		return;
	}

	DNODE_VERIFY(dn);

#ifdef ZFS_DEBUG
	mutex_enter(&dn->dn_mtx);
	ASSERT(dn->dn_phys->dn_type || dn->dn_allocated_txg);
	ASSERT(dn->dn_free_txg == 0 || dn->dn_free_txg >= txg);
	mutex_exit(&dn->dn_mtx);
#endif

	/*
	 * Determine old uid/gid when necessary
	 */
	dmu_objset_userquota_get_ids(dn, B_TRUE, tx);

	multilist_t *dirtylist = os->os_dirty_dnodes[txg & TXG_MASK];
	multilist_sublist_t *mls = multilist_sublist_lock_obj(dirtylist, dn);

	/*
	 * If we are already marked dirty, we're done.
	 */
	if (multilist_link_active(&dn->dn_dirty_link[txg & TXG_MASK])) {
		multilist_sublist_unlock(mls);
		return;
	}

	ASSERT(!zfs_refcount_is_zero(&dn->dn_holds) ||
	    !avl_is_empty(&dn->dn_dbufs));
	ASSERT(dn->dn_datablksz != 0);
	ASSERT0(dn->dn_next_bonuslen[txg&TXG_MASK]);
	ASSERT0(dn->dn_next_blksz[txg&TXG_MASK]);
	ASSERT0(dn->dn_next_bonustype[txg&TXG_MASK]);

	dprintf_ds(os->os_dsl_dataset, "obj=%llu txg=%llu\n",
	    dn->dn_object, txg);

	multilist_sublist_insert_head(mls, dn);

	multilist_sublist_unlock(mls);

	/*
	 * The dnode maintains a hold on its containing dbuf as
	 * long as there are holds on it.  Each instantiated child
	 * dbuf maintains a hold on the dnode.  When the last child
	 * drops its hold, the dnode will drop its hold on the
	 * containing dbuf. We add a "dirty hold" here so that the
	 * dnode will hang around after we finish processing its
	 * children.
	 */
	VERIFY(dnode_add_ref(dn, (void *)(uintptr_t)tx->tx_txg));

	(void) dbuf_dirty(dn->dn_dbuf, tx);

	dsl_dataset_dirty(os->os_dsl_dataset, tx);
}