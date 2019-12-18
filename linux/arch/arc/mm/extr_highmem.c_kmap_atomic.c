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
 unsigned long FIXMAP_ADDR (int) ; 
 int KM_TYPE_NR ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 scalar_t__ fixmap_page_table ; 
 int /*<<< orphan*/  init_mm ; 
 int kmap_atomic_idx_push () ; 
 int /*<<< orphan*/  kmap_prot ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ *,unsigned long,scalar_t__,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

void *kmap_atomic(struct page *page)
{
	int idx, cpu_idx;
	unsigned long vaddr;

	preempt_disable();
	pagefault_disable();
	if (!PageHighMem(page))
		return page_address(page);

	cpu_idx = kmap_atomic_idx_push();
	idx = cpu_idx + KM_TYPE_NR * smp_processor_id();
	vaddr = FIXMAP_ADDR(idx);

	set_pte_at(&init_mm, vaddr, fixmap_page_table + idx,
		   mk_pte(page, kmap_prot));

	return (void *)vaddr;
}