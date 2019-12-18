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
struct vm_area_struct {scalar_t__ vm_mm; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {scalar_t__ active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  cpu ; 
 unsigned long cpu_asid_mask (int /*<<< orphan*/ *) ; 
 unsigned long cpu_context (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  current_cpu_data ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,unsigned long,int) ; 
 int /*<<< orphan*/  pte_val (int /*<<< orphan*/ ) ; 
 unsigned long read_c0_entryhi () ; 
 int read_c0_index () ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  tlb_write_random () ; 
 int /*<<< orphan*/  write_c0_entryhi (int) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (int /*<<< orphan*/ ) ; 

void __update_tlb(struct vm_area_struct *vma, unsigned long address, pte_t pte)
{
	unsigned long asid_mask = cpu_asid_mask(&current_cpu_data);
	unsigned long flags;
	int idx, pid;

	/*
	 * Handle debugger faulting in for debugee.
	 */
	if (current->active_mm != vma->vm_mm)
		return;

	pid = read_c0_entryhi() & asid_mask;

#ifdef DEBUG_TLB
	if ((pid != (cpu_context(cpu, vma->vm_mm) & asid_mask)) || (cpu_context(cpu, vma->vm_mm) == 0)) {
		printk("update_mmu_cache: Wheee, bogus tlbpid mmpid=%lu tlbpid=%d\n",
		       (cpu_context(cpu, vma->vm_mm)), pid);
	}
#endif

	local_irq_save(flags);
	address &= PAGE_MASK;
	write_c0_entryhi(address | pid);
	BARRIER;
	tlb_probe();
	idx = read_c0_index();
	write_c0_entrylo0(pte_val(pte));
	write_c0_entryhi(address | pid);
	if (idx < 0) {					/* BARRIER */
		tlb_write_random();
	} else {
		tlb_write_indexed();
	}
	write_c0_entryhi(pid);
	local_irq_restore(flags);
}