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
struct hw_perf_event {int idx; int state; int /*<<< orphan*/  config_base; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct cpu_hw_events {int n_events; int* current_idx; int /*<<< orphan*/ * pcr; struct perf_event** event; int /*<<< orphan*/  n_added; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_HES_ARCH ; 
 int PIC_NO_INDEX ; 
 int /*<<< orphan*/  sparc_pmu_start (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void calculate_multiple_pcrs(struct cpu_hw_events *cpuc)
{
	int i;

	if (!cpuc->n_added)
		goto out;

	for (i = 0; i < cpuc->n_events; i++) {
		struct perf_event *cp = cpuc->event[i];
		struct hw_perf_event *hwc = &cp->hw;
		int idx = hwc->idx;

		if (cpuc->current_idx[i] != PIC_NO_INDEX)
			continue;

		cpuc->current_idx[i] = idx;

		if (cp->hw.state & PERF_HES_ARCH)
			continue;

		sparc_pmu_start(cp, PERF_EF_RELOAD);
	}
out:
	for (i = 0; i < cpuc->n_events; i++) {
		struct perf_event *cp = cpuc->event[i];
		int idx = cp->hw.idx;

		cpuc->pcr[idx] |= cp->hw.config_base;
	}
}