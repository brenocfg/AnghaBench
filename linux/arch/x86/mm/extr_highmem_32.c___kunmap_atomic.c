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
 scalar_t__ FIX_KMAP_BEGIN ; 
 scalar_t__ FIX_KMAP_END ; 
 int KM_TYPE_NR ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_OFFSET ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 unsigned long __fix_to_virt (scalar_t__) ; 
 int /*<<< orphan*/  arch_flush_lazy_mmu_mode () ; 
 scalar_t__ high_memory ; 
 int kmap_atomic_idx () ; 
 int /*<<< orphan*/  kmap_atomic_idx_pop () ; 
 scalar_t__ kmap_pte ; 
 int /*<<< orphan*/  kpte_clear_flush (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int smp_processor_id () ; 

void __kunmap_atomic(void *kvaddr)
{
	unsigned long vaddr = (unsigned long) kvaddr & PAGE_MASK;

	if (vaddr >= __fix_to_virt(FIX_KMAP_END) &&
	    vaddr <= __fix_to_virt(FIX_KMAP_BEGIN)) {
		int idx, type;

		type = kmap_atomic_idx();
		idx = type + KM_TYPE_NR * smp_processor_id();

#ifdef CONFIG_DEBUG_HIGHMEM
		WARN_ON_ONCE(vaddr != __fix_to_virt(FIX_KMAP_BEGIN + idx));
#endif
		/*
		 * Force other mappings to Oops if they'll try to access this
		 * pte without first remap it.  Keeping stale mappings around
		 * is a bad idea also, in case the page changes cacheability
		 * attributes or becomes a protected page in a hypervisor.
		 */
		kpte_clear_flush(kmap_pte-idx, vaddr);
		kmap_atomic_idx_pop();
		arch_flush_lazy_mmu_mode();
	}
#ifdef CONFIG_DEBUG_HIGHMEM
	else {
		BUG_ON(vaddr < PAGE_OFFSET);
		BUG_ON(vaddr >= (unsigned long)high_memory);
	}
#endif

	pagefault_enable();
	preempt_enable();
}