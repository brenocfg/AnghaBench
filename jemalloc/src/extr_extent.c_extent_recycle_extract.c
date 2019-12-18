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
struct TYPE_6__ {int /*<<< orphan*/  mtx; } ;
typedef  TYPE_1__ eset_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 size_t PAGE ; 
 void* PAGE_ADDR2BASE (void*) ; 
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 scalar_t__ arena_ind_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_debug ; 
 int /*<<< orphan*/ * eset_fit_locked (int /*<<< orphan*/ *,TYPE_1__*,size_t,size_t) ; 
 scalar_t__ eset_state_get (TYPE_1__*) ; 
 int /*<<< orphan*/  extent_activate_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ extent_arena_ind_get (int /*<<< orphan*/ *) ; 
 void* extent_base_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hooks_assure_initialized (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * extent_lock_from_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 
 size_t extent_size_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_state_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static extent_t *
extent_recycle_extract(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, rtree_ctx_t *rtree_ctx, eset_t *eset,
    void *new_addr, size_t size, size_t pad, size_t alignment, bool slab,
    bool growing_retained) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, growing_retained ? 1 : 0);
	assert(alignment > 0);
	if (config_debug && new_addr != NULL) {
		/*
		 * Non-NULL new_addr has two use cases:
		 *
		 *   1) Recycle a known-extant extent, e.g. during purging.
		 *   2) Perform in-place expanding reallocation.
		 *
		 * Regardless of use case, new_addr must either refer to a
		 * non-existing extent, or to the base of an extant extent,
		 * since only active slabs support interior lookups (which of
		 * course cannot be recycled).
		 */
		assert(PAGE_ADDR2BASE(new_addr) == new_addr);
		assert(pad == 0);
		assert(alignment <= PAGE);
	}

	size_t esize = size + pad;
	malloc_mutex_lock(tsdn, &eset->mtx);
	extent_hooks_assure_initialized(arena, r_extent_hooks);
	extent_t *extent;
	if (new_addr != NULL) {
		extent = extent_lock_from_addr(tsdn, rtree_ctx, new_addr,
		    false);
		if (extent != NULL) {
			/*
			 * We might null-out extent to report an error, but we
			 * still need to unlock the associated mutex after.
			 */
			extent_t *unlock_extent = extent;
			assert(extent_base_get(extent) == new_addr);
			if (extent_arena_ind_get(extent)
			    != arena_ind_get(arena) ||
			    extent_size_get(extent) < esize ||
			    extent_state_get(extent) !=
			    eset_state_get(eset)) {
				extent = NULL;
			}
			extent_unlock(tsdn, unlock_extent);
		}
	} else {
		extent = eset_fit_locked(tsdn, eset, esize, alignment);
	}
	if (extent == NULL) {
		malloc_mutex_unlock(tsdn, &eset->mtx);
		return NULL;
	}

	extent_activate_locked(tsdn, arena, eset, extent);
	malloc_mutex_unlock(tsdn, &eset->mtx);

	return extent;
}