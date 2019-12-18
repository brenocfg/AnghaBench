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
struct kvm_memory_slot {int base_gfn; TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/  lpid; int /*<<< orphan*/  pgtable; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long PTE_RPN_MASK ; 
 int /*<<< orphan*/  _PAGE_DIRTY ; 
 int /*<<< orphan*/ * __find_linux_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  kvmhv_update_nest_rmap_rc_list (struct kvm*,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  kvmppc_radix_tlbie_page (struct kvm*,unsigned long,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long kvmppc_radix_update_pte (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 scalar_t__ pte_dirty (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_radix_test_clear_dirty(struct kvm *kvm,
				struct kvm_memory_slot *memslot, int pagenum)
{
	unsigned long gfn = memslot->base_gfn + pagenum;
	unsigned long gpa = gfn << PAGE_SHIFT;
	pte_t *ptep;
	unsigned int shift;
	int ret = 0;
	unsigned long old, *rmapp;

	ptep = __find_linux_pte(kvm->arch.pgtable, gpa, NULL, &shift);
	if (ptep && pte_present(*ptep) && pte_dirty(*ptep)) {
		ret = 1;
		if (shift)
			ret = 1 << (shift - PAGE_SHIFT);
		spin_lock(&kvm->mmu_lock);
		old = kvmppc_radix_update_pte(kvm, ptep, _PAGE_DIRTY, 0,
					      gpa, shift);
		kvmppc_radix_tlbie_page(kvm, gpa, shift, kvm->arch.lpid);
		/* Also clear bit in ptes in shadow pgtable for nested guests */
		rmapp = &memslot->arch.rmap[gfn - memslot->base_gfn];
		kvmhv_update_nest_rmap_rc_list(kvm, rmapp, _PAGE_DIRTY, 0,
					       old & PTE_RPN_MASK,
					       1UL << shift);
		spin_unlock(&kvm->mmu_lock);
	}
	return ret;
}