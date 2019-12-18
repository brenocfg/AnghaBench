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
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long FIXADDR_START ; 
 scalar_t__ FIX_KMAP_BEGIN ; 
 int KM_TYPE_NR ; 
 unsigned long PAGE_MASK ; 
 unsigned long __fix_to_virt (scalar_t__) ; 
 int /*<<< orphan*/  flush_tlb_one (unsigned long) ; 
 int /*<<< orphan*/  init_mm ; 
 int kmap_atomic_idx () ; 
 int /*<<< orphan*/  kmap_atomic_idx_pop () ; 
 scalar_t__ kmap_pte ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  pte_clear (int /*<<< orphan*/ *,unsigned long,scalar_t__) ; 
 int smp_processor_id () ; 

void __kunmap_atomic(void *kvaddr)
{
	unsigned long vaddr = (unsigned long) kvaddr & PAGE_MASK;
	int idx;

	if (vaddr < FIXADDR_START)
		goto out;

#ifdef CONFIG_DEBUG_HIGHMEM
	idx = KM_TYPE_NR*smp_processor_id() + kmap_atomic_idx();

	BUG_ON(vaddr != __fix_to_virt(FIX_KMAP_BEGIN + idx));

	pte_clear(&init_mm, vaddr, kmap_pte - idx);
	flush_tlb_one(vaddr);
#else
	(void) idx; /* to kill a warning */
#endif
	kmap_atomic_idx_pop();
out:
	pagefault_enable();
	preempt_enable();
}