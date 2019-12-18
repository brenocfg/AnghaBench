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
struct perf_event {int dummy; } ;
struct cpu_hw_events {int n_events; int* current_idx; struct perf_event** event; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static int active_event_index(struct cpu_hw_events *cpuc,
			      struct perf_event *event)
{
	int i;

	for (i = 0; i < cpuc->n_events; i++) {
		if (cpuc->event[i] == event)
			break;
	}
	BUG_ON(i == cpuc->n_events);
	return cpuc->current_idx[i];
}