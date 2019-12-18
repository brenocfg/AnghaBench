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
typedef  int /*<<< orphan*/  seq_hooks_t ;

/* Variables and functions */
 size_t HOOK_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_debug ; 
 int /*<<< orphan*/  hook_remove_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hooks ; 
 int /*<<< orphan*/  hooks_mu ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_global_slow_dec (int /*<<< orphan*/ *) ; 

void
hook_remove(tsdn_t *tsdn, void *opaque) {
	if (config_debug) {
		char *hooks_begin = (char *)&hooks[0];
		char *hooks_end = (char *)&hooks[HOOK_MAX];
		char *hook = (char *)opaque;
		assert(hooks_begin <= hook && hook < hooks_end
		    && (hook - hooks_begin) % sizeof(seq_hooks_t) == 0);
	}
	malloc_mutex_lock(tsdn, &hooks_mu);
	hook_remove_locked((seq_hooks_t *)opaque);
	tsd_global_slow_dec(tsdn);
	malloc_mutex_unlock(tsdn, &hooks_mu);
}