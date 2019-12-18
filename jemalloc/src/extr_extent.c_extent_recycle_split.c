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
typedef  scalar_t__ extent_split_interior_result_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  eset_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 void* extent_base_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_deactivate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_deregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_deregister_no_gdump_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_lock_from_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 
 scalar_t__ extent_split_interior (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,void*,size_t,size_t,size_t,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ extent_split_interior_error ; 
 scalar_t__ extent_split_interior_ok ; 
 int /*<<< orphan*/  extents_abandon_vm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  maps_coalesce ; 
 int /*<<< orphan*/  opt_retain ; 
 int /*<<< orphan*/  unreachable () ; 

__attribute__((used)) static extent_t *
extent_recycle_split(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, rtree_ctx_t *rtree_ctx, eset_t *eset,
    void *new_addr, size_t size, size_t pad, size_t alignment, bool slab,
    szind_t szind, extent_t *extent, bool growing_retained) {
	extent_t *lead;
	extent_t *trail;
	extent_t *to_leak;
	extent_t *to_salvage;

	extent_split_interior_result_t result = extent_split_interior(
	    tsdn, arena, r_extent_hooks, rtree_ctx, &extent, &lead, &trail,
	    &to_leak, &to_salvage, new_addr, size, pad, alignment, slab, szind,
	    growing_retained);

	if (!maps_coalesce && result != extent_split_interior_ok
	    && !opt_retain) {
		/*
		 * Split isn't supported (implies Windows w/o retain).  Avoid
		 * leaking the eset.
		 */
		assert(to_leak != NULL && lead == NULL && trail == NULL);
		extent_deactivate(tsdn, arena, eset, to_leak);
		return NULL;
	}

	if (result == extent_split_interior_ok) {
		if (lead != NULL) {
			extent_deactivate(tsdn, arena, eset, lead);
		}
		if (trail != NULL) {
			extent_deactivate(tsdn, arena, eset, trail);
		}
		return extent;
	} else {
		/*
		 * We should have picked an extent that was large enough to
		 * fulfill our allocation request.
		 */
		assert(result == extent_split_interior_error);
		if (to_salvage != NULL) {
			extent_deregister(tsdn, to_salvage);
		}
		if (to_leak != NULL) {
			void *leak = extent_base_get(to_leak);
			extent_deregister_no_gdump_sub(tsdn, to_leak);
			extents_abandon_vm(tsdn, arena, r_extent_hooks, eset,
			    to_leak, growing_retained);
			assert(extent_lock_from_addr(tsdn, rtree_ctx, leak,
			    false) == NULL);
		}
		return NULL;
	}
	unreachable();
}