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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_radix_flush_pwc (struct kvm*,unsigned int) ; 
 int /*<<< orphan*/  kvmppc_unmap_free_pmd (struct kvm*,int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvmppc_unmap_free_pud_entry_table(struct kvm *kvm, pud_t *pud,
					unsigned long gpa, unsigned int lpid)
{
	pmd_t *pmd = pmd_offset(pud, 0);

	/*
	 * Clearing the pud entry then flushing the PWC ensures that the pmd
	 * page and any children pte pages will no longer be cached by the MMU,
	 * so can be freed without flushing the PWC again.
	 */
	pud_clear(pud);
	kvmppc_radix_flush_pwc(kvm, lpid);

	kvmppc_unmap_free_pmd(kvm, pmd, false, lpid);
}