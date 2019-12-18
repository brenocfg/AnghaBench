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
struct task_struct {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_SATP ; 
 int SATP_MODE ; 
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csr_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flush_icache_deferred (struct mm_struct*) ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 unsigned int smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 
 int virt_to_pfn (int /*<<< orphan*/ ) ; 

void switch_mm(struct mm_struct *prev, struct mm_struct *next,
	struct task_struct *task)
{
	unsigned int cpu;

	if (unlikely(prev == next))
		return;

	/*
	 * Mark the current MM context as inactive, and the next as
	 * active.  This is at least used by the icache flushing
	 * routines in order to determine who should be flushed.
	 */
	cpu = smp_processor_id();

	cpumask_clear_cpu(cpu, mm_cpumask(prev));
	cpumask_set_cpu(cpu, mm_cpumask(next));

	csr_write(CSR_SATP, virt_to_pfn(next->pgd) | SATP_MODE);
	local_flush_tlb_all();

	flush_icache_deferred(next);
}