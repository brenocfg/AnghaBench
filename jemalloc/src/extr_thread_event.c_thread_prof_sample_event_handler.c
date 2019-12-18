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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_prof ; 
 int lg_prof_sample ; 
 scalar_t__ opt_prof ; 
 int /*<<< orphan*/  prof_active_get_unlocked () ; 
 int /*<<< orphan*/  prof_idump (int /*<<< orphan*/ ) ; 
 scalar_t__ prof_idump_accum (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int prof_sample_event_wait_get (int /*<<< orphan*/ *) ; 
 scalar_t__ prof_sample_last_event_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_sample_last_event_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ thread_allocated_last_event_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_prof_sample_event_update (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
thread_prof_sample_event_handler(tsd_t *tsd) {
	assert(config_prof && opt_prof);
	assert(prof_sample_event_wait_get(tsd) == 0U);
	uint64_t last_event = thread_allocated_last_event_get(tsd);
	uint64_t last_sample_event = prof_sample_last_event_get(tsd);
	prof_sample_last_event_set(tsd, last_event);
	if (prof_idump_accum(tsd_tsdn(tsd), last_event - last_sample_event)) {
		prof_idump(tsd_tsdn(tsd));
	}
	if (!prof_active_get_unlocked()) {
		/*
		 * If prof_active is off, we reset prof_sample_event_wait to be
		 * the sample interval when it drops to 0, so that there won't
		 * be excessive routings to the slow path, and that when
		 * prof_active is turned on later, the counting for sampling
		 * can immediately resume as normal.
		 */
		thread_prof_sample_event_update(tsd,
		    (uint64_t)(1 << lg_prof_sample));
	}
}