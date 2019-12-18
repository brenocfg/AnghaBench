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
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int EINVAL ; 
 int NPMC ; 
 int PMCF_SYS_FLAGS ; 
 unsigned int* ctl_shadow ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * msr_pmc ; 
 int perfmon_inuse ; 
 scalar_t__* pmc_shadow ; 
 int /*<<< orphan*/  writectl (int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,scalar_t__) ; 

int
perfmon_setup(int pmc, unsigned int control)
{
	register_t	saveintr;

	if (pmc < 0 || pmc >= NPMC)
		return EINVAL;

	perfmon_inuse |= (1 << pmc);
	control &= ~(PMCF_SYS_FLAGS << 16);
	saveintr = intr_disable();
	ctl_shadow[pmc] = control;
	writectl(pmc);
	wrmsr(msr_pmc[pmc], pmc_shadow[pmc] = 0);
	intr_restore(saveintr);
	return 0;
}