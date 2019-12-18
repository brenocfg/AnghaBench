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
 int /*<<< orphan*/  X86_BUG_CPU_MELTDOWN ; 
 int /*<<< orphan*/  X86_FEATURE_SMAP ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool smap_works_speculatively(void)
{
	if (!boot_cpu_has(X86_FEATURE_SMAP))
		return false;

	/*
	 * On CPUs which are vulnerable to Meltdown, SMAP does not
	 * prevent speculative access to user data in the L1 cache.
	 * Consider SMAP to be non-functional as a mitigation on these
	 * CPUs.
	 */
	if (boot_cpu_has(X86_BUG_CPU_MELTDOWN))
		return false;

	return true;
}