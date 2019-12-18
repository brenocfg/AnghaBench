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
struct mm_struct {int /*<<< orphan*/  context; int /*<<< orphan*/ * pgd; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DBG_LOW (char*,struct mm_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long) ; 
 int HPTE_LOCAL_UPDATE ; 
 int H_PAGE_4K_PFN ; 
 scalar_t__ MMU_PAGE_64K ; 
 scalar_t__ USER_REGION_ID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long _PAGE_EXEC ; 
 unsigned long _PAGE_PRESENT ; 
 unsigned long _PAGE_READ ; 
 int __hash_page_4K (unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ *,unsigned long,int,int,int /*<<< orphan*/ ) ; 
 int __hash_page_64K (unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ *,unsigned long,int,int) ; 
 int /*<<< orphan*/ * find_current_mm_pte (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ get_region_id (unsigned long) ; 
 unsigned long get_user_vsid (int /*<<< orphan*/ *,unsigned long,int) ; 
 int /*<<< orphan*/  hash_failure_debug (unsigned long,unsigned long,unsigned long,unsigned long,int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ mm_ctx_user_psize (int /*<<< orphan*/ *) ; 
 scalar_t__ mm_is_thread_local (struct mm_struct*) ; 
 scalar_t__ pte_ci (int /*<<< orphan*/ ) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  should_hash_preload (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  subpage_protection (struct mm_struct*,unsigned long) ; 
 int user_segment_size (unsigned long) ; 

__attribute__((used)) static void hash_preload(struct mm_struct *mm, unsigned long ea,
			 bool is_exec, unsigned long trap)
{
	int hugepage_shift;
	unsigned long vsid;
	pgd_t *pgdir;
	pte_t *ptep;
	unsigned long flags;
	int rc, ssize, update_flags = 0;
	unsigned long access = _PAGE_PRESENT | _PAGE_READ | (is_exec ? _PAGE_EXEC : 0);

	BUG_ON(get_region_id(ea) != USER_REGION_ID);

	if (!should_hash_preload(mm, ea))
		return;

	DBG_LOW("hash_preload(mm=%p, mm->pgdir=%p, ea=%016lx, access=%lx,"
		" trap=%lx\n", mm, mm->pgd, ea, access, trap);

	/* Get Linux PTE if available */
	pgdir = mm->pgd;
	if (pgdir == NULL)
		return;

	/* Get VSID */
	ssize = user_segment_size(ea);
	vsid = get_user_vsid(&mm->context, ea, ssize);
	if (!vsid)
		return;
	/*
	 * Hash doesn't like irqs. Walking linux page table with irq disabled
	 * saves us from holding multiple locks.
	 */
	local_irq_save(flags);

	/*
	 * THP pages use update_mmu_cache_pmd. We don't do
	 * hash preload there. Hence can ignore THP here
	 */
	ptep = find_current_mm_pte(pgdir, ea, NULL, &hugepage_shift);
	if (!ptep)
		goto out_exit;

	WARN_ON(hugepage_shift);
#ifdef CONFIG_PPC_64K_PAGES
	/* If either H_PAGE_4K_PFN or cache inhibited is set (and we are on
	 * a 64K kernel), then we don't preload, hash_page() will take
	 * care of it once we actually try to access the page.
	 * That way we don't have to duplicate all of the logic for segment
	 * page size demotion here
	 */
	if ((pte_val(*ptep) & H_PAGE_4K_PFN) || pte_ci(*ptep))
		goto out_exit;
#endif /* CONFIG_PPC_64K_PAGES */

	/* Is that local to this CPU ? */
	if (mm_is_thread_local(mm))
		update_flags |= HPTE_LOCAL_UPDATE;

	/* Hash it in */
#ifdef CONFIG_PPC_64K_PAGES
	if (mm_ctx_user_psize(&mm->context) == MMU_PAGE_64K)
		rc = __hash_page_64K(ea, access, vsid, ptep, trap,
				     update_flags, ssize);
	else
#endif /* CONFIG_PPC_64K_PAGES */
		rc = __hash_page_4K(ea, access, vsid, ptep, trap, update_flags,
				    ssize, subpage_protection(mm, ea));

	/* Dump some info in case of hash insertion failure, they should
	 * never happen so it is really useful to know if/when they do
	 */
	if (rc == -1)
		hash_failure_debug(ea, access, vsid, trap, ssize,
				   mm_ctx_user_psize(&mm->context),
				   mm_ctx_user_psize(&mm->context),
				   pte_val(*ptep));
out_exit:
	local_irq_restore(flags);
}