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
typedef  int /*<<< orphan*/  rtree_leaf_elm_t ;
typedef  int /*<<< orphan*/  rtree_ctx_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_6__ {int (* merge ) (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ;} ;
typedef  TYPE_1__ extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  SC_NSIZES ; 
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 scalar_t__ arena_ind_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ extent_arena_ind_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_base_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_committed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_dalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ extent_head_no_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hook_post_reentrancy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hook_pre_reentrancy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hooks_assure_initialized (int /*<<< orphan*/ *,TYPE_1__**) ; 
 TYPE_1__ extent_hooks_default ; 
 int /*<<< orphan*/  extent_lock2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int extent_merge_default_impl (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  extent_rtree_leaf_elms_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  extent_rtree_write_acquired (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ extent_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_size_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ extent_sn_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_sn_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  extent_szind_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_unlock2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ extent_zeroed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_zeroed_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  extents_rtree ; 
 int /*<<< orphan*/  rtree_leaf_elm_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * tsdn_rtree_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
extent_merge_impl(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *a, extent_t *b,
    bool growing_retained) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, growing_retained ? 1 : 0);
	assert(extent_base_get(a) < extent_base_get(b));

	extent_hooks_assure_initialized(arena, r_extent_hooks);

	if ((*r_extent_hooks)->merge == NULL || extent_head_no_merge(a, b)) {
		return true;
	}

	bool err;
	if (*r_extent_hooks == &extent_hooks_default) {
		/* Call directly to propagate tsdn. */
		err = extent_merge_default_impl(extent_base_get(a),
		    extent_base_get(b));
	} else {
		extent_hook_pre_reentrancy(tsdn, arena);
		err = (*r_extent_hooks)->merge(*r_extent_hooks,
		    extent_base_get(a), extent_size_get(a), extent_base_get(b),
		    extent_size_get(b), extent_committed_get(a),
		    arena_ind_get(arena));
		extent_hook_post_reentrancy(tsdn);
	}

	if (err) {
		return true;
	}

	/*
	 * The rtree writes must happen while all the relevant elements are
	 * owned, so the following code uses decomposed helper functions rather
	 * than extent_{,de}register() to do things in the right order.
	 */
	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);
	rtree_leaf_elm_t *a_elm_a, *a_elm_b, *b_elm_a, *b_elm_b;
	extent_rtree_leaf_elms_lookup(tsdn, rtree_ctx, a, true, false, &a_elm_a,
	    &a_elm_b);
	extent_rtree_leaf_elms_lookup(tsdn, rtree_ctx, b, true, false, &b_elm_a,
	    &b_elm_b);

	extent_lock2(tsdn, a, b);

	if (a_elm_b != NULL) {
		rtree_leaf_elm_write(tsdn, &extents_rtree, a_elm_b, NULL,
		    SC_NSIZES, false);
	}
	if (b_elm_b != NULL) {
		rtree_leaf_elm_write(tsdn, &extents_rtree, b_elm_a, NULL,
		    SC_NSIZES, false);
	} else {
		b_elm_b = b_elm_a;
	}

	extent_size_set(a, extent_size_get(a) + extent_size_get(b));
	extent_szind_set(a, SC_NSIZES);
	extent_sn_set(a, (extent_sn_get(a) < extent_sn_get(b)) ?
	    extent_sn_get(a) : extent_sn_get(b));
	extent_zeroed_set(a, extent_zeroed_get(a) && extent_zeroed_get(b));

	extent_rtree_write_acquired(tsdn, a_elm_a, b_elm_b, a, SC_NSIZES,
	    false);

	extent_unlock2(tsdn, a, b);

	/*
	 * If we got here, we merged the extents; so they must be from the same
	 * arena (i.e. this one).
	 */
	assert(extent_arena_ind_get(b) == arena_ind_get(arena));
	extent_dalloc(tsdn, arena, b);

	return false;
}