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
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 scalar_t__ arena_dirty_decay_ms_default_get () ; 
 int /*<<< orphan*/  arena_dirty_decay_ms_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * arena_get (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ arena_muzzy_decay_ms_default_get () ; 
 int /*<<< orphan*/  arena_muzzy_decay_ms_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ huge_arena_ind ; 
 int /*<<< orphan*/  malloc_initialized () ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

arena_t *
arena_choose_huge(tsd_t *tsd) {
	/* huge_arena_ind can be 0 during init (will use a0). */
	if (huge_arena_ind == 0) {
		assert(!malloc_initialized());
	}

	arena_t *huge_arena = arena_get(tsd_tsdn(tsd), huge_arena_ind, false);
	if (huge_arena == NULL) {
		/* Create the huge arena on demand. */
		assert(huge_arena_ind != 0);
		huge_arena = arena_get(tsd_tsdn(tsd), huge_arena_ind, true);
		if (huge_arena == NULL) {
			return NULL;
		}
		/*
		 * Purge eagerly for huge allocations, because: 1) number of
		 * huge allocations is usually small, which means ticker based
		 * decay is not reliable; and 2) less immediate reuse is
		 * expected for huge allocations.
		 */
		if (arena_dirty_decay_ms_default_get() > 0) {
			arena_dirty_decay_ms_set(tsd_tsdn(tsd), huge_arena, 0);
		}
		if (arena_muzzy_decay_ms_default_get() > 0) {
			arena_muzzy_decay_ms_set(tsd_tsdn(tsd), huge_arena, 0);
		}
	}

	return huge_arena;
}