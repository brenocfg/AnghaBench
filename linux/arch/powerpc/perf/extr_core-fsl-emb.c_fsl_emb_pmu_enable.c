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
struct cpu_hw_events {scalar_t__ n_events; scalar_t__ disabled; } ;

/* Variables and functions */
 int PMGC0_FCECE ; 
 int PMGC0_PMIE ; 
 int /*<<< orphan*/  PMRN_PMGC0 ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  isync () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mtpmr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppc_set_pmu_inuse (int) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsl_emb_pmu_enable(struct pmu *pmu)
{
	struct cpu_hw_events *cpuhw;
	unsigned long flags;

	local_irq_save(flags);
	cpuhw = this_cpu_ptr(&cpu_hw_events);
	if (!cpuhw->disabled)
		goto out;

	cpuhw->disabled = 0;
	ppc_set_pmu_inuse(cpuhw->n_events != 0);

	if (cpuhw->n_events > 0) {
		mtpmr(PMRN_PMGC0, PMGC0_PMIE | PMGC0_FCECE);
		isync();
	}

 out:
	local_irq_restore(flags);
}