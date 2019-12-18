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
 scalar_t__ FIXADDR_START ; 
 int FIX_KMAP_BEGIN ; 
 int KM_TYPE_NR ; 
 int /*<<< orphan*/  LAST_PKMAP ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned long PKMAP_ADDR (int /*<<< orphan*/ ) ; 
 size_t PKMAP_NR (unsigned long) ; 
 int /*<<< orphan*/  __cpuc_flush_dcache_area (void*,int /*<<< orphan*/ ) ; 
 unsigned long __fix_to_virt (int) ; 
 int /*<<< orphan*/  __pte (int /*<<< orphan*/ ) ; 
 scalar_t__ cache_is_vivt () ; 
 int kmap_atomic_idx () ; 
 int /*<<< orphan*/  kmap_atomic_idx_pop () ; 
 int /*<<< orphan*/  kunmap_high (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/ * pkmap_page_table ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fixmap_pte (int,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

void __kunmap_atomic(void *kvaddr)
{
	unsigned long vaddr = (unsigned long) kvaddr & PAGE_MASK;
	int idx, type;

	if (kvaddr >= (void *)FIXADDR_START) {
		type = kmap_atomic_idx();
		idx = FIX_KMAP_BEGIN + type + KM_TYPE_NR * smp_processor_id();

		if (cache_is_vivt())
			__cpuc_flush_dcache_area((void *)vaddr, PAGE_SIZE);
#ifdef CONFIG_DEBUG_HIGHMEM
		BUG_ON(vaddr != __fix_to_virt(idx));
		set_fixmap_pte(idx, __pte(0));
#else
		(void) idx;  /* to kill a warning */
#endif
		kmap_atomic_idx_pop();
	} else if (vaddr >= PKMAP_ADDR(0) && vaddr < PKMAP_ADDR(LAST_PKMAP)) {
		/* this address was obtained through kmap_high_get() */
		kunmap_high(pte_page(pkmap_page_table[PKMAP_NR(vaddr)]));
	}
	pagefault_enable();
	preempt_enable();
}