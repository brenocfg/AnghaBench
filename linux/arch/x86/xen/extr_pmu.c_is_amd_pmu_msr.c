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
 unsigned int MSR_F15H_PERF_CTL ; 
 int MSR_F15H_PERF_CTR ; 
 unsigned int MSR_K7_EVNTSEL0 ; 
 int MSR_K7_PERFCTR0 ; 
 int amd_num_counters ; 

__attribute__((used)) static inline bool is_amd_pmu_msr(unsigned int msr)
{
	if ((msr >= MSR_F15H_PERF_CTL &&
	     msr < MSR_F15H_PERF_CTR + (amd_num_counters * 2)) ||
	    (msr >= MSR_K7_EVNTSEL0 &&
	     msr < MSR_K7_PERFCTR0 + amd_num_counters))
		return true;

	return false;
}