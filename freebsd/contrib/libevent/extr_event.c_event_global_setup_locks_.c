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
 int /*<<< orphan*/  EVTHREAD_SETUP_GLOBAL_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_debug_map_lock_ ; 
 scalar_t__ evsig_global_setup_locks_ (int const) ; 
 scalar_t__ evutil_global_setup_locks_ (int const) ; 
 scalar_t__ evutil_secure_rng_global_setup_locks_ (int const) ; 

int
event_global_setup_locks_(const int enable_locks)
{
#ifndef EVENT__DISABLE_DEBUG_MODE
	EVTHREAD_SETUP_GLOBAL_LOCK(event_debug_map_lock_, 0);
#endif
	if (evsig_global_setup_locks_(enable_locks) < 0)
		return -1;
	if (evutil_global_setup_locks_(enable_locks) < 0)
		return -1;
	if (evutil_secure_rng_global_setup_locks_(enable_locks) < 0)
		return -1;
	return 0;
}