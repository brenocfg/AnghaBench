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
struct TYPE_2__ {int /*<<< orphan*/  pgdir; } ;
struct kvm_vcpu {TYPE_1__ arch; struct kvm* kvm; } ;
struct kvm_memory_slot {int flags; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int H_PARAMETER ; 
 int H_SUCCESS ; 
 int H_TOO_HARD ; 
 int KVM_MEMSLOT_INVALID ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/ * __find_linux_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,unsigned int*) ; 
 unsigned long __gfn_to_hva_memslot (struct kvm_memory_slot*,unsigned long) ; 
 struct kvm_memory_slot* __gfn_to_memslot (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  kvm_memslots_raw (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_read_update_linux_pte (int /*<<< orphan*/ *,int) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvmppc_get_hpa(struct kvm_vcpu *vcpu, unsigned long gpa,
			  int writing, unsigned long *hpa,
			  struct kvm_memory_slot **memslot_p)
{
	struct kvm *kvm = vcpu->kvm;
	struct kvm_memory_slot *memslot;
	unsigned long gfn, hva, pa, psize = PAGE_SHIFT;
	unsigned int shift;
	pte_t *ptep, pte;

	/* Find the memslot for this address */
	gfn = gpa >> PAGE_SHIFT;
	memslot = __gfn_to_memslot(kvm_memslots_raw(kvm), gfn);
	if (!memslot || (memslot->flags & KVM_MEMSLOT_INVALID))
		return H_PARAMETER;

	/* Translate to host virtual address */
	hva = __gfn_to_hva_memslot(memslot, gfn);

	/* Try to find the host pte for that virtual address */
	ptep = __find_linux_pte(vcpu->arch.pgdir, hva, NULL, &shift);
	if (!ptep)
		return H_TOO_HARD;
	pte = kvmppc_read_update_linux_pte(ptep, writing);
	if (!pte_present(pte))
		return H_TOO_HARD;

	/* Convert to a physical address */
	if (shift)
		psize = 1UL << shift;
	pa = pte_pfn(pte) << PAGE_SHIFT;
	pa |= hva & (psize - 1);
	pa |= gpa & ~PAGE_MASK;

	if (hpa)
		*hpa = pa;
	if (memslot_p)
		*memslot_p = memslot;

	return H_SUCCESS;
}