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
struct x86_exception {int /*<<< orphan*/  address; int /*<<< orphan*/  error_code; } ;
struct vmcs12 {int /*<<< orphan*/  vm_exit_intr_error_code; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nested_run_pending; } ;
struct TYPE_4__ {TYPE_1__ nested; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_REASON_EXCEPTION_NMI ; 
 int INTR_INFO_DELIVER_CODE_MASK ; 
 int INTR_INFO_VALID_MASK ; 
 int INTR_TYPE_HARD_EXCEPTION ; 
 int PF_VECTOR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_inject_page_fault (struct kvm_vcpu*,struct x86_exception*) ; 
 scalar_t__ nested_vmx_is_page_fault_vmexit (struct vmcs12*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_vmx_vmexit (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static void vmx_inject_page_fault_nested(struct kvm_vcpu *vcpu,
		struct x86_exception *fault)
{
	struct vmcs12 *vmcs12 = get_vmcs12(vcpu);

	WARN_ON(!is_guest_mode(vcpu));

	if (nested_vmx_is_page_fault_vmexit(vmcs12, fault->error_code) &&
		!to_vmx(vcpu)->nested.nested_run_pending) {
		vmcs12->vm_exit_intr_error_code = fault->error_code;
		nested_vmx_vmexit(vcpu, EXIT_REASON_EXCEPTION_NMI,
				  PF_VECTOR | INTR_TYPE_HARD_EXCEPTION |
				  INTR_INFO_DELIVER_CODE_MASK | INTR_INFO_VALID_MASK,
				  fault->address);
	} else {
		kvm_inject_page_fault(vcpu, fault);
	}
}