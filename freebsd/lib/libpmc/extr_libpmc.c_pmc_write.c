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
struct pmc_op_pmcrw {int /*<<< orphan*/  pm_value; int /*<<< orphan*/  pm_flags; int /*<<< orphan*/  pm_pmcid; } ;
typedef  int /*<<< orphan*/  pmc_value_t ;
typedef  int /*<<< orphan*/  pmc_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMCRW ; 
 int PMC_CALL (int /*<<< orphan*/ ,struct pmc_op_pmcrw*) ; 
 int /*<<< orphan*/  PMC_F_NEWVALUE ; 

int
pmc_write(pmc_id_t pmc, pmc_value_t value)
{
	struct pmc_op_pmcrw pmc_write_op;

	pmc_write_op.pm_pmcid = pmc;
	pmc_write_op.pm_flags = PMC_F_NEWVALUE;
	pmc_write_op.pm_value = value;
	return (PMC_CALL(PMCRW, &pmc_write_op));
}