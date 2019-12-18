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
struct wakeup_source {scalar_t__ relax_count; scalar_t__ active_count; int active; void* max_time; int /*<<< orphan*/  name; scalar_t__ autosleep_enabled; scalar_t__ timer_expires; int /*<<< orphan*/  timer; void* last_time; int /*<<< orphan*/  total_time; } ;
typedef  void* ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_IN_PROGRESS ; 
 unsigned int atomic_add_return (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  combined_event_count ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,void*) ; 
 void* ktime_get () ; 
 void* ktime_sub (void*,void*) ; 
 scalar_t__ ktime_to_ns (void*) ; 
 int /*<<< orphan*/  split_counters (unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  trace_wakeup_source_deactivate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  update_prevent_sleep_time (struct wakeup_source*,void*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_count_wait_queue ; 

__attribute__((used)) static void wakeup_source_deactivate(struct wakeup_source *ws)
{
	unsigned int cnt, inpr, cec;
	ktime_t duration;
	ktime_t now;

	ws->relax_count++;
	/*
	 * __pm_relax() may be called directly or from a timer function.
	 * If it is called directly right after the timer function has been
	 * started, but before the timer function calls __pm_relax(), it is
	 * possible that __pm_stay_awake() will be called in the meantime and
	 * will set ws->active.  Then, ws->active may be cleared immediately
	 * by the __pm_relax() called from the timer function, but in such a
	 * case ws->relax_count will be different from ws->active_count.
	 */
	if (ws->relax_count != ws->active_count) {
		ws->relax_count--;
		return;
	}

	ws->active = false;

	now = ktime_get();
	duration = ktime_sub(now, ws->last_time);
	ws->total_time = ktime_add(ws->total_time, duration);
	if (ktime_to_ns(duration) > ktime_to_ns(ws->max_time))
		ws->max_time = duration;

	ws->last_time = now;
	del_timer(&ws->timer);
	ws->timer_expires = 0;

	if (ws->autosleep_enabled)
		update_prevent_sleep_time(ws, now);

	/*
	 * Increment the counter of registered wakeup events and decrement the
	 * couter of wakeup events in progress simultaneously.
	 */
	cec = atomic_add_return(MAX_IN_PROGRESS, &combined_event_count);
	trace_wakeup_source_deactivate(ws->name, cec);

	split_counters(&cnt, &inpr);
	if (!inpr && waitqueue_active(&wakeup_count_wait_queue))
		wake_up(&wakeup_count_wait_queue);
}