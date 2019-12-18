#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int vdev_ashift; int /*<<< orphan*/  vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_12__ {int /*<<< orphan*/  sm_dbuf; } ;
typedef  TYPE_3__ space_map_t ;
struct TYPE_13__ {scalar_t__ ms_condense_checked_txg; int /*<<< orphan*/  ms_allocatable; TYPE_3__* ms_sm; scalar_t__ ms_condense_wanted; int /*<<< orphan*/  ms_allocatable_by_size; int /*<<< orphan*/  ms_loaded; int /*<<< orphan*/  ms_lock; TYPE_1__* ms_group; } ;
typedef  TYPE_4__ metaslab_t ;
struct TYPE_14__ {int /*<<< orphan*/  doi_data_block_size; } ;
typedef  TYPE_5__ dmu_object_info_t ;
typedef  int boolean_t ;
struct TYPE_10__ {TYPE_2__* mg_vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int B_FALSE ; 
 int B_TRUE ; 
 scalar_t__ MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SM_NO_VDEVID ; 
 scalar_t__ avl_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_object_info_from_db (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ spa_syncing_txg (int /*<<< orphan*/ ) ; 
 scalar_t__ space_map_estimate_optimal_size (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ space_map_length (TYPE_3__*) ; 
 scalar_t__ zfs_condense_pct ; 
 scalar_t__ zfs_metaslab_condense_block_threshold ; 

__attribute__((used)) static boolean_t
metaslab_should_condense(metaslab_t *msp)
{
	space_map_t *sm = msp->ms_sm;
	vdev_t *vd = msp->ms_group->mg_vd;
	uint64_t vdev_blocksize = 1 << vd->vdev_ashift;
	uint64_t current_txg = spa_syncing_txg(vd->vdev_spa);

	ASSERT(MUTEX_HELD(&msp->ms_lock));
	ASSERT(msp->ms_loaded);

	/*
	 * Allocations and frees in early passes are generally more space
	 * efficient (in terms of blocks described in space map entries)
	 * than the ones in later passes (e.g. we don't compress after
	 * sync pass 5) and condensing a metaslab multiple times in a txg
	 * could degrade performance.
	 *
	 * Thus we prefer condensing each metaslab at most once every txg at
	 * the earliest sync pass possible. If a metaslab is eligible for
	 * condensing again after being considered for condensing within the
	 * same txg, it will hopefully be dirty in the next txg where it will
	 * be condensed at an earlier pass.
	 */
	if (msp->ms_condense_checked_txg == current_txg)
		return (B_FALSE);
	msp->ms_condense_checked_txg = current_txg;

	/*
	 * We always condense metaslabs that are empty and metaslabs for
	 * which a condense request has been made.
	 */
	if (avl_is_empty(&msp->ms_allocatable_by_size) ||
	    msp->ms_condense_wanted)
		return (B_TRUE);

	uint64_t object_size = space_map_length(msp->ms_sm);
	uint64_t optimal_size = space_map_estimate_optimal_size(sm,
	    msp->ms_allocatable, SM_NO_VDEVID);

	dmu_object_info_t doi;
	dmu_object_info_from_db(sm->sm_dbuf, &doi);
	uint64_t record_size = MAX(doi.doi_data_block_size, vdev_blocksize);

	return (object_size >= (optimal_size * zfs_condense_pct / 100) &&
	    object_size > zfs_metaslab_condense_block_threshold * record_size);
}