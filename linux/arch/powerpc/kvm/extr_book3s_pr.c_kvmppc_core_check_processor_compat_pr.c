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
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 int EIO ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ radix_enabled () ; 

__attribute__((used)) static int kvmppc_core_check_processor_compat_pr(void)
{
	/*
	 * PR KVM can work on POWER9 inside a guest partition
	 * running in HPT mode.  It can't work if we are using
	 * radix translation (because radix provides no way for
	 * a process to have unique translations in quadrant 3).
	 */
	if (cpu_has_feature(CPU_FTR_ARCH_300) && radix_enabled())
		return -EIO;
	return 0;
}