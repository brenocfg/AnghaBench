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
struct cpu_hw_events {int /*<<< orphan*/  perf_ctr_virt_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD64_EVENTSEL_HOSTONLY ; 
 int /*<<< orphan*/  amd_pmu_disable_all () ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_pmu_enable_all (int /*<<< orphan*/ ) ; 

void amd_pmu_disable_virt(void)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	/*
	 * We only mask out the Host-only bit so that host-only counting works
	 * when SVM is disabled. If someone sets up a guest-only counter when
	 * SVM is disabled the Guest-only bits still gets set and the counter
	 * will not count anything.
	 */
	cpuc->perf_ctr_virt_mask = AMD64_EVENTSEL_HOSTONLY;

	/* Reload all events */
	amd_pmu_disable_all();
	x86_pmu_enable_all(0);
}