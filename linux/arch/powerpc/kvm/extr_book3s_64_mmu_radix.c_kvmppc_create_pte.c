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
struct rmap_nested {int dummy; } ;
struct kvm {int /*<<< orphan*/  mm; int /*<<< orphan*/  mmu_lock; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 unsigned long PMD_MASK ; 
 int /*<<< orphan*/  PMD_SHIFT ; 
 int PTE_BITS_MUST_MATCH ; 
 unsigned long PUD_MASK ; 
 int /*<<< orphan*/  PUD_SHIFT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kvmhv_insert_nest_rmap (struct kvm*,unsigned long*,struct rmap_nested**) ; 
 int /*<<< orphan*/ * kvmppc_pmd_alloc () ; 
 int /*<<< orphan*/  kvmppc_pmd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvmppc_pte_alloc () ; 
 int /*<<< orphan*/  kvmppc_pte_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_radix_set_pte_at (struct kvm*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_radix_update_pte (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_unmap_free_pmd_entry_table (struct kvm*,int /*<<< orphan*/ *,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  kvmppc_unmap_free_pud_entry_table (struct kvm*,int /*<<< orphan*/ *,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  kvmppc_unmap_pte (struct kvm*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ mmu_notifier_retry (struct kvm*,unsigned long) ; 
 int pgd_index (unsigned long) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pgd_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_is_leaf (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pmd_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_raw (int /*<<< orphan*/ ) ; 
 int pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmdp_ptep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_raw (int /*<<< orphan*/ ) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_alloc_one (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pud_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pud_is_leaf (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pud_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_raw (int /*<<< orphan*/ ) ; 
 int pud_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int kvmppc_create_pte(struct kvm *kvm, pgd_t *pgtable, pte_t pte,
		      unsigned long gpa, unsigned int level,
		      unsigned long mmu_seq, unsigned int lpid,
		      unsigned long *rmapp, struct rmap_nested **n_rmap)
{
	pgd_t *pgd;
	pud_t *pud, *new_pud = NULL;
	pmd_t *pmd, *new_pmd = NULL;
	pte_t *ptep, *new_ptep = NULL;
	int ret;

	/* Traverse the guest's 2nd-level tree, allocate new levels needed */
	pgd = pgtable + pgd_index(gpa);
	pud = NULL;
	if (pgd_present(*pgd))
		pud = pud_offset(pgd, gpa);
	else
		new_pud = pud_alloc_one(kvm->mm, gpa);

	pmd = NULL;
	if (pud && pud_present(*pud) && !pud_is_leaf(*pud))
		pmd = pmd_offset(pud, gpa);
	else if (level <= 1)
		new_pmd = kvmppc_pmd_alloc();

	if (level == 0 && !(pmd && pmd_present(*pmd) && !pmd_is_leaf(*pmd)))
		new_ptep = kvmppc_pte_alloc();

	/* Check if we might have been invalidated; let the guest retry if so */
	spin_lock(&kvm->mmu_lock);
	ret = -EAGAIN;
	if (mmu_notifier_retry(kvm, mmu_seq))
		goto out_unlock;

	/* Now traverse again under the lock and change the tree */
	ret = -ENOMEM;
	if (pgd_none(*pgd)) {
		if (!new_pud)
			goto out_unlock;
		pgd_populate(kvm->mm, pgd, new_pud);
		new_pud = NULL;
	}
	pud = pud_offset(pgd, gpa);
	if (pud_is_leaf(*pud)) {
		unsigned long hgpa = gpa & PUD_MASK;

		/* Check if we raced and someone else has set the same thing */
		if (level == 2) {
			if (pud_raw(*pud) == pte_raw(pte)) {
				ret = 0;
				goto out_unlock;
			}
			/* Valid 1GB page here already, add our extra bits */
			WARN_ON_ONCE((pud_val(*pud) ^ pte_val(pte)) &
							PTE_BITS_MUST_MATCH);
			kvmppc_radix_update_pte(kvm, (pte_t *)pud,
					      0, pte_val(pte), hgpa, PUD_SHIFT);
			ret = 0;
			goto out_unlock;
		}
		/*
		 * If we raced with another CPU which has just put
		 * a 1GB pte in after we saw a pmd page, try again.
		 */
		if (!new_pmd) {
			ret = -EAGAIN;
			goto out_unlock;
		}
		/* Valid 1GB page here already, remove it */
		kvmppc_unmap_pte(kvm, (pte_t *)pud, hgpa, PUD_SHIFT, NULL,
				 lpid);
	}
	if (level == 2) {
		if (!pud_none(*pud)) {
			/*
			 * There's a page table page here, but we wanted to
			 * install a large page, so remove and free the page
			 * table page.
			 */
			kvmppc_unmap_free_pud_entry_table(kvm, pud, gpa, lpid);
		}
		kvmppc_radix_set_pte_at(kvm, gpa, (pte_t *)pud, pte);
		if (rmapp && n_rmap)
			kvmhv_insert_nest_rmap(kvm, rmapp, n_rmap);
		ret = 0;
		goto out_unlock;
	}
	if (pud_none(*pud)) {
		if (!new_pmd)
			goto out_unlock;
		pud_populate(kvm->mm, pud, new_pmd);
		new_pmd = NULL;
	}
	pmd = pmd_offset(pud, gpa);
	if (pmd_is_leaf(*pmd)) {
		unsigned long lgpa = gpa & PMD_MASK;

		/* Check if we raced and someone else has set the same thing */
		if (level == 1) {
			if (pmd_raw(*pmd) == pte_raw(pte)) {
				ret = 0;
				goto out_unlock;
			}
			/* Valid 2MB page here already, add our extra bits */
			WARN_ON_ONCE((pmd_val(*pmd) ^ pte_val(pte)) &
							PTE_BITS_MUST_MATCH);
			kvmppc_radix_update_pte(kvm, pmdp_ptep(pmd),
					0, pte_val(pte), lgpa, PMD_SHIFT);
			ret = 0;
			goto out_unlock;
		}

		/*
		 * If we raced with another CPU which has just put
		 * a 2MB pte in after we saw a pte page, try again.
		 */
		if (!new_ptep) {
			ret = -EAGAIN;
			goto out_unlock;
		}
		/* Valid 2MB page here already, remove it */
		kvmppc_unmap_pte(kvm, pmdp_ptep(pmd), lgpa, PMD_SHIFT, NULL,
				 lpid);
	}
	if (level == 1) {
		if (!pmd_none(*pmd)) {
			/*
			 * There's a page table page here, but we wanted to
			 * install a large page, so remove and free the page
			 * table page.
			 */
			kvmppc_unmap_free_pmd_entry_table(kvm, pmd, gpa, lpid);
		}
		kvmppc_radix_set_pte_at(kvm, gpa, pmdp_ptep(pmd), pte);
		if (rmapp && n_rmap)
			kvmhv_insert_nest_rmap(kvm, rmapp, n_rmap);
		ret = 0;
		goto out_unlock;
	}
	if (pmd_none(*pmd)) {
		if (!new_ptep)
			goto out_unlock;
		pmd_populate(kvm->mm, pmd, new_ptep);
		new_ptep = NULL;
	}
	ptep = pte_offset_kernel(pmd, gpa);
	if (pte_present(*ptep)) {
		/* Check if someone else set the same thing */
		if (pte_raw(*ptep) == pte_raw(pte)) {
			ret = 0;
			goto out_unlock;
		}
		/* Valid page here already, add our extra bits */
		WARN_ON_ONCE((pte_val(*ptep) ^ pte_val(pte)) &
							PTE_BITS_MUST_MATCH);
		kvmppc_radix_update_pte(kvm, ptep, 0, pte_val(pte), gpa, 0);
		ret = 0;
		goto out_unlock;
	}
	kvmppc_radix_set_pte_at(kvm, gpa, ptep, pte);
	if (rmapp && n_rmap)
		kvmhv_insert_nest_rmap(kvm, rmapp, n_rmap);
	ret = 0;

 out_unlock:
	spin_unlock(&kvm->mmu_lock);
	if (new_pud)
		pud_free(kvm->mm, new_pud);
	if (new_pmd)
		kvmppc_pmd_free(new_pmd);
	if (new_ptep)
		kvmppc_pte_free(new_ptep);
	return ret;
}