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
struct pmc_op_simple {int /*<<< orphan*/  pm_pmcid; } ;
typedef  int /*<<< orphan*/  pmc_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMCSTOP ; 
 int PMC_CALL (int /*<<< orphan*/ ,struct pmc_op_simple*) ; 

int
pmc_stop(pmc_id_t pmc)
{
	struct pmc_op_simple	pmc_stop_args;

	pmc_stop_args.pm_pmcid = pmc;
	return (PMC_CALL(PMCSTOP, &pmc_stop_args));
}