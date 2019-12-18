#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_list_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  eset_t ;
typedef  int /*<<< orphan*/  arena_t ;
struct TYPE_4__ {int purging; int /*<<< orphan*/  mtx; } ;
typedef  TYPE_1__ arena_decay_t ;

/* Variables and functions */
 int /*<<< orphan*/  WITNESS_RANK_CORE ; 
 size_t arena_decay_stashed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 size_t arena_stash_decayed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * extent_hooks_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsdn_witness_tsdp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  witness_assert_depth_to_rank (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
arena_decay_to_limit(tsdn_t *tsdn, arena_t *arena, arena_decay_t *decay,
    eset_t *eset, bool all, size_t npages_limit, size_t npages_decay_max,
    bool is_background_thread) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 1);
	malloc_mutex_assert_owner(tsdn, &decay->mtx);

	if (decay->purging || npages_decay_max == 0) {
		return;
	}
	decay->purging = true;
	malloc_mutex_unlock(tsdn, &decay->mtx);

	extent_hooks_t *extent_hooks = extent_hooks_get(arena);

	extent_list_t decay_extents;
	extent_list_init(&decay_extents);

	size_t npurge = arena_stash_decayed(tsdn, arena, &extent_hooks, eset,
	    npages_limit, npages_decay_max, &decay_extents);
	if (npurge != 0) {
		size_t npurged = arena_decay_stashed(tsdn, arena,
		    &extent_hooks, decay, eset, all, &decay_extents,
		    is_background_thread);
		assert(npurged == npurge);
	}

	malloc_mutex_lock(tsdn, &decay->mtx);
	decay->purging = false;
}