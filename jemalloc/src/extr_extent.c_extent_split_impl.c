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
typedef  int /*<<< orphan*/  szind_t ;
typedef  int /*<<< orphan*/  rtree_leaf_elm_t ;
typedef  int /*<<< orphan*/  rtree_ctx_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_6__ {int (* split ) (TYPE_1__*,scalar_t__,size_t,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_NOT_HEAD ; 
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 int /*<<< orphan*/  arena_ind_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* extent_addr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ extent_base_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_committed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_dalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_dumpable_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hook_post_reentrancy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hook_pre_reentrancy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hooks_assure_initialized (int /*<<< orphan*/ *,TYPE_1__**) ; 
 TYPE_1__ extent_hooks_default ; 
 int /*<<< orphan*/  extent_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_lock2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_rtree_leaf_elms_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  extent_rtree_write_acquired (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t extent_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_size_set (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  extent_sn_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_state_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_szind_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_unlock2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_zeroed_get (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,scalar_t__,size_t,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tsdn_rtree_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static extent_t *
extent_split_impl(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent, size_t size_a,
    szind_t szind_a, bool slab_a, size_t size_b, szind_t szind_b, bool slab_b,
    bool growing_retained) {
	assert(extent_size_get(extent) == size_a + size_b);
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, growing_retained ? 1 : 0);

	extent_hooks_assure_initialized(arena, r_extent_hooks);

	if ((*r_extent_hooks)->split == NULL) {
		return NULL;
	}

	extent_t *trail = extent_alloc(tsdn, arena);
	if (trail == NULL) {
		goto label_error_a;
	}

	extent_init(trail, arena_ind_get(arena),
	    (void *)((uintptr_t)extent_base_get(extent) + size_a), size_b,
	    slab_b, szind_b, extent_sn_get(extent), extent_state_get(extent),
	    extent_zeroed_get(extent), extent_committed_get(extent),
	    extent_dumpable_get(extent), EXTENT_NOT_HEAD);

	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);
	rtree_leaf_elm_t *lead_elm_a, *lead_elm_b;
	{
		extent_t lead;

		extent_init(&lead, arena_ind_get(arena),
		    extent_addr_get(extent), size_a,
		    slab_a, szind_a, extent_sn_get(extent),
		    extent_state_get(extent), extent_zeroed_get(extent),
		    extent_committed_get(extent), extent_dumpable_get(extent),
		    EXTENT_NOT_HEAD);

		extent_rtree_leaf_elms_lookup(tsdn, rtree_ctx, &lead, false,
		    true, &lead_elm_a, &lead_elm_b);
	}
	rtree_leaf_elm_t *trail_elm_a, *trail_elm_b;
	extent_rtree_leaf_elms_lookup(tsdn, rtree_ctx, trail, false, true,
	    &trail_elm_a, &trail_elm_b);

	if (lead_elm_a == NULL || lead_elm_b == NULL || trail_elm_a == NULL
	    || trail_elm_b == NULL) {
		goto label_error_b;
	}

	extent_lock2(tsdn, extent, trail);

	if (*r_extent_hooks != &extent_hooks_default) {
		extent_hook_pre_reentrancy(tsdn, arena);
	}
	bool err = (*r_extent_hooks)->split(*r_extent_hooks, extent_base_get(extent),
	    size_a + size_b, size_a, size_b, extent_committed_get(extent),
	    arena_ind_get(arena));
	if (*r_extent_hooks != &extent_hooks_default) {
		extent_hook_post_reentrancy(tsdn);
	}
	if (err) {
		goto label_error_c;
	}

	extent_size_set(extent, size_a);
	extent_szind_set(extent, szind_a);

	extent_rtree_write_acquired(tsdn, lead_elm_a, lead_elm_b, extent,
	    szind_a, slab_a);
	extent_rtree_write_acquired(tsdn, trail_elm_a, trail_elm_b, trail,
	    szind_b, slab_b);

	extent_unlock2(tsdn, extent, trail);

	return trail;
label_error_c:
	extent_unlock2(tsdn, extent, trail);
label_error_b:
	extent_dalloc(tsdn, arena, trail);
label_error_a:
	return NULL;
}