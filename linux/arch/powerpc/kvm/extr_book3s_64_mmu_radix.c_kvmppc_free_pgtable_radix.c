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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long PTRS_PER_PGD ; 
 int /*<<< orphan*/  kvmppc_unmap_free_pud (struct kvm*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  pgd_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void kvmppc_free_pgtable_radix(struct kvm *kvm, pgd_t *pgd, unsigned int lpid)
{
	unsigned long ig;

	for (ig = 0; ig < PTRS_PER_PGD; ++ig, ++pgd) {
		pud_t *pud;

		if (!pgd_present(*pgd))
			continue;
		pud = pud_offset(pgd, 0);
		kvmppc_unmap_free_pud(kvm, pud, lpid);
		pgd_clear(pgd);
	}
}