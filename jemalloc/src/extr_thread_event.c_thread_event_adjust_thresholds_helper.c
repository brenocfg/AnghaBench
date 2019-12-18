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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 scalar_t__ THREAD_ALLOCATED_NEXT_EVENT_FAST_MAX ; 
 scalar_t__ THREAD_EVENT_MAX_INTERVAL ; 
 scalar_t__ THREAD_EVENT_MAX_START_WAIT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ thread_allocated_last_event_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_allocated_next_event_fast_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  thread_allocated_next_event_set (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
thread_event_adjust_thresholds_helper(tsd_t *tsd, uint64_t wait) {
	assert(wait <= THREAD_EVENT_MAX_START_WAIT);
	uint64_t next_event = thread_allocated_last_event_get(tsd) + (wait <=
	    THREAD_EVENT_MAX_INTERVAL ? wait : THREAD_EVENT_MAX_INTERVAL);
	thread_allocated_next_event_set(tsd, next_event);
	uint64_t next_event_fast = (next_event <=
	    THREAD_ALLOCATED_NEXT_EVENT_FAST_MAX) ? next_event : 0U;
	thread_allocated_next_event_fast_set(tsd, next_event_fast);
}