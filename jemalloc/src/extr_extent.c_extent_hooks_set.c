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
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_6__ {int /*<<< orphan*/  mtx; } ;
typedef  TYPE_1__ background_thread_info_t ;
struct TYPE_7__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ arena_t ;

/* Variables and functions */
 TYPE_1__* arena_background_thread_info_get (TYPE_2__*) ; 
 int /*<<< orphan*/ * base_extent_hooks_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ have_background_thread ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

extent_hooks_t *
extent_hooks_set(tsd_t *tsd, arena_t *arena, extent_hooks_t *extent_hooks) {
	background_thread_info_t *info;
	if (have_background_thread) {
		info = arena_background_thread_info_get(arena);
		malloc_mutex_lock(tsd_tsdn(tsd), &info->mtx);
	}
	extent_hooks_t *ret = base_extent_hooks_set(arena->base, extent_hooks);
	if (have_background_thread) {
		malloc_mutex_unlock(tsd_tsdn(tsd), &info->mtx);
	}

	return ret;
}