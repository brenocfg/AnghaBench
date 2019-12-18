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
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  eset_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  extent_addr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_base_get (int /*<<< orphan*/ *) ; 
 int extent_dumpable_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_record (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ extent_size_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_zeroed_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
extents_dalloc(tsdn_t *tsdn, arena_t *arena, extent_hooks_t **r_extent_hooks,
    eset_t *eset, extent_t *extent) {
	assert(extent_base_get(extent) != NULL);
	assert(extent_size_get(extent) != 0);
	assert(extent_dumpable_get(extent));
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	extent_addr_set(extent, extent_base_get(extent));
	extent_zeroed_set(extent, false);

	extent_record(tsdn, arena, r_extent_hooks, eset, extent, false);
}