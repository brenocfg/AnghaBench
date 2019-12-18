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
typedef  int /*<<< orphan*/  nstime_t ;
typedef  int /*<<< orphan*/  eset_t ;
typedef  int /*<<< orphan*/  arena_t ;
struct TYPE_6__ {size_t nunpurged; } ;
typedef  TYPE_1__ arena_decay_t ;

/* Variables and functions */
 size_t arena_decay_backlog_npages_limit (TYPE_1__*) ; 
 int /*<<< orphan*/  arena_decay_epoch_advance_helper (TYPE_1__*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  arena_decay_try_purge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,size_t,size_t,int) ; 
 int /*<<< orphan*/  background_thread_enabled () ; 
 size_t eset_npages_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arena_decay_epoch_advance(tsdn_t *tsdn, arena_t *arena, arena_decay_t *decay,
    eset_t *eset, const nstime_t *time, bool is_background_thread) {
	size_t current_npages = eset_npages_get(eset);
	arena_decay_epoch_advance_helper(decay, time, current_npages);

	size_t npages_limit = arena_decay_backlog_npages_limit(decay);
	/* We may unlock decay->mtx when try_purge(). Finish logging first. */
	decay->nunpurged = (npages_limit > current_npages) ? npages_limit :
	    current_npages;

	if (!background_thread_enabled() || is_background_thread) {
		arena_decay_try_purge(tsdn, arena, decay, eset,
		    current_npages, npages_limit, is_background_thread);
	}
}