#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long* rmap; } ;
struct kvm_memory_slot {unsigned long base_gfn; TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/  pgtable; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long PTE_RPN_MASK ; 
 int /*<<< orphan*/  _PAGE_ACCESSED ; 
 int /*<<< orphan*/ * __find_linux_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  kvmhv_update_nest_rmap_rc_list (struct kvm*,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 unsigned long kvmppc_radix_update_pte (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_young (int /*<<< orphan*/ ) ; 

int kvm_age_radix(struct kvm *kvm, struct kvm_memory_slot *memslot,
		  unsigned long gfn)
{
	pte_t *ptep;
	unsigned long gpa = gfn << PAGE_SHIFT;
	unsigned int shift;
	int ref = 0;
	unsigned long old, *rmapp;

	ptep = __find_linux_pte(kvm->arch.pgtable, gpa, NULL, &shift);
	if (ptep && pte_present(*ptep) && pte_young(*ptep)) {
		old = kvmppc_radix_update_pte(kvm, ptep, _PAGE_ACCESSED, 0,
					      gpa, shift);
		/* XXX need to flush tlb here? */
		/* Also clear bit in ptes in shadow pgtable for nested guests */
		rmapp = &memslot->arch.rmap[gfn - memslot->base_gfn];
		kvmhv_update_nest_rmap_rc_list(kvm, rmapp, _PAGE_ACCESSED, 0,
					       old & PTE_RPN_MASK,
					       1UL << shift);
		ref = 1;
	}
	return ref;
}