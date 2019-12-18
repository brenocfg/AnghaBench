#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ vdev_removing; int /*<<< orphan*/ * vdev_spa; } ;
typedef  TYPE_4__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  space_map_phys_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_15__ {TYPE_2__* ms_sm; int /*<<< orphan*/  ms_max_size; scalar_t__ ms_loaded; int /*<<< orphan*/  ms_lock; TYPE_3__* ms_group; } ;
typedef  TYPE_5__ metaslab_t ;
struct TYPE_13__ {TYPE_4__* mg_vd; } ;
struct TYPE_12__ {TYPE_1__* sm_dbuf; } ;
struct TYPE_11__ {int db_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPA_FEATURE_SPACEMAP_HISTOGRAM ; 
 int /*<<< orphan*/  metaslab_block_maxsize (TYPE_5__*) ; 
 int /*<<< orphan*/  metaslab_segment_weight (TYPE_5__*) ; 
 int /*<<< orphan*/  metaslab_set_fragmentation (TYPE_5__*) ; 
 int /*<<< orphan*/  metaslab_space_weight (TYPE_5__*) ; 
 scalar_t__ spa_feature_is_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_metaslab_segment_weight_enabled ; 

__attribute__((used)) static uint64_t
metaslab_weight(metaslab_t *msp)
{
	vdev_t *vd = msp->ms_group->mg_vd;
	spa_t *spa = vd->vdev_spa;
	uint64_t weight;

	ASSERT(MUTEX_HELD(&msp->ms_lock));

	/*
	 * If this vdev is in the process of being removed, there is nothing
	 * for us to do here.
	 */
	if (vd->vdev_removing)
		return (0);

	metaslab_set_fragmentation(msp);

	/*
	 * Update the maximum size if the metaslab is loaded. This will
	 * ensure that we get an accurate maximum size if newly freed space
	 * has been added back into the free tree.
	 */
	if (msp->ms_loaded)
		msp->ms_max_size = metaslab_block_maxsize(msp);

	/*
	 * Segment-based weighting requires space map histogram support.
	 */
	if (zfs_metaslab_segment_weight_enabled &&
	    spa_feature_is_enabled(spa, SPA_FEATURE_SPACEMAP_HISTOGRAM) &&
	    (msp->ms_sm == NULL || msp->ms_sm->sm_dbuf->db_size ==
	    sizeof (space_map_phys_t))) {
		weight = metaslab_segment_weight(msp);
	} else {
		weight = metaslab_space_weight(msp);
	}
	return (weight);
}