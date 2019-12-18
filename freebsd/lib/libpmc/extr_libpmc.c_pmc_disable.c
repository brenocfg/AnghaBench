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
struct pmc_op_pmcadmin {int pm_cpu; int pm_pmc; int /*<<< orphan*/  pm_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCADMIN ; 
 int PMC_CALL (int /*<<< orphan*/ ,struct pmc_op_pmcadmin*) ; 
 int /*<<< orphan*/  PMC_STATE_DISABLED ; 

int
pmc_disable(int cpu, int pmc)
{
	struct pmc_op_pmcadmin ssa;

	ssa.pm_cpu = cpu;
	ssa.pm_pmc = pmc;
	ssa.pm_state = PMC_STATE_DISABLED;
	return (PMC_CALL(PMCADMIN, &ssa));
}