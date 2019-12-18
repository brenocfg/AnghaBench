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
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int mp_maxid ; 
 int mp_ncpus ; 

void
socfpga_mp_setmaxid(platform_t plat)
{
	int hwcpu, ncpu;

	/* If we've already set this don't bother to do it again. */
	if (mp_ncpus != 0)
		return;

	hwcpu = 2;

	ncpu = hwcpu;
	TUNABLE_INT_FETCH("hw.ncpu", &ncpu);
	if (ncpu < 1 || ncpu > hwcpu)
		ncpu = hwcpu;

	mp_ncpus = ncpu;
	mp_maxid = ncpu - 1;
}