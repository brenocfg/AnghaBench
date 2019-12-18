#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  rtree_ctx_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_14__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  delay_coalesce; } ;
typedef  TYPE_1__ eset_t ;
struct TYPE_15__ {TYPE_1__ eset_dirty; } ;
typedef  TYPE_2__ arena_t ;

/* Variables and functions */
 scalar_t__ SC_LARGE_MINCLASS ; 
 int /*<<< orphan*/  SC_NSIZES ; 
 int /*<<< orphan*/  arena_decay_extent (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ eset_state_get (TYPE_1__*) ; 
 scalar_t__ extent_base_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_deactivate_locked (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hooks_assure_initialized (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  extent_interior_deregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ extent_size_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_slab_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_slab_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ extent_state_active ; 
 scalar_t__ extent_state_dirty ; 
 scalar_t__ extent_state_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_state_muzzy ; 
 int /*<<< orphan*/  extent_szind_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * extent_try_coalesce (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * extent_try_coalesce_large (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  extent_zeroed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extents_rtree ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ oversize_threshold ; 
 int /*<<< orphan*/ * rtree_extent_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,uintptr_t,int) ; 
 int /*<<< orphan*/ * tsdn_rtree_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
extent_record(tsdn_t *tsdn, arena_t *arena, extent_hooks_t **r_extent_hooks,
    eset_t *eset, extent_t *extent, bool growing_retained) {
	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);

	assert((eset_state_get(eset) != extent_state_dirty &&
	    eset_state_get(eset) != extent_state_muzzy) ||
	    !extent_zeroed_get(extent));

	malloc_mutex_lock(tsdn, &eset->mtx);
	extent_hooks_assure_initialized(arena, r_extent_hooks);

	extent_szind_set(extent, SC_NSIZES);
	if (extent_slab_get(extent)) {
		extent_interior_deregister(tsdn, rtree_ctx, extent);
		extent_slab_set(extent, false);
	}

	assert(rtree_extent_read(tsdn, &extents_rtree, rtree_ctx,
	    (uintptr_t)extent_base_get(extent), true) == extent);

	if (!eset->delay_coalesce) {
		extent = extent_try_coalesce(tsdn, arena, r_extent_hooks,
		    rtree_ctx, eset, extent, NULL, growing_retained);
	} else if (extent_size_get(extent) >= SC_LARGE_MINCLASS) {
		assert(eset == &arena->eset_dirty);
		/* Always coalesce large eset eagerly. */
		bool coalesced;
		do {
			assert(extent_state_get(extent) == extent_state_active);
			extent = extent_try_coalesce_large(tsdn, arena,
			    r_extent_hooks, rtree_ctx, eset, extent,
			    &coalesced, growing_retained);
		} while (coalesced);
		if (extent_size_get(extent) >= oversize_threshold) {
			/* Shortcut to purge the oversize extent eagerly. */
			malloc_mutex_unlock(tsdn, &eset->mtx);
			arena_decay_extent(tsdn, arena, r_extent_hooks, extent);
			return;
		}
	}
	extent_deactivate_locked(tsdn, arena, eset, extent);

	malloc_mutex_unlock(tsdn, &eset->mtx);
}