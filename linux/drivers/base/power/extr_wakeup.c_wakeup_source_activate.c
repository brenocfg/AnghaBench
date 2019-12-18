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
struct wakeup_source {int active; int /*<<< orphan*/  name; int /*<<< orphan*/  last_time; int /*<<< orphan*/  start_prevent_time; scalar_t__ autosleep_enabled; int /*<<< orphan*/  active_count; } ;

/* Variables and functions */
 scalar_t__ WARN_ONCE (int /*<<< orphan*/ ,char*) ; 
 unsigned int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  combined_event_count ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  trace_wakeup_source_activate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wakeup_source_not_registered (struct wakeup_source*) ; 

__attribute__((used)) static void wakeup_source_activate(struct wakeup_source *ws)
{
	unsigned int cec;

	if (WARN_ONCE(wakeup_source_not_registered(ws),
			"unregistered wakeup source\n"))
		return;

	ws->active = true;
	ws->active_count++;
	ws->last_time = ktime_get();
	if (ws->autosleep_enabled)
		ws->start_prevent_time = ws->last_time;

	/* Increment the counter of events in progress. */
	cec = atomic_inc_return(&combined_event_count);

	trace_wakeup_source_activate(ws->name, cec);
}