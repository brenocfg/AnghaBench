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

/* Variables and functions */
 int /*<<< orphan*/  EVTHREAD_FREE_LOCK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * event_debug_map_lock_ ; 
 int /*<<< orphan*/  evthreadimpl_disable_lock_debugging_ () ; 

__attribute__((used)) static void
event_free_debug_globals_locks(void)
{
#ifndef EVENT__DISABLE_THREAD_SUPPORT
#ifndef EVENT__DISABLE_DEBUG_MODE
	if (event_debug_map_lock_ != NULL) {
		EVTHREAD_FREE_LOCK(event_debug_map_lock_, 0);
		event_debug_map_lock_ = NULL;
		evthreadimpl_disable_lock_debugging_();
	}
#endif /* EVENT__DISABLE_DEBUG_MODE */
#endif /* EVENT__DISABLE_THREAD_SUPPORT */
	return;
}