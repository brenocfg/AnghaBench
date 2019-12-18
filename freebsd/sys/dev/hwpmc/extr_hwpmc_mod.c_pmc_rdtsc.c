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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int AMDID_RDTSCP ; 
 scalar_t__ __predict_true (int) ; 
 int amd_feature ; 
 int /*<<< orphan*/  get_cyclecount () ; 
 int /*<<< orphan*/  rdtsc () ; 
 int /*<<< orphan*/  rdtscp () ; 

uint64_t
pmc_rdtsc(void)
{
#if defined(__i386__) || defined(__amd64__)
	if (__predict_true(amd_feature & AMDID_RDTSCP))
		return rdtscp();
	else
		return rdtsc();
#else
	return get_cyclecount();
#endif
}