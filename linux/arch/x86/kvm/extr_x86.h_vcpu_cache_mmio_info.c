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
typedef  int u64 ;
struct TYPE_3__ {int mmio_gva; unsigned int mmio_access; int mmio_gen; int /*<<< orphan*/  mmio_gfn; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;
typedef  int gva_t ;
typedef  int /*<<< orphan*/  gfn_t ;
struct TYPE_4__ {int generation; } ;

/* Variables and functions */
 int KVM_MEMSLOT_GEN_UPDATE_IN_PROGRESS ; 
 int PAGE_MASK ; 
 TYPE_2__* kvm_memslots (int /*<<< orphan*/ ) ; 
 scalar_t__ mmu_is_nested (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void vcpu_cache_mmio_info(struct kvm_vcpu *vcpu,
					gva_t gva, gfn_t gfn, unsigned access)
{
	u64 gen = kvm_memslots(vcpu->kvm)->generation;

	if (unlikely(gen & KVM_MEMSLOT_GEN_UPDATE_IN_PROGRESS))
		return;

	/*
	 * If this is a shadow nested page table, the "GVA" is
	 * actually a nGPA.
	 */
	vcpu->arch.mmio_gva = mmu_is_nested(vcpu) ? 0 : gva & PAGE_MASK;
	vcpu->arch.mmio_access = access;
	vcpu->arch.mmio_gfn = gfn;
	vcpu->arch.mmio_gen = gen;
}