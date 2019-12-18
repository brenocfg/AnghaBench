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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ thread_allocated_get (int /*<<< orphan*/ *) ; 
 scalar_t__ thread_allocated_last_event_get (int /*<<< orphan*/ *) ; 
 scalar_t__ thread_allocated_next_event_compute (int /*<<< orphan*/ *) ; 
 scalar_t__ thread_allocated_next_event_fast_get (int /*<<< orphan*/ *) ; 
 scalar_t__ thread_allocated_next_event_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_event_active ; 

void
thread_event_assert_invariants_debug(tsd_t *tsd) {
	uint64_t thread_allocated = thread_allocated_get(tsd);
	uint64_t last_event = thread_allocated_last_event_get(tsd);
	uint64_t next_event = thread_allocated_next_event_get(tsd);
	uint64_t next_event_fast = thread_allocated_next_event_fast_get(tsd);

	assert(last_event != next_event);
	if (next_event <= THREAD_ALLOCATED_NEXT_EVENT_FAST_MAX) {
		assert(next_event_fast == next_event);
	} else {
		assert(next_event_fast == 0U);
	}

	/* The subtraction is intentionally susceptible to underflow. */
	uint64_t interval = next_event - last_event;

	/* The subtraction is intentionally susceptible to underflow. */
	assert(thread_allocated - last_event < interval);

	uint64_t min_wait = thread_allocated_next_event_compute(tsd);

	/*
	 * next_event should have been pushed up only except when no event is
	 * on and the TSD is just initialized.  The last_event == 0U guard
	 * below is stronger than needed, but having an exactly accurate guard
	 * is more complicated to implement.
	 */
	assert((!thread_event_active && last_event == 0U) ||
	    interval == min_wait ||
	    (interval < min_wait && interval == THREAD_EVENT_MAX_INTERVAL));
}