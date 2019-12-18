#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kvm_memory_slot {unsigned long base_gfn; unsigned long npages; } ;
struct TYPE_2__ {int /*<<< orphan*/  lpid; int /*<<< orphan*/  pgtable; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ * __find_linux_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  kvmppc_unmap_pte (struct kvm*,int /*<<< orphan*/ *,unsigned long,unsigned int,struct kvm_memory_slot const*,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void kvmppc_radix_flush_memslot(struct kvm *kvm,
				const struct kvm_memory_slot *memslot)
{
	unsigned long n;
	pte_t *ptep;
	unsigned long gpa;
	unsigned int shift;

	gpa = memslot->base_gfn << PAGE_SHIFT;
	spin_lock(&kvm->mmu_lock);
	for (n = memslot->npages; n; --n) {
		ptep = __find_linux_pte(kvm->arch.pgtable, gpa, NULL, &shift);
		if (ptep && pte_present(*ptep))
			kvmppc_unmap_pte(kvm, ptep, gpa, shift, memslot,
					 kvm->arch.lpid);
		gpa += PAGE_SIZE;
	}
	spin_unlock(&kvm->mmu_lock);
}