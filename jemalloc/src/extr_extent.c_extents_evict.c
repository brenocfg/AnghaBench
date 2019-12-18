#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  rtree_ctx_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_6__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  delay_coalesce; int /*<<< orphan*/  npages; int /*<<< orphan*/  lru; } ;
typedef  TYPE_1__ eset_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 size_t atomic_load_zu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eset_remove_locked (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int eset_state_get (TYPE_1__*) ; 
 int /*<<< orphan*/  extent_deregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_list_first (int /*<<< orphan*/ *) ; 
#define  extent_state_active 131 
#define  extent_state_dirty 130 
#define  extent_state_muzzy 129 
#define  extent_state_retained 128 
 int /*<<< orphan*/  extent_state_set (int /*<<< orphan*/ *,int const) ; 
 scalar_t__ extent_try_delayed_coalesce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  not_reached () ; 
 int /*<<< orphan*/ * tsdn_rtree_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

extent_t *
extents_evict(tsdn_t *tsdn, arena_t *arena, extent_hooks_t **r_extent_hooks,
    eset_t *eset, size_t npages_min) {
	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);

	malloc_mutex_lock(tsdn, &eset->mtx);

	/*
	 * Get the LRU coalesced extent, if any.  If coalescing was delayed,
	 * the loop will iterate until the LRU extent is fully coalesced.
	 */
	extent_t *extent;
	while (true) {
		/* Get the LRU extent, if any. */
		extent = extent_list_first(&eset->lru);
		if (extent == NULL) {
			goto label_return;
		}
		/* Check the eviction limit. */
		size_t extents_npages = atomic_load_zu(&eset->npages,
		    ATOMIC_RELAXED);
		if (extents_npages <= npages_min) {
			extent = NULL;
			goto label_return;
		}
		eset_remove_locked(tsdn, eset, extent);
		if (!eset->delay_coalesce) {
			break;
		}
		/* Try to coalesce. */
		if (extent_try_delayed_coalesce(tsdn, arena, r_extent_hooks,
		    rtree_ctx, eset, extent)) {
			break;
		}
		/*
		 * The LRU extent was just coalesced and the result placed in
		 * the LRU at its neighbor's position.  Start over.
		 */
	}

	/*
	 * Either mark the extent active or deregister it to protect against
	 * concurrent operations.
	 */
	switch (eset_state_get(eset)) {
	case extent_state_active:
		not_reached();
	case extent_state_dirty:
	case extent_state_muzzy:
		extent_state_set(extent, extent_state_active);
		break;
	case extent_state_retained:
		extent_deregister(tsdn, extent);
		break;
	default:
		not_reached();
	}

label_return:
	malloc_mutex_unlock(tsdn, &eset->mtx);
	return extent;
}