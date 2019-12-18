#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  space_map_t ;
struct TYPE_17__ {int /*<<< orphan*/  rt_root; } ;
typedef  TYPE_4__ range_tree_t ;
struct TYPE_18__ {void* ms_condensing; int /*<<< orphan*/  ms_lock; TYPE_4__* ms_allocatable; int /*<<< orphan*/ * ms_allocating; int /*<<< orphan*/ * ms_defer; int /*<<< orphan*/  ms_freed; int /*<<< orphan*/  ms_freeing; int /*<<< orphan*/  ms_size; int /*<<< orphan*/  ms_start; void* ms_condense_wanted; int /*<<< orphan*/ * ms_sm; TYPE_3__* ms_group; int /*<<< orphan*/  ms_id; int /*<<< orphan*/  ms_loaded; } ;
typedef  TYPE_5__ metaslab_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_16__ {TYPE_2__* mg_vd; } ;
struct TYPE_15__ {TYPE_1__* vdev_spa; int /*<<< orphan*/  vdev_id; } ;
struct TYPE_14__ {int /*<<< orphan*/  spa_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SM_ALLOC ; 
 int /*<<< orphan*/  SM_FREE ; 
 int /*<<< orphan*/  SM_NO_VDEVID ; 
 int TXG_CONCURRENT_STATES ; 
 int TXG_DEFER_SIZE ; 
 int TXG_MASK ; 
 int /*<<< orphan*/  avl_numnodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_add (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* range_tree_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_destroy (TYPE_4__*) ; 
 int /*<<< orphan*/  range_tree_remove ; 
 int /*<<< orphan*/  range_tree_vacate (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  space_map_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  space_map_truncate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  space_map_write (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_metaslab_sm_blksz ; 

__attribute__((used)) static void
metaslab_condense(metaslab_t *msp, uint64_t txg, dmu_tx_t *tx)
{
	range_tree_t *condense_tree;
	space_map_t *sm = msp->ms_sm;

	ASSERT(MUTEX_HELD(&msp->ms_lock));
	ASSERT(msp->ms_loaded);

	zfs_dbgmsg("condensing: txg %llu, msp[%llu] %p, vdev id %llu, "
	    "spa %s, smp size %llu, segments %lu, forcing condense=%s", txg,
	    msp->ms_id, msp, msp->ms_group->mg_vd->vdev_id,
	    msp->ms_group->mg_vd->vdev_spa->spa_name,
	    space_map_length(msp->ms_sm),
	    avl_numnodes(&msp->ms_allocatable->rt_root),
	    msp->ms_condense_wanted ? "TRUE" : "FALSE");

	msp->ms_condense_wanted = B_FALSE;

	/*
	 * Create an range tree that is 100% allocated. We remove segments
	 * that have been freed in this txg, any deferred frees that exist,
	 * and any allocation in the future. Removing segments should be
	 * a relatively inexpensive operation since we expect these trees to
	 * have a small number of nodes.
	 */
	condense_tree = range_tree_create(NULL, NULL);
	range_tree_add(condense_tree, msp->ms_start, msp->ms_size);

	range_tree_walk(msp->ms_freeing, range_tree_remove, condense_tree);
	range_tree_walk(msp->ms_freed, range_tree_remove, condense_tree);

	for (int t = 0; t < TXG_DEFER_SIZE; t++) {
		range_tree_walk(msp->ms_defer[t],
		    range_tree_remove, condense_tree);
	}

	for (int t = 1; t < TXG_CONCURRENT_STATES; t++) {
		range_tree_walk(msp->ms_allocating[(txg + t) & TXG_MASK],
		    range_tree_remove, condense_tree);
	}

	/*
	 * We're about to drop the metaslab's lock thus allowing
	 * other consumers to change it's content. Set the
	 * metaslab's ms_condensing flag to ensure that
	 * allocations on this metaslab do not occur while we're
	 * in the middle of committing it to disk. This is only critical
	 * for ms_allocatable as all other range trees use per txg
	 * views of their content.
	 */
	msp->ms_condensing = B_TRUE;

	mutex_exit(&msp->ms_lock);
	space_map_truncate(sm, zfs_metaslab_sm_blksz, tx);

	/*
	 * While we would ideally like to create a space map representation
	 * that consists only of allocation records, doing so can be
	 * prohibitively expensive because the in-core free tree can be
	 * large, and therefore computationally expensive to subtract
	 * from the condense_tree. Instead we sync out two trees, a cheap
	 * allocation only tree followed by the in-core free tree. While not
	 * optimal, this is typically close to optimal, and much cheaper to
	 * compute.
	 */
	space_map_write(sm, condense_tree, SM_ALLOC, SM_NO_VDEVID, tx);
	range_tree_vacate(condense_tree, NULL, NULL);
	range_tree_destroy(condense_tree);

	space_map_write(sm, msp->ms_allocatable, SM_FREE, SM_NO_VDEVID, tx);
	mutex_enter(&msp->ms_lock);
	msp->ms_condensing = B_FALSE;
}