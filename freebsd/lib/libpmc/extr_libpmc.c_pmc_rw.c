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
struct pmc_op_pmcrw {int pm_flags; int /*<<< orphan*/  pm_value; int /*<<< orphan*/  pm_pmcid; } ;
typedef  int /*<<< orphan*/  pmc_value_t ;
typedef  int /*<<< orphan*/  pmc_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMCRW ; 
 scalar_t__ PMC_CALL (int /*<<< orphan*/ ,struct pmc_op_pmcrw*) ; 
 int PMC_F_NEWVALUE ; 
 int PMC_F_OLDVALUE ; 

int
pmc_rw(pmc_id_t pmc, pmc_value_t newvalue, pmc_value_t *oldvaluep)
{
	struct pmc_op_pmcrw pmc_rw_op;

	pmc_rw_op.pm_pmcid = pmc;
	pmc_rw_op.pm_flags = PMC_F_NEWVALUE | PMC_F_OLDVALUE;
	pmc_rw_op.pm_value = newvalue;

	if (PMC_CALL(PMCRW, &pmc_rw_op) < 0)
		return (-1);

	*oldvaluep = pmc_rw_op.pm_value;
	return (0);
}