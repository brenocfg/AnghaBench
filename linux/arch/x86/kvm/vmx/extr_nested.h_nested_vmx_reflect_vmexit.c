#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vmcs12 {void* vm_exit_intr_error_code; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_QUALIFICATION ; 
 scalar_t__ EXIT_REASON_EXTERNAL_INTERRUPT ; 
 scalar_t__ INTR_INFO_DELIVER_CODE_MASK ; 
 scalar_t__ INTR_INFO_VALID_MASK ; 
 int /*<<< orphan*/  VM_EXIT_INTR_ERROR_CODE ; 
 int /*<<< orphan*/  VM_EXIT_INTR_INFO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_vmexit (struct kvm_vcpu*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 void* vmcs_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int nested_vmx_reflect_vmexit(struct kvm_vcpu *vcpu,
					    u32 exit_reason)
{
	u32 exit_intr_info = vmcs_read32(VM_EXIT_INTR_INFO);

	/*
	 * At this point, the exit interruption info in exit_intr_info
	 * is only valid for EXCEPTION_NMI exits.  For EXTERNAL_INTERRUPT
	 * we need to query the in-kernel LAPIC.
	 */
	WARN_ON(exit_reason == EXIT_REASON_EXTERNAL_INTERRUPT);
	if ((exit_intr_info &
	     (INTR_INFO_VALID_MASK | INTR_INFO_DELIVER_CODE_MASK)) ==
	    (INTR_INFO_VALID_MASK | INTR_INFO_DELIVER_CODE_MASK)) {
		struct vmcs12 *vmcs12 = get_vmcs12(vcpu);

		vmcs12->vm_exit_intr_error_code =
			vmcs_read32(VM_EXIT_INTR_ERROR_CODE);
	}

	nested_vmx_vmexit(vcpu, exit_reason, exit_intr_info,
			  vmcs_readl(EXIT_QUALIFICATION));
	return 1;
}