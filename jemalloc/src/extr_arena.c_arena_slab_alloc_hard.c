#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_6__ {int /*<<< orphan*/  slab_size; } ;
typedef  TYPE_1__ bin_info_t ;
struct TYPE_7__ {int /*<<< orphan*/  stats; } ;
typedef  TYPE_2__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE ; 
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 int /*<<< orphan*/  arena_stats_mapped_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ config_stats ; 
 int /*<<< orphan*/ * extent_alloc_wrapper (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static extent_t *
arena_slab_alloc_hard(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, const bin_info_t *bin_info,
    szind_t szind) {
	extent_t *slab;
	bool zero, commit;

	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	zero = false;
	commit = true;
	slab = extent_alloc_wrapper(tsdn, arena, r_extent_hooks, NULL,
	    bin_info->slab_size, 0, PAGE, true, szind, &zero, &commit);

	if (config_stats && slab != NULL) {
		arena_stats_mapped_add(tsdn, &arena->stats,
		    bin_info->slab_size);
	}

	return slab;
}