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

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PTE_INDEX_SIZE ; 
 unsigned long PTRS_PER_PTE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kvmppc_pte_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_unmap_pte (struct kvm*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_unmap_free_pte(struct kvm *kvm, pte_t *pte, bool full,
				  unsigned int lpid)
{
	if (full) {
		memset(pte, 0, sizeof(long) << PTE_INDEX_SIZE);
	} else {
		pte_t *p = pte;
		unsigned long it;

		for (it = 0; it < PTRS_PER_PTE; ++it, ++p) {
			if (pte_val(*p) == 0)
				continue;
			WARN_ON_ONCE(1);
			kvmppc_unmap_pte(kvm, p,
					 pte_pfn(*p) << PAGE_SHIFT,
					 PAGE_SHIFT, NULL, lpid);
		}
	}

	kvmppc_pte_free(pte);
}