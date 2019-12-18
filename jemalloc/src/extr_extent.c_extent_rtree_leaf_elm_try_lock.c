#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  rtree_leaf_elm_t ;
typedef  int /*<<< orphan*/  lock_result_t ;
typedef  int /*<<< orphan*/  extent_t ;

/* Variables and functions */
 int /*<<< orphan*/  extent_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extents_rtree ; 
 int /*<<< orphan*/  lock_result_failure ; 
 int /*<<< orphan*/  lock_result_no_extent ; 
 int /*<<< orphan*/  lock_result_success ; 
 int /*<<< orphan*/ * rtree_leaf_elm_extent_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ rtree_leaf_elm_slab_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static lock_result_t
extent_rtree_leaf_elm_try_lock(tsdn_t *tsdn, rtree_leaf_elm_t *elm,
    extent_t **result, bool inactive_only) {
	extent_t *extent1 = rtree_leaf_elm_extent_read(tsdn, &extents_rtree,
	    elm, true);

	/* Slab implies active extents and should be skipped. */
	if (extent1 == NULL || (inactive_only && rtree_leaf_elm_slab_read(tsdn,
	    &extents_rtree, elm, true))) {
		return lock_result_no_extent;
	}

	/*
	 * It's possible that the extent changed out from under us, and with it
	 * the leaf->extent mapping.  We have to recheck while holding the lock.
	 */
	extent_lock(tsdn, extent1);
	extent_t *extent2 = rtree_leaf_elm_extent_read(tsdn,
	    &extents_rtree, elm, true);

	if (extent1 == extent2) {
		*result = extent1;
		return lock_result_success;
	} else {
		extent_unlock(tsdn, extent1);
		return lock_result_failure;
	}
}