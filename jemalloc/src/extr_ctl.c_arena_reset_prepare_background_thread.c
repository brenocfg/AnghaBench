#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  mtx; } ;
typedef  TYPE_1__ background_thread_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ background_thread_enabled () ; 
 TYPE_1__* background_thread_info_get (unsigned int) ; 
 int /*<<< orphan*/  background_thread_lock ; 
 scalar_t__ background_thread_paused ; 
 scalar_t__ background_thread_started ; 
 scalar_t__ have_background_thread ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arena_reset_prepare_background_thread(tsd_t *tsd, unsigned arena_ind) {
	/* Temporarily disable the background thread during arena reset. */
	if (have_background_thread) {
		malloc_mutex_lock(tsd_tsdn(tsd), &background_thread_lock);
		if (background_thread_enabled()) {
			background_thread_info_t *info =
			    background_thread_info_get(arena_ind);
			assert(info->state == background_thread_started);
			malloc_mutex_lock(tsd_tsdn(tsd), &info->mtx);
			info->state = background_thread_paused;
			malloc_mutex_unlock(tsd_tsdn(tsd), &info->mtx);
		}
	}
}