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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long _PAGE_ACCESSED ; 
 unsigned long _PAGE_DIRTY ; 
 int /*<<< orphan*/ * __find_linux_pte (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  kvmppc_radix_update_pte (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned int) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_write (int /*<<< orphan*/ ) ; 

bool kvmppc_hv_handle_set_rc(struct kvm *kvm, pgd_t *pgtable, bool writing,
			     unsigned long gpa, unsigned int lpid)
{
	unsigned long pgflags;
	unsigned int shift;
	pte_t *ptep;

	/*
	 * Need to set an R or C bit in the 2nd-level tables;
	 * since we are just helping out the hardware here,
	 * it is sufficient to do what the hardware does.
	 */
	pgflags = _PAGE_ACCESSED;
	if (writing)
		pgflags |= _PAGE_DIRTY;
	/*
	 * We are walking the secondary (partition-scoped) page table here.
	 * We can do this without disabling irq because the Linux MM
	 * subsystem doesn't do THP splits and collapses on this tree.
	 */
	ptep = __find_linux_pte(pgtable, gpa, NULL, &shift);
	if (ptep && pte_present(*ptep) && (!writing || pte_write(*ptep))) {
		kvmppc_radix_update_pte(kvm, ptep, 0, pgflags, gpa, shift);
		return true;
	}
	return false;
}