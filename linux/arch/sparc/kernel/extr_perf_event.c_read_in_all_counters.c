#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ idx; int state; } ;
struct perf_event {TYPE_1__ hw; } ;
struct cpu_hw_events {int n_events; scalar_t__* current_idx; struct perf_event** event; } ;

/* Variables and functions */
 int PERF_HES_ARCH ; 
 int PERF_HES_STOPPED ; 
 scalar_t__ PIC_NO_INDEX ; 
 int /*<<< orphan*/  sparc_perf_event_update (struct perf_event*,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void read_in_all_counters(struct cpu_hw_events *cpuc)
{
	int i;

	for (i = 0; i < cpuc->n_events; i++) {
		struct perf_event *cp = cpuc->event[i];

		if (cpuc->current_idx[i] != PIC_NO_INDEX &&
		    cpuc->current_idx[i] != cp->hw.idx) {
			sparc_perf_event_update(cp, &cp->hw,
						cpuc->current_idx[i]);
			cpuc->current_idx[i] = PIC_NO_INDEX;
			if (cp->hw.state & PERF_HES_STOPPED)
				cp->hw.state |= PERF_HES_ARCH;
		}
	}
}