#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  eset_t ;
typedef  int /*<<< orphan*/  arena_t ;
struct TYPE_5__ {int /*<<< orphan*/  mtx; } ;
typedef  TYPE_1__ arena_decay_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_decay_ms_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arena_decay_reinit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arena_maybe_decay (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
arena_decay_ms_set(tsdn_t *tsdn, arena_t *arena, arena_decay_t *decay,
    eset_t *eset, ssize_t decay_ms) {
	if (!arena_decay_ms_valid(decay_ms)) {
		return true;
	}

	malloc_mutex_lock(tsdn, &decay->mtx);
	/*
	 * Restart decay backlog from scratch, which may cause many dirty pages
	 * to be immediately purged.  It would conceptually be possible to map
	 * the old backlog onto the new backlog, but there is no justification
	 * for such complexity since decay_ms changes are intended to be
	 * infrequent, either between the {-1, 0, >0} states, or a one-time
	 * arbitrary change during initial arena configuration.
	 */
	arena_decay_reinit(decay, decay_ms);
	arena_maybe_decay(tsdn, arena, decay, eset, false);
	malloc_mutex_unlock(tsdn, &decay->mtx);

	return false;
}