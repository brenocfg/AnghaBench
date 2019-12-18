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
struct pmc_op_pmcattach {int /*<<< orphan*/  pm_pid; int /*<<< orphan*/  pm_pmc; } ;
typedef  int /*<<< orphan*/  pmc_id_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMCDETACH ; 
 int PMC_CALL (int /*<<< orphan*/ ,struct pmc_op_pmcattach*) ; 

int
pmc_detach(pmc_id_t pmc, pid_t pid)
{
	struct pmc_op_pmcattach pmc_detach_args;

	pmc_detach_args.pm_pmc = pmc;
	pmc_detach_args.pm_pid = pid;
	return (PMC_CALL(PMCDETACH, &pmc_detach_args));
}