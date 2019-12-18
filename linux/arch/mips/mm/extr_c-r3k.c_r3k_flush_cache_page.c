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
struct vm_area_struct {int vm_flags; struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long KSEG0ADDR (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int VM_EXEC ; 
 int _PAGE_PRESENT ; 
 scalar_t__ cpu_context (int /*<<< orphan*/ ,struct mm_struct*) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/ * pte_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  r3k_flush_dcache_range (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  r3k_flush_icache_range (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void r3k_flush_cache_page(struct vm_area_struct *vma,
				 unsigned long addr, unsigned long pfn)
{
	unsigned long kaddr = KSEG0ADDR(pfn << PAGE_SHIFT);
	int exec = vma->vm_flags & VM_EXEC;
	struct mm_struct *mm = vma->vm_mm;
	pgd_t *pgdp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	pr_debug("cpage[%08llx,%08lx]\n",
		 cpu_context(smp_processor_id(), mm), addr);

	/* No ASID => no such page in the cache.  */
	if (cpu_context(smp_processor_id(), mm) == 0)
		return;

	pgdp = pgd_offset(mm, addr);
	pudp = pud_offset(pgdp, addr);
	pmdp = pmd_offset(pudp, addr);
	ptep = pte_offset(pmdp, addr);

	/* Invalid => no such page in the cache.  */
	if (!(pte_val(*ptep) & _PAGE_PRESENT))
		return;

	r3k_flush_dcache_range(kaddr, kaddr + PAGE_SIZE);
	if (exec)
		r3k_flush_icache_range(kaddr, kaddr + PAGE_SIZE);
}