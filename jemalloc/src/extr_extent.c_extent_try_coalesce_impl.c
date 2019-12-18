#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  rtree_ctx_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_5__ {scalar_t__ delay_coalesce; } ;
typedef  TYPE_1__ eset_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  extent_before_get (int /*<<< orphan*/ *) ; 
 int extent_can_coalesce (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_coalesce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * extent_lock_from_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  extent_past_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static extent_t *
extent_try_coalesce_impl(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, rtree_ctx_t *rtree_ctx, eset_t *eset,
    extent_t *extent, bool *coalesced, bool growing_retained,
    bool inactive_only) {
	/*
	 * We avoid checking / locking inactive neighbors for large size
	 * classes, since they are eagerly coalesced on deallocation which can
	 * cause lock contention.
	 */
	/*
	 * Continue attempting to coalesce until failure, to protect against
	 * races with other threads that are thwarted by this one.
	 */
	bool again;
	do {
		again = false;

		/* Try to coalesce forward. */
		extent_t *next = extent_lock_from_addr(tsdn, rtree_ctx,
		    extent_past_get(extent), inactive_only);
		if (next != NULL) {
			/*
			 * eset->mtx only protects against races for
			 * like-state eset, so call extent_can_coalesce()
			 * before releasing next's pool lock.
			 */
			bool can_coalesce = extent_can_coalesce(arena, eset,
			    extent, next);

			extent_unlock(tsdn, next);

			if (can_coalesce && !extent_coalesce(tsdn, arena,
			    r_extent_hooks, eset, extent, next, true,
			    growing_retained)) {
				if (eset->delay_coalesce) {
					/* Do minimal coalescing. */
					*coalesced = true;
					return extent;
				}
				again = true;
			}
		}

		/* Try to coalesce backward. */
		extent_t *prev = extent_lock_from_addr(tsdn, rtree_ctx,
		    extent_before_get(extent), inactive_only);
		if (prev != NULL) {
			bool can_coalesce = extent_can_coalesce(arena, eset,
			    extent, prev);
			extent_unlock(tsdn, prev);

			if (can_coalesce && !extent_coalesce(tsdn, arena,
			    r_extent_hooks, eset, extent, prev, false,
			    growing_retained)) {
				extent = prev;
				if (eset->delay_coalesce) {
					/* Do minimal coalescing. */
					*coalesced = true;
					return extent;
				}
				again = true;
			}
		}
	} while (again);

	if (eset->delay_coalesce) {
		*coalesced = false;
	}
	return extent;
}