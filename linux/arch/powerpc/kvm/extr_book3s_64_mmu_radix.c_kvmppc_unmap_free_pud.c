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
struct kvm {int /*<<< orphan*/  mm; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long PTRS_PER_PUD ; 
 int /*<<< orphan*/  kvmppc_unmap_free_pmd (struct kvm*,int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pud_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pud_is_leaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_present (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_unmap_free_pud(struct kvm *kvm, pud_t *pud,
				  unsigned int lpid)
{
	unsigned long iu;
	pud_t *p = pud;

	for (iu = 0; iu < PTRS_PER_PUD; ++iu, ++p) {
		if (!pud_present(*p))
			continue;
		if (pud_is_leaf(*p)) {
			pud_clear(p);
		} else {
			pmd_t *pmd;

			pmd = pmd_offset(p, 0);
			kvmppc_unmap_free_pmd(kvm, pmd, true, lpid);
			pud_clear(p);
		}
	}
	pud_free(kvm->mm, pud);
}