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
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_split_interior_result_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 uintptr_t ALIGNMENT_CEILING (uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NSIZES ; 
 size_t PAGE ; 
 int /*<<< orphan*/  PAGE_CEILING (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ extent_addr_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_base_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_past_get (int /*<<< orphan*/ *) ; 
 size_t extent_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_split_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  extent_split_interior_cant_alloc ; 
 int /*<<< orphan*/  extent_split_interior_error ; 
 int /*<<< orphan*/  extent_split_interior_ok ; 
 int /*<<< orphan*/  extent_szind_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extents_rtree ; 
 int /*<<< orphan*/  rtree_szind_slab_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,uintptr_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static extent_split_interior_result_t
extent_split_interior(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, rtree_ctx_t *rtree_ctx,
    /* The result of splitting, in case of success. */
    extent_t **extent, extent_t **lead, extent_t **trail,
    /* The mess to clean up, in case of error. */
    extent_t **to_leak, extent_t **to_salvage,
    void *new_addr, size_t size, size_t pad, size_t alignment, bool slab,
    szind_t szind, bool growing_retained) {
	size_t esize = size + pad;
	size_t leadsize = ALIGNMENT_CEILING((uintptr_t)extent_base_get(*extent),
	    PAGE_CEILING(alignment)) - (uintptr_t)extent_base_get(*extent);
	assert(new_addr == NULL || leadsize == 0);
	if (extent_size_get(*extent) < leadsize + esize) {
		return extent_split_interior_cant_alloc;
	}
	size_t trailsize = extent_size_get(*extent) - leadsize - esize;

	*lead = NULL;
	*trail = NULL;
	*to_leak = NULL;
	*to_salvage = NULL;

	/* Split the lead. */
	if (leadsize != 0) {
		*lead = *extent;
		*extent = extent_split_impl(tsdn, arena, r_extent_hooks,
		    *lead, leadsize, NSIZES, false, esize + trailsize, szind,
		    slab, growing_retained);
		if (*extent == NULL) {
			*to_leak = *lead;
			*lead = NULL;
			return extent_split_interior_error;
		}
	}

	/* Split the trail. */
	if (trailsize != 0) {
		*trail = extent_split_impl(tsdn, arena, r_extent_hooks, *extent,
		    esize, szind, slab, trailsize, NSIZES, false,
		    growing_retained);
		if (*trail == NULL) {
			*to_leak = *extent;
			*to_salvage = *lead;
			*lead = NULL;
			*extent = NULL;
			return extent_split_interior_error;
		}
	}

	if (leadsize == 0 && trailsize == 0) {
		/*
		 * Splitting causes szind to be set as a side effect, but no
		 * splitting occurred.
		 */
		extent_szind_set(*extent, szind);
		if (szind != NSIZES) {
			rtree_szind_slab_update(tsdn, &extents_rtree, rtree_ctx,
			    (uintptr_t)extent_addr_get(*extent), szind, slab);
			if (slab && extent_size_get(*extent) > PAGE) {
				rtree_szind_slab_update(tsdn, &extents_rtree,
				    rtree_ctx,
				    (uintptr_t)extent_past_get(*extent) -
				    (uintptr_t)PAGE, szind, slab);
			}
		}
	}

	return extent_split_interior_ok;
}