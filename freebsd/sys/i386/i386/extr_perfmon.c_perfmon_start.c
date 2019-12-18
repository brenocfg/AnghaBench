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
 int EBUSY ; 
 int EINVAL ; 
 int NPMC ; 
 int PMCF_EN ; 
 int* ctl_shadow ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * msr_pmc ; 
 int perfmon_inuse ; 
 int /*<<< orphan*/ * pmc_shadow ; 
 int /*<<< orphan*/  writectl (int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
perfmon_start(int pmc)
{
	register_t	saveintr;

	if (pmc < 0 || pmc >= NPMC)
		return EINVAL;

	if (perfmon_inuse & (1 << pmc)) {
		saveintr = intr_disable();
		ctl_shadow[pmc] |= (PMCF_EN << 16);
		wrmsr(msr_pmc[pmc], pmc_shadow[pmc]);
		writectl(pmc);
		intr_restore(saveintr);
		return 0;
	}
	return EBUSY;
}