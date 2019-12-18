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
typedef  unsigned long long u64 ;
typedef  scalar_t__ u32 ;
struct vcpu_svm {unsigned long long* avic_physical_id_cache; scalar_t__ ldr_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  apic; } ;
struct kvm_vcpu {scalar_t__ vcpu_id; TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long long* avic_get_physical_id_entry (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  avic_handle_ldr_update (struct kvm_vcpu*) ; 
 scalar_t__ kvm_xapic_id (int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static int avic_handle_apic_id_update(struct kvm_vcpu *vcpu)
{
	u64 *old, *new;
	struct vcpu_svm *svm = to_svm(vcpu);
	u32 id = kvm_xapic_id(vcpu->arch.apic);

	if (vcpu->vcpu_id == id)
		return 0;

	old = avic_get_physical_id_entry(vcpu, vcpu->vcpu_id);
	new = avic_get_physical_id_entry(vcpu, id);
	if (!new || !old)
		return 1;

	/* We need to move physical_id_entry to new offset */
	*new = *old;
	*old = 0ULL;
	to_svm(vcpu)->avic_physical_id_cache = new;

	/*
	 * Also update the guest physical APIC ID in the logical
	 * APIC ID table entry if already setup the LDR.
	 */
	if (svm->ldr_reg)
		avic_handle_ldr_update(vcpu);

	return 0;
}