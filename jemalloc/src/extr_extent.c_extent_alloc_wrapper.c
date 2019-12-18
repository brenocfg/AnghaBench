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
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * extent_alloc_retained (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,void*,size_t,size_t,size_t,int,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/ * extent_alloc_wrapper_hard (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,void*,size_t,size_t,size_t,int,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ extent_dumpable_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_hooks_assure_initialized (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ opt_retain ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

extent_t *
extent_alloc_wrapper(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, void *new_addr, size_t size, size_t pad,
    size_t alignment, bool slab, szind_t szind, bool *zero, bool *commit) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	extent_hooks_assure_initialized(arena, r_extent_hooks);

	extent_t *extent = extent_alloc_retained(tsdn, arena, r_extent_hooks,
	    new_addr, size, pad, alignment, slab, szind, zero, commit);
	if (extent == NULL) {
		if (opt_retain && new_addr != NULL) {
			/*
			 * When retain is enabled and new_addr is set, we do not
			 * attempt extent_alloc_wrapper_hard which does mmap
			 * that is very unlikely to succeed (unless it happens
			 * to be at the end).
			 */
			return NULL;
		}
		extent = extent_alloc_wrapper_hard(tsdn, arena, r_extent_hooks,
		    new_addr, size, pad, alignment, slab, szind, zero, commit);
	}

	assert(extent == NULL || extent_dumpable_get(extent));
	return extent;
}