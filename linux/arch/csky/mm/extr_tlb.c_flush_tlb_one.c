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
 int ASID_MASK ; 
 unsigned long TLB_ENTRY_SIZE_MASK ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int read_mmu_entryhi () ; 
 int read_mmu_index () ; 
 int /*<<< orphan*/  restore_asid_inv_utlb (int,int) ; 
 int /*<<< orphan*/  sync_is () ; 
 int /*<<< orphan*/  tlb_invalid_indexed () ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  write_mmu_entryhi (unsigned long) ; 

void flush_tlb_one(unsigned long addr)
{
	addr &= TLB_ENTRY_SIZE_MASK;

#ifdef CONFIG_CPU_HAS_TLBI
	asm volatile("tlbi.vaas %0"::"r"(addr));
	sync_is();
#else
	{
	int oldpid, idx;
	unsigned long flags;

	local_irq_save(flags);
	oldpid = read_mmu_entryhi() & ASID_MASK;
	write_mmu_entryhi(addr | oldpid);
	tlb_probe();
	idx = read_mmu_index();
	if (idx >= 0)
		tlb_invalid_indexed();

	restore_asid_inv_utlb(oldpid, oldpid);
	local_irq_restore(flags);
	}
#endif
}