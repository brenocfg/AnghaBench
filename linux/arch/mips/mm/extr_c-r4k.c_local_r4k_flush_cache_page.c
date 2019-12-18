#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int vm_flags; struct mm_struct* vm_mm; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
struct flush_cache_page_args {unsigned long addr; int /*<<< orphan*/  pfn; struct vm_area_struct* vma; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_2__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  Page_dcache_dirty (struct page*) ; 
 int /*<<< orphan*/  R4K_HIT ; 
 int VM_EXEC ; 
 int _PAGE_VALID ; 
 scalar_t__ cpu_has_dc_aliases ; 
 int /*<<< orphan*/  cpu_has_ic_fills_f_dc ; 
 scalar_t__ cpu_has_vtag_icache ; 
 int /*<<< orphan*/  cpu_icache_snoops_remote_store ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  drop_mmu_context (struct mm_struct*) ; 
 int /*<<< orphan*/  has_valid_asid (struct mm_struct*,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*) ; 
 void* kmap_coherent (struct page*,unsigned long) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  kunmap_coherent () ; 
 scalar_t__ page_mapcount (struct page*) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pte_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  r4k_blast_dcache_page (unsigned long) ; 
 int /*<<< orphan*/  r4k_blast_dcache_user_page (unsigned long) ; 
 int /*<<< orphan*/  r4k_blast_icache_page (unsigned long) ; 
 int /*<<< orphan*/  r4k_blast_icache_user_page (unsigned long) ; 
 int /*<<< orphan*/  r4k_blast_scache_page (unsigned long) ; 

__attribute__((used)) static inline void local_r4k_flush_cache_page(void *args)
{
	struct flush_cache_page_args *fcp_args = args;
	struct vm_area_struct *vma = fcp_args->vma;
	unsigned long addr = fcp_args->addr;
	struct page *page = pfn_to_page(fcp_args->pfn);
	int exec = vma->vm_flags & VM_EXEC;
	struct mm_struct *mm = vma->vm_mm;
	int map_coherent = 0;
	pgd_t *pgdp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;
	void *vaddr;

	/*
	 * If owns no valid ASID yet, cannot possibly have gotten
	 * this page into the cache.
	 */
	if (!has_valid_asid(mm, R4K_HIT))
		return;

	addr &= PAGE_MASK;
	pgdp = pgd_offset(mm, addr);
	pudp = pud_offset(pgdp, addr);
	pmdp = pmd_offset(pudp, addr);
	ptep = pte_offset(pmdp, addr);

	/*
	 * If the page isn't marked valid, the page cannot possibly be
	 * in the cache.
	 */
	if (!(pte_present(*ptep)))
		return;

	if ((mm == current->active_mm) && (pte_val(*ptep) & _PAGE_VALID))
		vaddr = NULL;
	else {
		/*
		 * Use kmap_coherent or kmap_atomic to do flushes for
		 * another ASID than the current one.
		 */
		map_coherent = (cpu_has_dc_aliases &&
				page_mapcount(page) &&
				!Page_dcache_dirty(page));
		if (map_coherent)
			vaddr = kmap_coherent(page, addr);
		else
			vaddr = kmap_atomic(page);
		addr = (unsigned long)vaddr;
	}

	if (cpu_has_dc_aliases || (exec && !cpu_has_ic_fills_f_dc)) {
		vaddr ? r4k_blast_dcache_page(addr) :
			r4k_blast_dcache_user_page(addr);
		if (exec && !cpu_icache_snoops_remote_store)
			r4k_blast_scache_page(addr);
	}
	if (exec) {
		if (vaddr && cpu_has_vtag_icache && mm == current->active_mm) {
			drop_mmu_context(mm);
		} else
			vaddr ? r4k_blast_icache_page(addr) :
				r4k_blast_icache_user_page(addr);
	}

	if (vaddr) {
		if (map_coherent)
			kunmap_coherent();
		else
			kunmap_atomic(vaddr);
	}
}