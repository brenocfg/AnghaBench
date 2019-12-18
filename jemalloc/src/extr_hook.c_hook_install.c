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
typedef  int /*<<< orphan*/  hooks_t ;

/* Variables and functions */
 void* hook_install_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hooks_mu ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_global_slow_inc (int /*<<< orphan*/ *) ; 

void *
hook_install(tsdn_t *tsdn, hooks_t *to_install) {
	malloc_mutex_lock(tsdn, &hooks_mu);
	void *ret = hook_install_locked(to_install);
	if (ret != NULL) {
		tsd_global_slow_inc(tsdn);
	}
	malloc_mutex_unlock(tsdn, &hooks_mu);
	return ret;
}