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
typedef  int /*<<< orphan*/  uint32_t ;
struct pmc_op_getmsr {int /*<<< orphan*/  pm_msr; int /*<<< orphan*/  pm_pmcid; } ;
typedef  int /*<<< orphan*/  pmc_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMCGETMSR ; 
 scalar_t__ PMC_CALL (int /*<<< orphan*/ ,struct pmc_op_getmsr*) ; 

int
pmc_get_msr(pmc_id_t pmc, uint32_t *msr)
{
	struct pmc_op_getmsr gm;

	gm.pm_pmcid = pmc;
	if (PMC_CALL(PMCGETMSR, &gm) < 0)
		return (-1);
	*msr = gm.pm_msr;
	return (0);
}