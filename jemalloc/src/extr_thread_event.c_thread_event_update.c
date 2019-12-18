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
 scalar_t__ thread_allocated_get (int /*<<< orphan*/ *) ; 
 scalar_t__ thread_allocated_last_event_get (int /*<<< orphan*/ *) ; 
 scalar_t__ thread_allocated_next_event_compute (int /*<<< orphan*/ *) ; 
 scalar_t__ thread_allocated_next_event_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_event_adjust_thresholds_helper (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  thread_event_assert_invariants (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_event_trigger (int /*<<< orphan*/ *,int) ; 

void
thread_event_update(tsd_t *tsd) {
	uint64_t wait = thread_allocated_next_event_compute(tsd);
	thread_event_adjust_thresholds_helper(tsd, wait);

	uint64_t last_event = thread_allocated_last_event_get(tsd);

	/* Both subtractions are intentionally susceptible to underflow. */
	if (thread_allocated_get(tsd) - last_event >=
	    thread_allocated_next_event_get(tsd) - last_event) {
		thread_event_trigger(tsd, true);
	} else {
		thread_event_assert_invariants(tsd);
	}
}