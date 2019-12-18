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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int CPUV7_L2CTLR_NPROC (int) ; 
 int cp15_l2ctlr_get () ; 
 int mp_maxid ; 
 int mp_ncpus ; 

void
tegra124_mp_setmaxid(platform_t plat)
{
	int ncpu;

	/* If we've already set the global vars don't bother to do it again. */
	if (mp_ncpus != 0)
		return;

	/* Read current CP15 Cache Size ID Register */
	ncpu = cp15_l2ctlr_get();
	ncpu = CPUV7_L2CTLR_NPROC(ncpu);

	mp_ncpus = ncpu;
	mp_maxid = ncpu - 1;
}