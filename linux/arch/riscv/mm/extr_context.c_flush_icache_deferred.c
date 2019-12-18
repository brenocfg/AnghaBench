#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  icache_stale_mask; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_test_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_flush_icache_all () ; 
 int /*<<< orphan*/  smp_mb () ; 
 unsigned int smp_processor_id () ; 

__attribute__((used)) static inline void flush_icache_deferred(struct mm_struct *mm)
{
#ifdef CONFIG_SMP
	unsigned int cpu = smp_processor_id();
	cpumask_t *mask = &mm->context.icache_stale_mask;

	if (cpumask_test_cpu(cpu, mask)) {
		cpumask_clear_cpu(cpu, mask);
		/*
		 * Ensure the remote hart's writes are visible to this hart.
		 * This pairs with a barrier in flush_icache_mm.
		 */
		smp_mb();
		local_flush_icache_all();
	}

#endif
}