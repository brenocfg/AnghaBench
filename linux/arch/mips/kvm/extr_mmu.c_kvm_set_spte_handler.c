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
struct kvm_memory_slot {int flags; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int gpa_t ;
typedef  int gfn_t ;

/* Variables and functions */
 int KVM_MEM_LOG_DIRTY_PAGES ; 
 int KVM_MEM_READONLY ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/ * kvm_mips_pte_for_gpa (struct kvm*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pte_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkclean (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_wrprotect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_young (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_set_spte_handler(struct kvm *kvm, gfn_t gfn, gfn_t gfn_end,
				struct kvm_memory_slot *memslot, void *data)
{
	gpa_t gpa = gfn << PAGE_SHIFT;
	pte_t hva_pte = *(pte_t *)data;
	pte_t *gpa_pte = kvm_mips_pte_for_gpa(kvm, NULL, gpa);
	pte_t old_pte;

	if (!gpa_pte)
		return 0;

	/* Mapping may need adjusting depending on memslot flags */
	old_pte = *gpa_pte;
	if (memslot->flags & KVM_MEM_LOG_DIRTY_PAGES && !pte_dirty(old_pte))
		hva_pte = pte_mkclean(hva_pte);
	else if (memslot->flags & KVM_MEM_READONLY)
		hva_pte = pte_wrprotect(hva_pte);

	set_pte(gpa_pte, hva_pte);

	/* Replacing an absent or old page doesn't need flushes */
	if (!pte_present(old_pte) || !pte_young(old_pte))
		return 0;

	/* Pages swapped, aged, moved, or cleaned require flushes */
	return !pte_present(hva_pte) ||
	       !pte_young(hva_pte) ||
	       pte_pfn(old_pte) != pte_pfn(hva_pte) ||
	       (pte_dirty(old_pte) && !pte_dirty(hva_pte));
}