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
typedef  int u64 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int generation; } ;

/* Variables and functions */
 int KVM_MEMSLOT_GEN_UPDATE_IN_PROGRESS ; 
 int MMIO_SPTE_GEN_MASK ; 
 int get_mmio_spte_generation (int) ; 
 TYPE_1__* kvm_vcpu_memslots (struct kvm_vcpu*) ; 
 int likely (int) ; 
 int /*<<< orphan*/  trace_check_mmio_spte (int,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool check_mmio_spte(struct kvm_vcpu *vcpu, u64 spte)
{
	u64 kvm_gen, spte_gen, gen;

	gen = kvm_vcpu_memslots(vcpu)->generation;
	if (unlikely(gen & KVM_MEMSLOT_GEN_UPDATE_IN_PROGRESS))
		return false;

	kvm_gen = gen & MMIO_SPTE_GEN_MASK;
	spte_gen = get_mmio_spte_generation(spte);

	trace_check_mmio_spte(spte, kvm_gen, spte_gen);
	return likely(kvm_gen == spte_gen);
}