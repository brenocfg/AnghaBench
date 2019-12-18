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
 unsigned int R4K_HIT ; 
 int /*<<< orphan*/ * cpu_foreign_map ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ mips_cm_present () ; 

__attribute__((used)) static inline bool r4k_op_needs_ipi(unsigned int type)
{
	/* The MIPS Coherence Manager (CM) globalizes address-based cache ops */
	if (type == R4K_HIT && mips_cm_present())
		return false;

	/*
	 * Hardware doesn't globalize the required cache ops, so SMP calls may
	 * be needed, but only if there are foreign CPUs (non-siblings with
	 * separate caches).
	 */
	/* cpu_foreign_map[] undeclared when !CONFIG_SMP */
#ifdef CONFIG_SMP
	return !cpumask_empty(&cpu_foreign_map[0]);
#else
	return false;
#endif
}