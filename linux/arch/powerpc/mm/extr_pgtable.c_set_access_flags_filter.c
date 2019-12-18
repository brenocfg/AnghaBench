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
struct vm_area_struct {int vm_flags; } ;
struct page {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_FTR_HPTE_TABLE ; 
 int /*<<< orphan*/  PG_arch_1 ; 
 int VM_EXEC ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  flush_dcache_icache_page (struct page*) ; 
 int /*<<< orphan*/  is_exec_fault () ; 
 struct page* maybe_pte_to_page (int /*<<< orphan*/ ) ; 
 scalar_t__ mmu_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_exec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static pte_t set_access_flags_filter(pte_t pte, struct vm_area_struct *vma,
				     int dirty)
{
	struct page *pg;

	if (mmu_has_feature(MMU_FTR_HPTE_TABLE))
		return pte;

	/* So here, we only care about exec faults, as we use them
	 * to recover lost _PAGE_EXEC and perform I$/D$ coherency
	 * if necessary. Also if _PAGE_EXEC is already set, same deal,
	 * we just bail out
	 */
	if (dirty || pte_exec(pte) || !is_exec_fault())
		return pte;

#ifdef CONFIG_DEBUG_VM
	/* So this is an exec fault, _PAGE_EXEC is not set. If it was
	 * an error we would have bailed out earlier in do_page_fault()
	 * but let's make sure of it
	 */
	if (WARN_ON(!(vma->vm_flags & VM_EXEC)))
		return pte;
#endif /* CONFIG_DEBUG_VM */

	/* If you set _PAGE_EXEC on weird pages you're on your own */
	pg = maybe_pte_to_page(pte);
	if (unlikely(!pg))
		goto bail;

	/* If the page is already clean, we move on */
	if (test_bit(PG_arch_1, &pg->flags))
		goto bail;

	/* Clean the page and set PG_arch_1 */
	flush_dcache_icache_page(pg);
	set_bit(PG_arch_1, &pg->flags);

 bail:
	return pte_mkexec(pte);
}