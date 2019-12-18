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
typedef  int /*<<< orphan*/  eset_t ;
typedef  int /*<<< orphan*/  arena_t ;
struct TYPE_6__ {size_t* backlog; int /*<<< orphan*/  mtx; } ;
typedef  TYPE_1__ arena_decay_t ;

/* Variables and functions */
 int SMOOTHSTEP_NSTEPS ; 
 int /*<<< orphan*/  arena_decay_to_limit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int arena_maybe_decay (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ background_thread_enabled () ; 
 int /*<<< orphan*/  background_thread_interval_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  eset_npages_get (int /*<<< orphan*/ *) ; 
 scalar_t__ have_background_thread ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc_mutex_trylock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
arena_decay_impl(tsdn_t *tsdn, arena_t *arena, arena_decay_t *decay,
    eset_t *eset, bool is_background_thread, bool all) {
	if (all) {
		malloc_mutex_lock(tsdn, &decay->mtx);
		arena_decay_to_limit(tsdn, arena, decay, eset, all, 0,
		    eset_npages_get(eset), is_background_thread);
		malloc_mutex_unlock(tsdn, &decay->mtx);

		return false;
	}

	if (malloc_mutex_trylock(tsdn, &decay->mtx)) {
		/* No need to wait if another thread is in progress. */
		return true;
	}

	bool epoch_advanced = arena_maybe_decay(tsdn, arena, decay, eset,
	    is_background_thread);
	size_t npages_new;
	if (epoch_advanced) {
		/* Backlog is updated on epoch advance. */
		npages_new = decay->backlog[SMOOTHSTEP_NSTEPS-1];
	}
	malloc_mutex_unlock(tsdn, &decay->mtx);

	if (have_background_thread && background_thread_enabled() &&
	    epoch_advanced && !is_background_thread) {
		background_thread_interval_check(tsdn, arena, decay,
		    npages_new);
	}

	return false;
}