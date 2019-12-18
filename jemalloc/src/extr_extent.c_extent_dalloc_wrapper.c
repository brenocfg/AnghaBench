#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_16__ {int /*<<< orphan*/  (* purge_lazy ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* purge_forced ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ extent_hooks_t ;
struct TYPE_17__ {int /*<<< orphan*/  eset_retained; } ;
typedef  TYPE_2__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 int /*<<< orphan*/  arena_ind_get (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ config_prof ; 
 int /*<<< orphan*/  extent_base_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_committed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_dalloc_wrapper_try (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_decommit_wrapper (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_deregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_dumpable_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_gdump_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hook_post_reentrancy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hook_pre_reentrancy (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__ extent_hooks_default ; 
 scalar_t__ extent_may_dalloc () ; 
 int /*<<< orphan*/  extent_record (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  extent_reregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_size_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_state_get (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_state_muzzy ; 
 int /*<<< orphan*/  extent_zeroed_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
extent_dalloc_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent) {
	assert(extent_dumpable_get(extent));
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	/* Avoid calling the default extent_dalloc unless have to. */
	if (*r_extent_hooks != &extent_hooks_default || extent_may_dalloc()) {
		/*
		 * Deregister first to avoid a race with other allocating
		 * threads, and reregister if deallocation fails.
		 */
		extent_deregister(tsdn, extent);
		if (!extent_dalloc_wrapper_try(tsdn, arena, r_extent_hooks,
		    extent)) {
			return;
		}
		extent_reregister(tsdn, extent);
	}

	if (*r_extent_hooks != &extent_hooks_default) {
		extent_hook_pre_reentrancy(tsdn, arena);
	}
	/* Try to decommit; purge if that fails. */
	bool zeroed;
	if (!extent_committed_get(extent)) {
		zeroed = true;
	} else if (!extent_decommit_wrapper(tsdn, arena, r_extent_hooks, extent,
	    0, extent_size_get(extent))) {
		zeroed = true;
	} else if ((*r_extent_hooks)->purge_forced != NULL &&
	    !(*r_extent_hooks)->purge_forced(*r_extent_hooks,
	    extent_base_get(extent), extent_size_get(extent), 0,
	    extent_size_get(extent), arena_ind_get(arena))) {
		zeroed = true;
	} else if (extent_state_get(extent) == extent_state_muzzy ||
	    ((*r_extent_hooks)->purge_lazy != NULL &&
	    !(*r_extent_hooks)->purge_lazy(*r_extent_hooks,
	    extent_base_get(extent), extent_size_get(extent), 0,
	    extent_size_get(extent), arena_ind_get(arena)))) {
		zeroed = false;
	} else {
		zeroed = false;
	}
	if (*r_extent_hooks != &extent_hooks_default) {
		extent_hook_post_reentrancy(tsdn);
	}
	extent_zeroed_set(extent, zeroed);

	if (config_prof) {
		extent_gdump_sub(tsdn, extent);
	}

	extent_record(tsdn, arena, r_extent_hooks, &arena->eset_retained,
	    extent, false);
}