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
 int /*<<< orphan*/  CONFIG_DEBUG_HIGHMEM ; 
 scalar_t__ FIX_KMAP_BEGIN ; 
 scalar_t__ FIX_KMAP_END ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int KM_TYPE_NR ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long __fix_to_virt (scalar_t__) ; 
 int /*<<< orphan*/  init_mm ; 
 int kmap_atomic_idx () ; 
 int /*<<< orphan*/  kmap_atomic_idx_pop () ; 
 scalar_t__ kmap_pte ; 
 int /*<<< orphan*/  local_flush_tlb_page (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  pte_clear (int /*<<< orphan*/ *,unsigned long,scalar_t__) ; 
 int smp_processor_id () ; 

void __kunmap_atomic(void *kvaddr)
{
	unsigned long vaddr = (unsigned long) kvaddr & PAGE_MASK;

	if (vaddr < __fix_to_virt(FIX_KMAP_END)) {
		pagefault_enable();
		preempt_enable();
		return;
	}

	if (IS_ENABLED(CONFIG_DEBUG_HIGHMEM)) {
		int type = kmap_atomic_idx();
		unsigned int idx;

		idx = type + KM_TYPE_NR * smp_processor_id();
		WARN_ON(vaddr != __fix_to_virt(FIX_KMAP_BEGIN + idx));

		/*
		 * force other mappings to Oops if they'll try to access
		 * this pte without first remap it
		 */
		pte_clear(&init_mm, vaddr, kmap_pte-idx);
		local_flush_tlb_page(NULL, vaddr);
	}

	kmap_atomic_idx_pop();
	pagefault_enable();
	preempt_enable();
}