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
 int CPUID2_MON ; 
 int CPUID5_MON_MWAIT_EXT ; 
 int CPUID5_MWAIT_INTRBREAK ; 
 int cpu_feature2 ; 
 int cpu_mon_mwait_flags ; 

bool
cpu_mwait_usable(void)
{

	return ((cpu_feature2 & CPUID2_MON) != 0 && ((cpu_mon_mwait_flags &
	    (CPUID5_MON_MWAIT_EXT | CPUID5_MWAIT_INTRBREAK)) ==
	    (CPUID5_MON_MWAIT_EXT | CPUID5_MWAIT_INTRBREAK)));
}