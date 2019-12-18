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
struct arch_tlbflush_unmap_batch {int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLB_LOCAL_SHOOTDOWN ; 
 scalar_t__ cpumask_any_but (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_tlb_func_local (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_others (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  full_flush_tlb_info ; 
 int get_cpu () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  lockdep_assert_irqs_enabled () ; 
 scalar_t__ nr_cpu_ids ; 
 int /*<<< orphan*/  put_cpu () ; 

void arch_tlbbatch_flush(struct arch_tlbflush_unmap_batch *batch)
{
	int cpu = get_cpu();

	if (cpumask_test_cpu(cpu, &batch->cpumask)) {
		lockdep_assert_irqs_enabled();
		local_irq_disable();
		flush_tlb_func_local(&full_flush_tlb_info, TLB_LOCAL_SHOOTDOWN);
		local_irq_enable();
	}

	if (cpumask_any_but(&batch->cpumask, cpu) < nr_cpu_ids)
		flush_tlb_others(&batch->cpumask, &full_flush_tlb_info);

	cpumask_clear(&batch->cpumask);

	put_cpu();
}