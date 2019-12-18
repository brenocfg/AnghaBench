#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vdev_ms_count; int /*<<< orphan*/  vdev_nonrot; int /*<<< orphan*/  vdev_removing; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;
struct TYPE_6__ {int ms_size; int ms_fragmentation; int ms_id; int ms_weight; scalar_t__ ms_loaded; int /*<<< orphan*/  ms_sm; int /*<<< orphan*/  ms_lock; TYPE_3__* ms_group; } ;
typedef  TYPE_2__ metaslab_t ;
struct TYPE_7__ {TYPE_1__* mg_vd; } ;
typedef  TYPE_3__ metaslab_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int METASLAB_ACTIVE_MASK ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int SPA_MINBLOCKSIZE ; 
 int /*<<< orphan*/  WEIGHT_SET_SPACEBASED (int) ; 
 int ZFS_FRAG_INVALID ; 
 scalar_t__ metaslab_fragmentation_factor_enabled ; 
 scalar_t__ metaslab_lba_weighting_enabled ; 
 int space_map_allocated (int /*<<< orphan*/ ) ; 
 int zfs_metaslab_fragmentation_threshold ; 

__attribute__((used)) static uint64_t
metaslab_space_weight(metaslab_t *msp)
{
	metaslab_group_t *mg = msp->ms_group;
	vdev_t *vd = mg->mg_vd;
	uint64_t weight, space;

	ASSERT(MUTEX_HELD(&msp->ms_lock));
	ASSERT(!vd->vdev_removing);

	/*
	 * The baseline weight is the metaslab's free space.
	 */
	space = msp->ms_size - space_map_allocated(msp->ms_sm);

	if (metaslab_fragmentation_factor_enabled &&
	    msp->ms_fragmentation != ZFS_FRAG_INVALID) {
		/*
		 * Use the fragmentation information to inversely scale
		 * down the baseline weight. We need to ensure that we
		 * don't exclude this metaslab completely when it's 100%
		 * fragmented. To avoid this we reduce the fragmented value
		 * by 1.
		 */
		space = (space * (100 - (msp->ms_fragmentation - 1))) / 100;

		/*
		 * If space < SPA_MINBLOCKSIZE, then we will not allocate from
		 * this metaslab again. The fragmentation metric may have
		 * decreased the space to something smaller than
		 * SPA_MINBLOCKSIZE, so reset the space to SPA_MINBLOCKSIZE
		 * so that we can consume any remaining space.
		 */
		if (space > 0 && space < SPA_MINBLOCKSIZE)
			space = SPA_MINBLOCKSIZE;
	}
	weight = space;

	/*
	 * Modern disks have uniform bit density and constant angular velocity.
	 * Therefore, the outer recording zones are faster (higher bandwidth)
	 * than the inner zones by the ratio of outer to inner track diameter,
	 * which is typically around 2:1.  We account for this by assigning
	 * higher weight to lower metaslabs (multiplier ranging from 2x to 1x).
	 * In effect, this means that we'll select the metaslab with the most
	 * free bandwidth rather than simply the one with the most free space.
	 */
	if (!vd->vdev_nonrot && metaslab_lba_weighting_enabled) {
		weight = 2 * weight - (msp->ms_id * weight) / vd->vdev_ms_count;
		ASSERT(weight >= space && weight <= 2 * space);
	}

	/*
	 * If this metaslab is one we're actively using, adjust its
	 * weight to make it preferable to any inactive metaslab so
	 * we'll polish it off. If the fragmentation on this metaslab
	 * has exceed our threshold, then don't mark it active.
	 */
	if (msp->ms_loaded && msp->ms_fragmentation != ZFS_FRAG_INVALID &&
	    msp->ms_fragmentation <= zfs_metaslab_fragmentation_threshold) {
		weight |= (msp->ms_weight & METASLAB_ACTIVE_MASK);
	}

	WEIGHT_SET_SPACEBASED(weight);
	return (weight);
}