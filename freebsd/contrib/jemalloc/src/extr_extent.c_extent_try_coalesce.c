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
struct TYPE_5__ {scalar_t__ delay_coalesce; } ;
typedef  TYPE_1__ extents_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  extent_before_get (int /*<<< orphan*/ *) ; 
 int extent_can_coalesce (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_coalesce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * extent_lock_from_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_past_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static extent_t *
extent_try_coalesce(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, rtree_ctx_t *rtree_ctx, extents_t *extents,
    extent_t *extent, bool *coalesced, bool growing_retained) {
	/*
	 * Continue attempting to coalesce until failure, to protect against
	 * races with other threads that are thwarted by this one.
	 */
	bool again;
	do {
		again = false;

		/* Try to coalesce forward. */
		extent_t *next = extent_lock_from_addr(tsdn, rtree_ctx,
		    extent_past_get(extent));
		if (next != NULL) {
			/*
			 * extents->mtx only protects against races for
			 * like-state extents, so call extent_can_coalesce()
			 * before releasing next's pool lock.
			 */
			bool can_coalesce = extent_can_coalesce(arena, extents,
			    extent, next);

			extent_unlock(tsdn, next);

			if (can_coalesce && !extent_coalesce(tsdn, arena,
			    r_extent_hooks, extents, extent, next, true,
			    growing_retained)) {
				if (extents->delay_coalesce) {
					/* Do minimal coalescing. */
					*coalesced = true;
					return extent;
				}
				again = true;
			}
		}

		/* Try to coalesce backward. */
		extent_t *prev = extent_lock_from_addr(tsdn, rtree_ctx,
		    extent_before_get(extent));
		if (prev != NULL) {
			bool can_coalesce = extent_can_coalesce(arena, extents,
			    extent, prev);
			extent_unlock(tsdn, prev);

			if (can_coalesce && !extent_coalesce(tsdn, arena,
			    r_extent_hooks, extents, extent, prev, false,
			    growing_retained)) {
				extent = prev;
				if (extents->delay_coalesce) {
					/* Do minimal coalescing. */
					*coalesced = true;
					return extent;
				}
				again = true;
			}
		}
	} while (again);

	if (extents->delay_coalesce) {
		*coalesced = false;
	}
	return extent;
}