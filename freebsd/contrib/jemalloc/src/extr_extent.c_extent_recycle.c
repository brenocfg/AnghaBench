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
typedef  int /*<<< orphan*/  szind_t ;
typedef  int /*<<< orphan*/  rtree_ctx_t ;
typedef  int /*<<< orphan*/  extents_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int PAGE ; 
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_debug ; 
 int /*<<< orphan*/  extent_addr_randomize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 void* extent_base_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_commit_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ extent_committed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_interior_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_record (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * extent_recycle_extract (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t,size_t,size_t,int,int) ; 
 int /*<<< orphan*/ * extent_recycle_split (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t,size_t,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 size_t extent_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_slab_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ extent_state_active ; 
 scalar_t__ extent_state_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_zeroed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_zeroed_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ pages_purge_forced (void*,size_t) ; 
 int /*<<< orphan*/ * tsdn_rtree_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static extent_t *
extent_recycle(tsdn_t *tsdn, arena_t *arena, extent_hooks_t **r_extent_hooks,
    extents_t *extents, void *new_addr, size_t size, size_t pad,
    size_t alignment, bool slab, szind_t szind, bool *zero, bool *commit,
    bool growing_retained) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, growing_retained ? 1 : 0);
	assert(new_addr == NULL || !slab);
	assert(pad == 0 || !slab);
	assert(!*zero || !slab);

	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);

	extent_t *extent = extent_recycle_extract(tsdn, arena, r_extent_hooks,
	    rtree_ctx, extents, new_addr, size, pad, alignment, slab,
	    growing_retained);
	if (extent == NULL) {
		return NULL;
	}

	extent = extent_recycle_split(tsdn, arena, r_extent_hooks, rtree_ctx,
	    extents, new_addr, size, pad, alignment, slab, szind, extent,
	    growing_retained);
	if (extent == NULL) {
		return NULL;
	}

	if (*commit && !extent_committed_get(extent)) {
		if (extent_commit_impl(tsdn, arena, r_extent_hooks, extent,
		    0, extent_size_get(extent), growing_retained)) {
			extent_record(tsdn, arena, r_extent_hooks, extents,
			    extent, growing_retained);
			return NULL;
		}
		extent_zeroed_set(extent, true);
	}

	if (extent_committed_get(extent)) {
		*commit = true;
	}
	if (extent_zeroed_get(extent)) {
		*zero = true;
	}

	if (pad != 0) {
		extent_addr_randomize(tsdn, extent, alignment);
	}
	assert(extent_state_get(extent) == extent_state_active);
	if (slab) {
		extent_slab_set(extent, slab);
		extent_interior_register(tsdn, rtree_ctx, extent, szind);
	}

	if (*zero) {
		void *addr = extent_base_get(extent);
		if (!extent_zeroed_get(extent)) {
			size_t size = extent_size_get(extent);
			if (pages_purge_forced(addr, size)) {
				memset(addr, 0, size);
			}
		} else if (config_debug) {
			size_t *p = (size_t *)(uintptr_t)addr;
			/* Check the first page only. */
			for (size_t i = 0; i < PAGE / sizeof(size_t); i++) {
				assert(p[i] == 0);
			}
		}
	}
	return extent;
}