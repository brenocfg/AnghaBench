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
 int cpu_exthigh ; 
 int /*<<< orphan*/  do_cpuid (int,unsigned int*) ; 

bool
vmm_supports_1G_pages(void)
{
	unsigned int regs[4];

	/*
	 * CPUID.80000001:EDX[bit 26] = 1 indicates support for 1GB pages
	 *
	 * Both Intel and AMD support this bit.
	 */
	if (cpu_exthigh >= 0x80000001) {
		do_cpuid(0x80000001, regs);
		if (regs[3] & (1 << 26))
			return (true);
	}
	return (false);
}