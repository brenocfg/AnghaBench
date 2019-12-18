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
struct pmc_op_pmcrw {int pm_value; int /*<<< orphan*/  pm_flags; int /*<<< orphan*/  pm_pmcid; } ;
typedef  int pmc_value_t ;
typedef  int /*<<< orphan*/  pmc_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMCRW ; 
 scalar_t__ PMC_CALL (int /*<<< orphan*/ ,struct pmc_op_pmcrw*) ; 
 int /*<<< orphan*/  PMC_F_OLDVALUE ; 

int
pmc_read(pmc_id_t pmc, pmc_value_t *value)
{
	struct pmc_op_pmcrw pmc_read_op;

	pmc_read_op.pm_pmcid = pmc;
	pmc_read_op.pm_flags = PMC_F_OLDVALUE;
	pmc_read_op.pm_value = -1;

	if (PMC_CALL(PMCRW, &pmc_read_op) < 0)
		return (-1);

	*value = pmc_read_op.pm_value;
	return (0);
}