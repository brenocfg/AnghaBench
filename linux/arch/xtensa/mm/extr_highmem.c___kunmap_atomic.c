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
 int /*<<< orphan*/  DCACHE_ALIAS (unsigned long) ; 
 scalar_t__ FIXADDR_START ; 
 scalar_t__ FIXADDR_TOP ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  kmap_atomic_idx () ; 
 int /*<<< orphan*/  kmap_atomic_idx_pop () ; 
 int kmap_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kmap_pte ; 
 int /*<<< orphan*/  local_flush_tlb_kernel_range (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  pte_clear (int /*<<< orphan*/ *,void*,scalar_t__) ; 

void __kunmap_atomic(void *kvaddr)
{
	if (kvaddr >= (void *)FIXADDR_START &&
	    kvaddr < (void *)FIXADDR_TOP) {
		int idx = kmap_idx(kmap_atomic_idx(),
				   DCACHE_ALIAS((unsigned long)kvaddr));

		/*
		 * Force other mappings to Oops if they'll try to access this
		 * pte without first remap it.  Keeping stale mappings around
		 * is a bad idea also, in case the page changes cacheability
		 * attributes or becomes a protected page in a hypervisor.
		 */
		pte_clear(&init_mm, kvaddr, kmap_pte + idx);
		local_flush_tlb_kernel_range((unsigned long)kvaddr,
					     (unsigned long)kvaddr + PAGE_SIZE);

		kmap_atomic_idx_pop();
	}

	pagefault_enable();
	preempt_enable();
}