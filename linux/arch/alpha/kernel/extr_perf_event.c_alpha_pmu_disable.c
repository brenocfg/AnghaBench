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
struct pmu {int dummy; } ;
struct cpu_hw_events {int /*<<< orphan*/  idx_mask; scalar_t__ n_added; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERFMON_CMD_DISABLE ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrperfmon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alpha_pmu_disable(struct pmu *pmu)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	if (!cpuc->enabled)
		return;

	cpuc->enabled = 0;
	cpuc->n_added = 0;

	wrperfmon(PERFMON_CMD_DISABLE, cpuc->idx_mask);
}