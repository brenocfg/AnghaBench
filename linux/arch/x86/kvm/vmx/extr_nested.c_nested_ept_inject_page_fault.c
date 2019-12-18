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
typedef  int /*<<< orphan*/  u32 ;
struct x86_exception {int error_code; int /*<<< orphan*/  address; } ;
struct vmcs12 {int /*<<< orphan*/  guest_physical_address; } ;
struct TYPE_4__ {int pml_full; } ;
struct vcpu_vmx {TYPE_2__ nested; } ;
struct TYPE_3__ {unsigned long exit_qualification; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_REASON_EPT_MISCONFIG ; 
 int /*<<< orphan*/  EXIT_REASON_EPT_VIOLATION ; 
 int /*<<< orphan*/  EXIT_REASON_PML_FULL ; 
 unsigned long INTR_INFO_UNBLOCK_NMI ; 
 int PFERR_RSVD_MASK ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_vmexit (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static void nested_ept_inject_page_fault(struct kvm_vcpu *vcpu,
		struct x86_exception *fault)
{
	struct vmcs12 *vmcs12 = get_vmcs12(vcpu);
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	u32 exit_reason;
	unsigned long exit_qualification = vcpu->arch.exit_qualification;

	if (vmx->nested.pml_full) {
		exit_reason = EXIT_REASON_PML_FULL;
		vmx->nested.pml_full = false;
		exit_qualification &= INTR_INFO_UNBLOCK_NMI;
	} else if (fault->error_code & PFERR_RSVD_MASK)
		exit_reason = EXIT_REASON_EPT_MISCONFIG;
	else
		exit_reason = EXIT_REASON_EPT_VIOLATION;

	nested_vmx_vmexit(vcpu, exit_reason, 0, exit_qualification);
	vmcs12->guest_physical_address = fault->address;
}