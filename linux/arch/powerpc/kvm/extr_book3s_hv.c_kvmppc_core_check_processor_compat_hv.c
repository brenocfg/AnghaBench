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
 int /*<<< orphan*/  CPU_FTR_ARCH_206 ; 
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int EIO ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ radix_enabled () ; 

__attribute__((used)) static int kvmppc_core_check_processor_compat_hv(void)
{
	if (cpu_has_feature(CPU_FTR_HVMODE) &&
	    cpu_has_feature(CPU_FTR_ARCH_206))
		return 0;

	/* POWER9 in radix mode is capable of being a nested hypervisor. */
	if (cpu_has_feature(CPU_FTR_ARCH_300) && radix_enabled())
		return 0;

	return -EIO;
}