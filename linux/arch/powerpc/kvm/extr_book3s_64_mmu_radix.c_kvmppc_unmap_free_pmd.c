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
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PMD_SHIFT ; 
 unsigned long PTRS_PER_PMD ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kvmppc_pmd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_unmap_free_pte (struct kvm*,int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  kvmppc_unmap_pte (struct kvm*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  pmd_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ pmd_is_leaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pte_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_unmap_free_pmd(struct kvm *kvm, pmd_t *pmd, bool full,
				  unsigned int lpid)
{
	unsigned long im;
	pmd_t *p = pmd;

	for (im = 0; im < PTRS_PER_PMD; ++im, ++p) {
		if (!pmd_present(*p))
			continue;
		if (pmd_is_leaf(*p)) {
			if (full) {
				pmd_clear(p);
			} else {
				WARN_ON_ONCE(1);
				kvmppc_unmap_pte(kvm, (pte_t *)p,
					 pte_pfn(*(pte_t *)p) << PAGE_SHIFT,
					 PMD_SHIFT, NULL, lpid);
			}
		} else {
			pte_t *pte;

			pte = pte_offset_map(p, 0);
			kvmppc_unmap_free_pte(kvm, pte, full, lpid);
			pmd_clear(p);
		}
	}
	kvmppc_pmd_free(pmd);
}