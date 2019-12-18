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
typedef  int /*<<< orphan*/  uintmax_t ;
struct pmc_process {int dummy; } ;
struct pmc_cpu {int dummy; } ;

/* Variables and functions */
 int CR4_PCE ; 
 int /*<<< orphan*/  MDP ; 
 int /*<<< orphan*/  PMCDBG3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc_cpu*,struct pmc_process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWO ; 
 int /*<<< orphan*/  load_cr4 (int) ; 
 int rcr4 () ; 

__attribute__((used)) static int
intel_switch_out(struct pmc_cpu *pc, struct pmc_process *pp)
{
	(void) pc;
	(void) pp;		/* can be NULL */

	PMCDBG3(MDP,SWO,1, "pc=%p pp=%p cr4=0x%jx", pc, pp,
	    (uintmax_t) rcr4());

	/* always turn off the RDPMC instruction */
	load_cr4(rcr4() & ~CR4_PCE);

	return 0;
}