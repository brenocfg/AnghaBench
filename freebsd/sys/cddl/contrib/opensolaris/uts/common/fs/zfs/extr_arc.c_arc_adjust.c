#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {int /*<<< orphan*/  arcs_size; } ;
struct TYPE_8__ {int /*<<< orphan*/  arcs_size; } ;

/* Variables and functions */
 scalar_t__ ARC_BUFC_DATA ; 
 scalar_t__ ARC_BUFC_METADATA ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ aggsum_value (int /*<<< orphan*/ *) ; 
 scalar_t__ arc_adjust_impl (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ arc_adjust_meta (scalar_t__) ; 
 scalar_t__ arc_adjust_type (TYPE_1__*) ; 
 TYPE_5__* arc_anon ; 
 scalar_t__ arc_c ; 
 scalar_t__ arc_meta_min ; 
 int /*<<< orphan*/  arc_meta_used ; 
 TYPE_1__* arc_mfu ; 
 TYPE_1__* arc_mfu_ghost ; 
 TYPE_1__* arc_mru ; 
 TYPE_1__* arc_mru_ghost ; 
 scalar_t__ arc_p ; 
 int /*<<< orphan*/  arc_size ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t
arc_adjust(void)
{
	uint64_t total_evicted = 0;
	uint64_t bytes;
	int64_t target;
	uint64_t asize = aggsum_value(&arc_size);
	uint64_t ameta = aggsum_value(&arc_meta_used);

	/*
	 * If we're over arc_meta_limit, we want to correct that before
	 * potentially evicting data buffers below.
	 */
	total_evicted += arc_adjust_meta(ameta);

	/*
	 * Adjust MRU size
	 *
	 * If we're over the target cache size, we want to evict enough
	 * from the list to get back to our target size. We don't want
	 * to evict too much from the MRU, such that it drops below
	 * arc_p. So, if we're over our target cache size more than
	 * the MRU is over arc_p, we'll evict enough to get back to
	 * arc_p here, and then evict more from the MFU below.
	 */
	target = MIN((int64_t)(asize - arc_c),
	    (int64_t)(zfs_refcount_count(&arc_anon->arcs_size) +
	    zfs_refcount_count(&arc_mru->arcs_size) + ameta - arc_p));

	/*
	 * If we're below arc_meta_min, always prefer to evict data.
	 * Otherwise, try to satisfy the requested number of bytes to
	 * evict from the type which contains older buffers; in an
	 * effort to keep newer buffers in the cache regardless of their
	 * type. If we cannot satisfy the number of bytes from this
	 * type, spill over into the next type.
	 */
	if (arc_adjust_type(arc_mru) == ARC_BUFC_METADATA &&
	    ameta > arc_meta_min) {
		bytes = arc_adjust_impl(arc_mru, 0, target, ARC_BUFC_METADATA);
		total_evicted += bytes;

		/*
		 * If we couldn't evict our target number of bytes from
		 * metadata, we try to get the rest from data.
		 */
		target -= bytes;

		total_evicted +=
		    arc_adjust_impl(arc_mru, 0, target, ARC_BUFC_DATA);
	} else {
		bytes = arc_adjust_impl(arc_mru, 0, target, ARC_BUFC_DATA);
		total_evicted += bytes;

		/*
		 * If we couldn't evict our target number of bytes from
		 * data, we try to get the rest from metadata.
		 */
		target -= bytes;

		total_evicted +=
		    arc_adjust_impl(arc_mru, 0, target, ARC_BUFC_METADATA);
	}

	/*
	 * Re-sum ARC stats after the first round of evictions.
	 */
	asize = aggsum_value(&arc_size);
	ameta = aggsum_value(&arc_meta_used);

	/*
	 * Adjust MFU size
	 *
	 * Now that we've tried to evict enough from the MRU to get its
	 * size back to arc_p, if we're still above the target cache
	 * size, we evict the rest from the MFU.
	 */
	target = asize - arc_c;

	if (arc_adjust_type(arc_mfu) == ARC_BUFC_METADATA &&
	    ameta > arc_meta_min) {
		bytes = arc_adjust_impl(arc_mfu, 0, target, ARC_BUFC_METADATA);
		total_evicted += bytes;

		/*
		 * If we couldn't evict our target number of bytes from
		 * metadata, we try to get the rest from data.
		 */
		target -= bytes;

		total_evicted +=
		    arc_adjust_impl(arc_mfu, 0, target, ARC_BUFC_DATA);
	} else {
		bytes = arc_adjust_impl(arc_mfu, 0, target, ARC_BUFC_DATA);
		total_evicted += bytes;

		/*
		 * If we couldn't evict our target number of bytes from
		 * data, we try to get the rest from data.
		 */
		target -= bytes;

		total_evicted +=
		    arc_adjust_impl(arc_mfu, 0, target, ARC_BUFC_METADATA);
	}

	/*
	 * Adjust ghost lists
	 *
	 * In addition to the above, the ARC also defines target values
	 * for the ghost lists. The sum of the mru list and mru ghost
	 * list should never exceed the target size of the cache, and
	 * the sum of the mru list, mfu list, mru ghost list, and mfu
	 * ghost list should never exceed twice the target size of the
	 * cache. The following logic enforces these limits on the ghost
	 * caches, and evicts from them as needed.
	 */
	target = zfs_refcount_count(&arc_mru->arcs_size) +
	    zfs_refcount_count(&arc_mru_ghost->arcs_size) - arc_c;

	bytes = arc_adjust_impl(arc_mru_ghost, 0, target, ARC_BUFC_DATA);
	total_evicted += bytes;

	target -= bytes;

	total_evicted +=
	    arc_adjust_impl(arc_mru_ghost, 0, target, ARC_BUFC_METADATA);

	/*
	 * We assume the sum of the mru list and mfu list is less than
	 * or equal to arc_c (we enforced this above), which means we
	 * can use the simpler of the two equations below:
	 *
	 *	mru + mfu + mru ghost + mfu ghost <= 2 * arc_c
	 *		    mru ghost + mfu ghost <= arc_c
	 */
	target = zfs_refcount_count(&arc_mru_ghost->arcs_size) +
	    zfs_refcount_count(&arc_mfu_ghost->arcs_size) - arc_c;

	bytes = arc_adjust_impl(arc_mfu_ghost, 0, target, ARC_BUFC_DATA);
	total_evicted += bytes;

	target -= bytes;

	total_evicted +=
	    arc_adjust_impl(arc_mfu_ghost, 0, target, ARC_BUFC_METADATA);

	return (total_evicted);
}