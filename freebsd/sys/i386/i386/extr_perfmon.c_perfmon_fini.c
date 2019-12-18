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
 scalar_t__* ctl_shadow ; 
 int perfmon_inuse ; 
 int /*<<< orphan*/  perfmon_stop (int) ; 

int
perfmon_fini(int pmc)
{
	if (pmc < 0 || pmc >= NPMC)
		return EINVAL;

	if (perfmon_inuse & (1 << pmc)) {
		perfmon_stop(pmc);
		ctl_shadow[pmc] = 0;
		perfmon_inuse &= ~(1 << pmc);
		return 0;
	}
	return EBUSY;		/* XXX reversed sense */
}