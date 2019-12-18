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
typedef  scalar_t__ u32 ;
struct vcpu_svm {scalar_t__ dfr_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DFR ; 
 int /*<<< orphan*/  avic_invalidate_logical_id_entry (struct kvm_vcpu*) ; 
 scalar_t__ kvm_lapic_get_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void avic_handle_dfr_update(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	u32 dfr = kvm_lapic_get_reg(vcpu->arch.apic, APIC_DFR);

	if (svm->dfr_reg == dfr)
		return;

	avic_invalidate_logical_id_entry(vcpu);
	svm->dfr_reg = dfr;
}