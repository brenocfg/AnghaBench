#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {scalar_t__ vm_mm; int vm_flags; } ;
struct page {int /*<<< orphan*/  flags; } ;
struct flusher_data {unsigned long addr1; unsigned long addr2; struct vm_area_struct* vma; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_6__ {scalar_t__ active_mm; } ;
struct TYPE_4__ {scalar_t__ n_aliases; } ;
struct TYPE_5__ {TYPE_1__ dcache; } ;

/* Variables and functions */
 unsigned long CACHE_OC_ADDRESS_ARRAY ; 
 scalar_t__ NO_CONTEXT ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PG_dcache_clean ; 
 int VM_EXEC ; 
 int _PAGE_PRESENT ; 
 scalar_t__ cpu_context (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* current ; 
 TYPE_2__ current_cpu_data ; 
 int /*<<< orphan*/  flush_cache_one (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_icache_all () ; 
 void* kmap_atomic (struct page*) ; 
 void* kmap_coherent (struct page*,unsigned long) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  kunmap_coherent (void*) ; 
 scalar_t__ page_mapcount (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/ * pgd_offset (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long shm_align_mask ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sh4_flush_cache_page(void *args)
{
	struct flusher_data *data = args;
	struct vm_area_struct *vma;
	struct page *page;
	unsigned long address, pfn, phys;
	int map_coherent = 0;
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	void *vaddr;

	vma = data->vma;
	address = data->addr1 & PAGE_MASK;
	pfn = data->addr2;
	phys = pfn << PAGE_SHIFT;
	page = pfn_to_page(pfn);

	if (cpu_context(smp_processor_id(), vma->vm_mm) == NO_CONTEXT)
		return;

	pgd = pgd_offset(vma->vm_mm, address);
	pud = pud_offset(pgd, address);
	pmd = pmd_offset(pud, address);
	pte = pte_offset_kernel(pmd, address);

	/* If the page isn't present, there is nothing to do here. */
	if (!(pte_val(*pte) & _PAGE_PRESENT))
		return;

	if ((vma->vm_mm == current->active_mm))
		vaddr = NULL;
	else {
		/*
		 * Use kmap_coherent or kmap_atomic to do flushes for
		 * another ASID than the current one.
		 */
		map_coherent = (current_cpu_data.dcache.n_aliases &&
			test_bit(PG_dcache_clean, &page->flags) &&
			page_mapcount(page));
		if (map_coherent)
			vaddr = kmap_coherent(page, address);
		else
			vaddr = kmap_atomic(page);

		address = (unsigned long)vaddr;
	}

	flush_cache_one(CACHE_OC_ADDRESS_ARRAY |
			(address & shm_align_mask), phys);

	if (vma->vm_flags & VM_EXEC)
		flush_icache_all();

	if (vaddr) {
		if (map_coherent)
			kunmap_coherent(vaddr);
		else
			kunmap_atomic(vaddr);
	}
}