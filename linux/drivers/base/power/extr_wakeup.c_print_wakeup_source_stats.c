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
struct wakeup_source {unsigned long active_count; int /*<<< orphan*/  lock; scalar_t__ last_time; int /*<<< orphan*/  expire_count; int /*<<< orphan*/  wakeup_count; int /*<<< orphan*/  event_count; int /*<<< orphan*/  name; scalar_t__ start_prevent_time; scalar_t__ autosleep_enabled; scalar_t__ active; scalar_t__ prevent_sleep_time; scalar_t__ max_time; scalar_t__ total_time; } ;
struct seq_file {int dummy; } ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 scalar_t__ ktime_add (scalar_t__,scalar_t__) ; 
 scalar_t__ ktime_get () ; 
 scalar_t__ ktime_sub (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ktime_to_ms (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int print_wakeup_source_stats(struct seq_file *m,
				     struct wakeup_source *ws)
{
	unsigned long flags;
	ktime_t total_time;
	ktime_t max_time;
	unsigned long active_count;
	ktime_t active_time;
	ktime_t prevent_sleep_time;

	spin_lock_irqsave(&ws->lock, flags);

	total_time = ws->total_time;
	max_time = ws->max_time;
	prevent_sleep_time = ws->prevent_sleep_time;
	active_count = ws->active_count;
	if (ws->active) {
		ktime_t now = ktime_get();

		active_time = ktime_sub(now, ws->last_time);
		total_time = ktime_add(total_time, active_time);
		if (active_time > max_time)
			max_time = active_time;

		if (ws->autosleep_enabled)
			prevent_sleep_time = ktime_add(prevent_sleep_time,
				ktime_sub(now, ws->start_prevent_time));
	} else {
		active_time = 0;
	}

	seq_printf(m, "%-12s\t%lu\t\t%lu\t\t%lu\t\t%lu\t\t%lld\t\t%lld\t\t%lld\t\t%lld\t\t%lld\n",
		   ws->name, active_count, ws->event_count,
		   ws->wakeup_count, ws->expire_count,
		   ktime_to_ms(active_time), ktime_to_ms(total_time),
		   ktime_to_ms(max_time), ktime_to_ms(ws->last_time),
		   ktime_to_ms(prevent_sleep_time));

	spin_unlock_irqrestore(&ws->lock, flags);

	return 0;
}