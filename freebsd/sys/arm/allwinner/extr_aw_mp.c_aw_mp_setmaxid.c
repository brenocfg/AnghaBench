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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int CPUV7_L2CTLR_NPROC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp15_l2ctlr_get () ; 
 int mp_maxid ; 
 int mp_ncpus ; 

void
aw_mp_setmaxid(platform_t plat)
{
	int ncpu;
	uint32_t reg;

	if (mp_ncpus != 0)
		return;

	reg = cp15_l2ctlr_get();
	ncpu = CPUV7_L2CTLR_NPROC(reg);

	mp_ncpus = ncpu;
	mp_maxid = ncpu - 1;
}