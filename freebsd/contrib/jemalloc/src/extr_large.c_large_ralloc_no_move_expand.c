#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  szind_t ;
typedef  int /*<<< orphan*/  rtree_ctx_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_15__ {int /*<<< orphan*/ * merge; } ;
typedef  TYPE_1__ extent_hooks_t ;
struct TYPE_16__ {int /*<<< orphan*/  stats; int /*<<< orphan*/  extents_muzzy; int /*<<< orphan*/  extents_dirty; } ;
typedef  TYPE_2__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  CACHELINE ; 
 int /*<<< orphan*/  JEMALLOC_ALLOC_JUNK ; 
 int /*<<< orphan*/  NSIZES ; 
 scalar_t__ PAGE ; 
 void* PAGE_ADDR2BASE (void*) ; 
 int /*<<< orphan*/  arena_extent_ralloc_large_expand (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  arena_stats_mapped_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_cache_oblivious ; 
 scalar_t__ config_fill ; 
 scalar_t__ config_stats ; 
 scalar_t__ extent_addr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_alloc_wrapper (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__**,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int*) ; 
 TYPE_2__* extent_arena_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_dalloc_wrapper (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__**,int /*<<< orphan*/ *) ; 
 TYPE_1__* extent_hooks_get (TYPE_2__*) ; 
 scalar_t__ extent_merge_wrapper (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_past_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_szind_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t extent_usize_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extents_alloc (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  extents_rtree ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  opt_junk_alloc ; 
 int /*<<< orphan*/  opt_zero ; 
 int /*<<< orphan*/  rtree_szind_slab_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,uintptr_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sz_size2index (size_t) ; 
 int /*<<< orphan*/ * tsdn_rtree_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
large_ralloc_no_move_expand(tsdn_t *tsdn, extent_t *extent, size_t usize,
    bool zero) {
	arena_t *arena = extent_arena_get(extent);
	size_t oldusize = extent_usize_get(extent);
	extent_hooks_t *extent_hooks = extent_hooks_get(arena);
	size_t trailsize = usize - oldusize;

	if (extent_hooks->merge == NULL) {
		return true;
	}

	if (config_fill && unlikely(opt_zero)) {
		zero = true;
	}
	/*
	 * Copy zero into is_zeroed_trail and pass the copy when allocating the
	 * extent, so that it is possible to make correct junk/zero fill
	 * decisions below, even if is_zeroed_trail ends up true when zero is
	 * false.
	 */
	bool is_zeroed_trail = zero;
	bool commit = true;
	extent_t *trail;
	bool new_mapping;
	if ((trail = extents_alloc(tsdn, arena, &extent_hooks,
	    &arena->extents_dirty, extent_past_get(extent), trailsize, 0,
	    CACHELINE, false, NSIZES, &is_zeroed_trail, &commit)) != NULL
	    || (trail = extents_alloc(tsdn, arena, &extent_hooks,
	    &arena->extents_muzzy, extent_past_get(extent), trailsize, 0,
	    CACHELINE, false, NSIZES, &is_zeroed_trail, &commit)) != NULL) {
		if (config_stats) {
			new_mapping = false;
		}
	} else {
		if ((trail = extent_alloc_wrapper(tsdn, arena, &extent_hooks,
		    extent_past_get(extent), trailsize, 0, CACHELINE, false,
		    NSIZES, &is_zeroed_trail, &commit)) == NULL) {
			return true;
		}
		if (config_stats) {
			new_mapping = true;
		}
	}

	if (extent_merge_wrapper(tsdn, arena, &extent_hooks, extent, trail)) {
		extent_dalloc_wrapper(tsdn, arena, &extent_hooks, trail);
		return true;
	}
	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);
	szind_t szind = sz_size2index(usize);
	extent_szind_set(extent, szind);
	rtree_szind_slab_update(tsdn, &extents_rtree, rtree_ctx,
	    (uintptr_t)extent_addr_get(extent), szind, false);

	if (config_stats && new_mapping) {
		arena_stats_mapped_add(tsdn, &arena->stats, trailsize);
	}

	if (zero) {
		if (config_cache_oblivious) {
			/*
			 * Zero the trailing bytes of the original allocation's
			 * last page, since they are in an indeterminate state.
			 * There will always be trailing bytes, because ptr's
			 * offset from the beginning of the extent is a multiple
			 * of CACHELINE in [0 .. PAGE).
			 */
			void *zbase = (void *)
			    ((uintptr_t)extent_addr_get(extent) + oldusize);
			void *zpast = PAGE_ADDR2BASE((void *)((uintptr_t)zbase +
			    PAGE));
			size_t nzero = (uintptr_t)zpast - (uintptr_t)zbase;
			assert(nzero > 0);
			memset(zbase, 0, nzero);
		}
		assert(is_zeroed_trail);
	} else if (config_fill && unlikely(opt_junk_alloc)) {
		memset((void *)((uintptr_t)extent_addr_get(extent) + oldusize),
		    JEMALLOC_ALLOC_JUNK, usize - oldusize);
	}

	arena_extent_ralloc_large_expand(tsdn, arena, extent, oldusize);

	return false;
}