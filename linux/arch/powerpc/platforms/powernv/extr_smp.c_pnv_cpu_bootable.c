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
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int smp_generic_cpu_bootable (unsigned int) ; 

__attribute__((used)) static int pnv_cpu_bootable(unsigned int nr)
{
	/*
	 * Starting with POWER8, the subcore logic relies on all threads of a
	 * core being booted so that they can participate in split mode
	 * switches. So on those machines we ignore the smt_enabled_at_boot
	 * setting (smt-enabled on the kernel command line).
	 */
	if (cpu_has_feature(CPU_FTR_ARCH_207S))
		return 1;

	return smp_generic_cpu_bootable(nr);
}