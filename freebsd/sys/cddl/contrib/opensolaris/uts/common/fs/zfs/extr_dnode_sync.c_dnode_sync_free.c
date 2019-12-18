#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ dn_type; scalar_t__ dn_free_txg; scalar_t__ dn_allocated_txg; int dn_num_slots; scalar_t__ dn_object; int /*<<< orphan*/  dn_mtx; int /*<<< orphan*/  dn_have_spill; scalar_t__ dn_maxblkid; TYPE_11__* dn_phys; TYPE_1__* dn_dbuf; scalar_t__* dn_next_blksz; scalar_t__* dn_next_indblkshift; scalar_t__* dn_next_nlevels; int /*<<< orphan*/ * dn_dirty_records; } ;
typedef  TYPE_2__ dnode_t ;
typedef  int /*<<< orphan*/  dnode_phys_t ;
struct TYPE_16__ {int tx_txg; } ;
typedef  TYPE_3__ dmu_tx_t ;
struct TYPE_14__ {int /*<<< orphan*/  db; } ;
struct TYPE_13__ {scalar_t__ dn_type; int /*<<< orphan*/  dn_blkptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int BP_IS_HOLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ DMU_META_DNODE_OBJECT ; 
 scalar_t__ DMU_OT_NONE ; 
 int /*<<< orphan*/  DN_USED_BYTES (TYPE_11__*) ; 
 int TXG_MASK ; 
 int /*<<< orphan*/  bzero (TYPE_11__*,int) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int dmu_tx_is_syncing (TYPE_3__*) ; 
 int /*<<< orphan*/  dnode_evict_dbufs (TYPE_2__*) ; 
 int /*<<< orphan*/  dnode_free_interior_slots (TYPE_2__*) ; 
 int /*<<< orphan*/  dnode_rele (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  dnode_undirty_dbufs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dnode_sync_free(dnode_t *dn, dmu_tx_t *tx)
{
	int txgoff = tx->tx_txg & TXG_MASK;

	ASSERT(dmu_tx_is_syncing(tx));

	/*
	 * Our contents should have been freed in dnode_sync() by the
	 * free range record inserted by the caller of dnode_free().
	 */
	ASSERT0(DN_USED_BYTES(dn->dn_phys));
	ASSERT(BP_IS_HOLE(dn->dn_phys->dn_blkptr));

	dnode_undirty_dbufs(&dn->dn_dirty_records[txgoff]);
	dnode_evict_dbufs(dn);

	/*
	 * XXX - It would be nice to assert this, but we may still
	 * have residual holds from async evictions from the arc...
	 *
	 * zfs_obj_to_path() also depends on this being
	 * commented out.
	 *
	 * ASSERT3U(zfs_refcount_count(&dn->dn_holds), ==, 1);
	 */

	/* Undirty next bits */
	dn->dn_next_nlevels[txgoff] = 0;
	dn->dn_next_indblkshift[txgoff] = 0;
	dn->dn_next_blksz[txgoff] = 0;

	/* ASSERT(blkptrs are zero); */
	ASSERT(dn->dn_phys->dn_type != DMU_OT_NONE);
	ASSERT(dn->dn_type != DMU_OT_NONE);

	ASSERT(dn->dn_free_txg > 0);
	if (dn->dn_allocated_txg != dn->dn_free_txg)
		dmu_buf_will_dirty(&dn->dn_dbuf->db, tx);
	bzero(dn->dn_phys, sizeof (dnode_phys_t) * dn->dn_num_slots);
	dnode_free_interior_slots(dn);

	mutex_enter(&dn->dn_mtx);
	dn->dn_type = DMU_OT_NONE;
	dn->dn_maxblkid = 0;
	dn->dn_allocated_txg = 0;
	dn->dn_free_txg = 0;
	dn->dn_have_spill = B_FALSE;
	dn->dn_num_slots = 1;
	mutex_exit(&dn->dn_mtx);

	ASSERT(dn->dn_object != DMU_META_DNODE_OBJECT);

	dnode_rele(dn, (void *)(uintptr_t)tx->tx_txg);
	/*
	 * Now that we've released our hold, the dnode may
	 * be evicted, so we musn't access it.
	 */
}