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
 int /*<<< orphan*/  kvmppc_radix_flush_pwc (struct kvm*,unsigned int) ; 
 int /*<<< orphan*/  kvmppc_unmap_free_pte (struct kvm*,int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  pmd_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_unmap_free_pmd_entry_table(struct kvm *kvm, pmd_t *pmd,
					unsigned long gpa, unsigned int lpid)
{
	pte_t *pte = pte_offset_kernel(pmd, 0);

	/*
	 * Clearing the pmd entry then flushing the PWC ensures that the pte
	 * page no longer be cached by the MMU, so can be freed without
	 * flushing the PWC again.
	 */
	pmd_clear(pmd);
	kvmppc_radix_flush_pwc(kvm, lpid);

	kvmppc_unmap_free_pte(kvm, pte, false, lpid);
}