#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  dva_t ;
struct TYPE_21__ {int /*<<< orphan*/  ds_remap_deadlist; int /*<<< orphan*/  ds_remap_deadlist_lock; int /*<<< orphan*/  ds_is_snapshot; TYPE_2__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_22__ {scalar_t__ tx_txg; } ;
typedef  TYPE_4__ dmu_tx_t ;
struct TYPE_23__ {scalar_t__ blk_birth; int /*<<< orphan*/ * blk_dva; } ;
typedef  TYPE_5__ blkptr_t ;
struct TYPE_20__ {TYPE_1__* dd_pool; } ;
struct TYPE_19__ {int /*<<< orphan*/ * dp_spa; } ;
struct TYPE_18__ {scalar_t__ ds_prev_snap_txg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BP_ZERO (TYPE_5__*) ; 
 int /*<<< orphan*/  DVA_SET_ASIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DVA_SET_OFFSET (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DVA_SET_VDEV (int /*<<< orphan*/ *,scalar_t__) ; 
 int dmu_tx_is_syncing (TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_dataset_create_remap_deadlist (TYPE_3__*,TYPE_4__*) ; 
 TYPE_10__* dsl_dataset_phys (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_dataset_remap_deadlist_exists (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_deadlist_insert (int /*<<< orphan*/ *,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_vdev_indirect_mark_obsolete (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,TYPE_4__*) ; 

void
dsl_dataset_block_remapped(dsl_dataset_t *ds, uint64_t vdev, uint64_t offset,
    uint64_t size, uint64_t birth, dmu_tx_t *tx)
{
	spa_t *spa = ds->ds_dir->dd_pool->dp_spa;

	ASSERT(dmu_tx_is_syncing(tx));
	ASSERT(birth <= tx->tx_txg);
	ASSERT(!ds->ds_is_snapshot);

	if (birth > dsl_dataset_phys(ds)->ds_prev_snap_txg) {
		spa_vdev_indirect_mark_obsolete(spa, vdev, offset, size, tx);
	} else {
		blkptr_t fakebp;
		dva_t *dva = &fakebp.blk_dva[0];

		ASSERT(ds != NULL);

		mutex_enter(&ds->ds_remap_deadlist_lock);
		if (!dsl_dataset_remap_deadlist_exists(ds)) {
			dsl_dataset_create_remap_deadlist(ds, tx);
		}
		mutex_exit(&ds->ds_remap_deadlist_lock);

		BP_ZERO(&fakebp);
		fakebp.blk_birth = birth;
		DVA_SET_VDEV(dva, vdev);
		DVA_SET_OFFSET(dva, offset);
		DVA_SET_ASIZE(dva, size);

		dsl_deadlist_insert(&ds->ds_remap_deadlist, &fakebp, tx);
	}
}