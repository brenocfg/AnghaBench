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
struct cpu_cf_events {int flags; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int PMU_F_ENABLED ; 
 int /*<<< orphan*/  cpu_cf_events ; 
 int lcctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct cpu_cf_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpumf_pmu_enable(struct pmu *pmu)
{
	struct cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	int err;

	if (cpuhw->flags & PMU_F_ENABLED)
		return;

	err = lcctl(cpuhw->state);
	if (err) {
		pr_err("Enabling the performance measuring unit "
		       "failed with rc=%x\n", err);
		return;
	}

	cpuhw->flags |= PMU_F_ENABLED;
}