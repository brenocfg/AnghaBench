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
struct pmc_process {int pp_flags; } ;
struct pmc_cpu {int dummy; } ;

/* Variables and functions */
 int CR4_PCE ; 
 int /*<<< orphan*/  MDP ; 
 int /*<<< orphan*/  PMCDBG3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc_cpu*,struct pmc_process*,int) ; 
 int PMC_PP_ENABLE_MSR_ACCESS ; 
 int /*<<< orphan*/  SWO ; 
 int /*<<< orphan*/  load_cr4 (int) ; 
 int rcr4 () ; 

__attribute__((used)) static int
amd_switch_out(struct pmc_cpu *pc, struct pmc_process *pp)
{
	(void) pc;
	(void) pp;		/* can be NULL */

	PMCDBG3(MDP,SWO,1, "pc=%p pp=%p enable-msr=%d", pc, pp, pp ?
	    (pp->pp_flags & PMC_PP_ENABLE_MSR_ACCESS) == 1 : 0);

	/* always turn off the RDPMC instruction */
	load_cr4(rcr4() & ~CR4_PCE);

	return 0;
}