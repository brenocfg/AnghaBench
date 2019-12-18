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

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int NPMC ; 
 int /*<<< orphan*/ * msr_pmc ; 
 int perfmon_inuse ; 
 scalar_t__* pmc_shadow ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,scalar_t__) ; 

int
perfmon_reset(int pmc)
{
	if (pmc < 0 || pmc >= NPMC)
		return EINVAL;

	if (perfmon_inuse & (1 << pmc)) {
		wrmsr(msr_pmc[pmc], pmc_shadow[pmc] = 0);
		return 0;
	}
	return EBUSY;
}