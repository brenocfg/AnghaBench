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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int FIX_KMAP_BEGIN ; 
 int KM_TYPE_NR ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 unsigned long __fix_to_virt (unsigned int) ; 
 int /*<<< orphan*/  cache_is_vivt () ; 
 int /*<<< orphan*/  get_fixmap_pte (unsigned long) ; 
 int kmap_atomic_idx_push () ; 
 void* kmap_high_get (struct page*) ; 
 int /*<<< orphan*/  kmap_prot ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fixmap_pte (unsigned int,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

void *kmap_atomic(struct page *page)
{
	unsigned int idx;
	unsigned long vaddr;
	void *kmap;
	int type;

	preempt_disable();
	pagefault_disable();
	if (!PageHighMem(page))
		return page_address(page);

#ifdef CONFIG_DEBUG_HIGHMEM
	/*
	 * There is no cache coherency issue when non VIVT, so force the
	 * dedicated kmap usage for better debugging purposes in that case.
	 */
	if (!cache_is_vivt())
		kmap = NULL;
	else
#endif
		kmap = kmap_high_get(page);
	if (kmap)
		return kmap;

	type = kmap_atomic_idx_push();

	idx = FIX_KMAP_BEGIN + type + KM_TYPE_NR * smp_processor_id();
	vaddr = __fix_to_virt(idx);
#ifdef CONFIG_DEBUG_HIGHMEM
	/*
	 * With debugging enabled, kunmap_atomic forces that entry to 0.
	 * Make sure it was indeed properly unmapped.
	 */
	BUG_ON(!pte_none(get_fixmap_pte(vaddr)));
#endif
	/*
	 * When debugging is off, kunmap_atomic leaves the previous mapping
	 * in place, so the contained TLB flush ensures the TLB is updated
	 * with the new mapping.
	 */
	set_fixmap_pte(idx, mk_pte(page, kmap_prot));

	return (void *)vaddr;
}