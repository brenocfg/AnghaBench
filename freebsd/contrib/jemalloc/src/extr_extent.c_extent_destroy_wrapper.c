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
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* destroy ) (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 int /*<<< orphan*/  arena_ind_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  extent_addr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_base_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_committed_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_dalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_deregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_destroy_default_impl (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  extent_hook_post_reentrancy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hook_pre_reentrancy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hooks_assure_initialized (int /*<<< orphan*/ *,TYPE_1__**) ; 
 TYPE_1__ extent_hooks_default ; 
 scalar_t__ extent_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
extent_destroy_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *extent) {
	assert(extent_base_get(extent) != NULL);
	assert(extent_size_get(extent) != 0);
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	/* Deregister first to avoid a race with other allocating threads. */
	extent_deregister(tsdn, extent);

	extent_addr_set(extent, extent_base_get(extent));

	extent_hooks_assure_initialized(arena, r_extent_hooks);
	/* Try to destroy; silently fail otherwise. */
	if (*r_extent_hooks == &extent_hooks_default) {
		/* Call directly to propagate tsdn. */
		extent_destroy_default_impl(extent_base_get(extent),
		    extent_size_get(extent));
	} else if ((*r_extent_hooks)->destroy != NULL) {
		extent_hook_pre_reentrancy(tsdn, arena);
		(*r_extent_hooks)->destroy(*r_extent_hooks,
		    extent_base_get(extent), extent_size_get(extent),
		    extent_committed_get(extent), arena_ind_get(arena));
		extent_hook_post_reentrancy(tsdn);
	}

	extent_dalloc(tsdn, arena, extent);
}