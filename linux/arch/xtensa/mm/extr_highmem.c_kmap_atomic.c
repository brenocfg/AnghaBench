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
typedef  enum fixed_addresses { ____Placeholder_fixed_addresses } fixed_addresses ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DCACHE_ALIAS (int /*<<< orphan*/ ) ; 
 int FIX_KMAP_BEGIN ; 
 int /*<<< orphan*/  PAGE_KERNEL_EXEC ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 unsigned long __fix_to_virt (int) ; 
 int /*<<< orphan*/  kmap_atomic_idx_push () ; 
 int kmap_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmap_pte ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *kmap_atomic(struct page *page)
{
	enum fixed_addresses idx;
	unsigned long vaddr;

	preempt_disable();
	pagefault_disable();
	if (!PageHighMem(page))
		return page_address(page);

	idx = kmap_idx(kmap_atomic_idx_push(),
		       DCACHE_ALIAS(page_to_phys(page)));
	vaddr = __fix_to_virt(FIX_KMAP_BEGIN + idx);
#ifdef CONFIG_DEBUG_HIGHMEM
	BUG_ON(!pte_none(*(kmap_pte + idx)));
#endif
	set_pte(kmap_pte + idx, mk_pte(page, PAGE_KERNEL_EXEC));

	return (void *)vaddr;
}