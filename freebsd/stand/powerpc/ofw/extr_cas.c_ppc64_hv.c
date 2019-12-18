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

__attribute__((used)) static __inline int
ppc64_hv(void)
{
	int hv;

	/* PSL_HV is bit 3 of 64-bit MSR */
	__asm __volatile ("mfmsr %0\n\t"
		"rldicl %0,%0,4,63" : "=r"(hv));

	return (hv);
}