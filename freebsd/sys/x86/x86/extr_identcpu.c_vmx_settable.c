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
typedef  unsigned long long uint64_t ;
typedef  unsigned long long uint32_t ;

/* Variables and functions */
 unsigned long long rdmsr (int) ; 

__attribute__((used)) static uint32_t
vmx_settable(uint64_t basic, int msr, int true_msr)
{
	uint64_t val;

	if (basic & (1ULL << 55))
		val = rdmsr(true_msr);
	else
		val = rdmsr(msr);

	/* Just report the controls that can be set to 1. */
	return (val >> 32);
}