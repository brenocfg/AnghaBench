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
struct mm_struct {int dummy; } ;
struct kmem_cache {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  hugepd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned long) ; 
 int /*<<< orphan*/  CONFIG_PPC_8xx ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int HUGEPD_SHIFT_MASK ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct kmem_cache* PGT_CACHE (unsigned int) ; 
 unsigned int PTE_INDEX_SIZE ; 
 unsigned int PTE_T_ORDER ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  __hugepd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hugepd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hugepd_populate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * kmem_cache_alloc (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (struct kmem_cache*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmemleak_ignore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgtable_gfp_flags (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __hugepte_alloc(struct mm_struct *mm, hugepd_t *hpdp,
			   unsigned long address, unsigned int pdshift,
			   unsigned int pshift, spinlock_t *ptl)
{
	struct kmem_cache *cachep;
	pte_t *new;
	int i;
	int num_hugepd;

	if (pshift >= pdshift) {
		cachep = PGT_CACHE(PTE_T_ORDER);
		num_hugepd = 1 << (pshift - pdshift);
	} else if (IS_ENABLED(CONFIG_PPC_8xx)) {
		cachep = PGT_CACHE(PTE_INDEX_SIZE);
		num_hugepd = 1;
	} else {
		cachep = PGT_CACHE(pdshift - pshift);
		num_hugepd = 1;
	}

	if (!cachep) {
		WARN_ONCE(1, "No page table cache created for hugetlb tables");
		return -ENOMEM;
	}

	new = kmem_cache_alloc(cachep, pgtable_gfp_flags(mm, GFP_KERNEL));

	BUG_ON(pshift > HUGEPD_SHIFT_MASK);
	BUG_ON((unsigned long)new & HUGEPD_SHIFT_MASK);

	if (!new)
		return -ENOMEM;

	/*
	 * Make sure other cpus find the hugepd set only after a
	 * properly initialized page table is visible to them.
	 * For more details look for comment in __pte_alloc().
	 */
	smp_wmb();

	spin_lock(ptl);
	/*
	 * We have multiple higher-level entries that point to the same
	 * actual pte location.  Fill in each as we go and backtrack on error.
	 * We need all of these so the DTLB pgtable walk code can find the
	 * right higher-level entry without knowing if it's a hugepage or not.
	 */
	for (i = 0; i < num_hugepd; i++, hpdp++) {
		if (unlikely(!hugepd_none(*hpdp)))
			break;
		hugepd_populate(hpdp, new, pshift);
	}
	/* If we bailed from the for loop early, an error occurred, clean up */
	if (i < num_hugepd) {
		for (i = i - 1 ; i >= 0; i--, hpdp--)
			*hpdp = __hugepd(0);
		kmem_cache_free(cachep, new);
	} else {
		kmemleak_ignore(new);
	}
	spin_unlock(ptl);
	return 0;
}