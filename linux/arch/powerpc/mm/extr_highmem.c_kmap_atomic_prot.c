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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DEBUG_HIGHMEM ; 
 scalar_t__ FIX_KMAP_BEGIN ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int KM_TYPE_NR ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long __fix_to_virt (scalar_t__) ; 
 int /*<<< orphan*/  __set_pte_at (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_mm ; 
 int kmap_atomic_idx_push () ; 
 int /*<<< orphan*/ * kmap_pte ; 
 int /*<<< orphan*/  local_flush_tlb_page (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

void *kmap_atomic_prot(struct page *page, pgprot_t prot)
{
	unsigned long vaddr;
	int idx, type;

	preempt_disable();
	pagefault_disable();
	if (!PageHighMem(page))
		return page_address(page);

	type = kmap_atomic_idx_push();
	idx = type + KM_TYPE_NR*smp_processor_id();
	vaddr = __fix_to_virt(FIX_KMAP_BEGIN + idx);
	WARN_ON(IS_ENABLED(CONFIG_DEBUG_HIGHMEM) && !pte_none(*(kmap_pte - idx)));
	__set_pte_at(&init_mm, vaddr, kmap_pte-idx, mk_pte(page, prot), 1);
	local_flush_tlb_page(NULL, vaddr);

	return (void*) vaddr;
}