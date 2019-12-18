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
struct pmc_op_pmcsetcount {int /*<<< orphan*/  pm_count; int /*<<< orphan*/  pm_pmcid; } ;
typedef  int /*<<< orphan*/  pmc_value_t ;
typedef  int /*<<< orphan*/  pmc_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMCSETCOUNT ; 
 scalar_t__ PMC_CALL (int /*<<< orphan*/ ,struct pmc_op_pmcsetcount*) ; 

int
pmc_set(pmc_id_t pmc, pmc_value_t value)
{
	struct pmc_op_pmcsetcount sc;

	sc.pm_pmcid = pmc;
	sc.pm_count = value;

	if (PMC_CALL(PMCSETCOUNT, &sc) < 0)
		return (-1);
	return (0);
}