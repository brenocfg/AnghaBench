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
 unsigned long __fix_to_virt (int) ; 
 int /*<<< orphan*/  get_fixmap_pte (unsigned long) ; 
 int kmap_atomic_idx_push () ; 
 int /*<<< orphan*/  kmap_prot ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fixmap_pte (int,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

void *kmap_atomic_pfn(unsigned long pfn)
{
	unsigned long vaddr;
	int idx, type;
	struct page *page = pfn_to_page(pfn);

	preempt_disable();
	pagefault_disable();
	if (!PageHighMem(page))
		return page_address(page);

	type = kmap_atomic_idx_push();
	idx = FIX_KMAP_BEGIN + type + KM_TYPE_NR * smp_processor_id();
	vaddr = __fix_to_virt(idx);
#ifdef CONFIG_DEBUG_HIGHMEM
	BUG_ON(!pte_none(get_fixmap_pte(vaddr)));
#endif
	set_fixmap_pte(idx, pfn_pte(pfn, kmap_prot));

	return (void *)vaddr;
}