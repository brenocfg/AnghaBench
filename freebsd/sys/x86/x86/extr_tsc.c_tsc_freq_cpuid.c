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
typedef  int uint64_t ;
typedef  int u_int ;

/* Variables and functions */
 int cpu_high ; 
 int /*<<< orphan*/  do_cpuid (int,int*) ; 
 int tsc_freq ; 

__attribute__((used)) static bool
tsc_freq_cpuid(void)
{
	u_int regs[4];

	if (cpu_high < 0x15)
		return (false);
	do_cpuid(0x15, regs);
	if (regs[0] != 0 && regs[1] != 0 && regs[2] != 0) {
		tsc_freq = (uint64_t)regs[2] * regs[1] / regs[0];
		return (true);
	}

	if (cpu_high < 0x16)
		return (false);
	do_cpuid(0x16, regs);
	if (regs[0] != 0) {
		tsc_freq = (uint64_t)regs[0] * 1000000;
		return (true);
	}

	return (false);
}