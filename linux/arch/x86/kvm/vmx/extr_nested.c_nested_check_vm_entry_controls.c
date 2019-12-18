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
typedef  int u8 ;
typedef  int u32 ;
struct vmcs12 {int vm_entry_intr_info_field; int guest_cr0; int vm_entry_exception_error_code; int vm_entry_instruction_len; int /*<<< orphan*/  vm_entry_controls; } ;
struct TYPE_3__ {int /*<<< orphan*/  entry_ctls_high; int /*<<< orphan*/  entry_ctls_low; } ;
struct TYPE_4__ {TYPE_1__ msrs; } ;
struct vcpu_vmx {TYPE_2__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ CC (int) ; 
 int EINVAL ; 
 int GENMASK (int,int) ; 
 int INTR_INFO_DELIVER_CODE_MASK ; 
 int INTR_INFO_INTR_TYPE_MASK ; 
 int INTR_INFO_RESVD_BITS_MASK ; 
 int INTR_INFO_VALID_MASK ; 
 int INTR_INFO_VECTOR_MASK ; 
 int INTR_TYPE_HARD_EXCEPTION ; 
 int INTR_TYPE_NMI_INTR ; 
 int INTR_TYPE_OTHER_EVENT ; 
#define  INTR_TYPE_PRIV_SW_EXCEPTION 130 
 int INTR_TYPE_RESERVED ; 
#define  INTR_TYPE_SOFT_EXCEPTION 129 
#define  INTR_TYPE_SOFT_INTR 128 
 int NMI_VECTOR ; 
 int /*<<< orphan*/  SECONDARY_EXEC_UNRESTRICTED_GUEST ; 
 int X86_CR0_PE ; 
 int nested_cpu_has2 (struct vmcs12*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_cpu_has_zero_length_injection (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_cpu_supports_monitor_trap_flag (struct kvm_vcpu*) ; 
 scalar_t__ nested_vmx_check_entry_msr_switch_controls (struct kvm_vcpu*,struct vmcs12*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_control_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ x86_exception_has_error_code (int) ; 

__attribute__((used)) static int nested_check_vm_entry_controls(struct kvm_vcpu *vcpu,
					  struct vmcs12 *vmcs12)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	if (CC(!vmx_control_verify(vmcs12->vm_entry_controls,
				    vmx->nested.msrs.entry_ctls_low,
				    vmx->nested.msrs.entry_ctls_high)))
		return -EINVAL;

	/*
	 * From the Intel SDM, volume 3:
	 * Fields relevant to VM-entry event injection must be set properly.
	 * These fields are the VM-entry interruption-information field, the
	 * VM-entry exception error code, and the VM-entry instruction length.
	 */
	if (vmcs12->vm_entry_intr_info_field & INTR_INFO_VALID_MASK) {
		u32 intr_info = vmcs12->vm_entry_intr_info_field;
		u8 vector = intr_info & INTR_INFO_VECTOR_MASK;
		u32 intr_type = intr_info & INTR_INFO_INTR_TYPE_MASK;
		bool has_error_code = intr_info & INTR_INFO_DELIVER_CODE_MASK;
		bool should_have_error_code;
		bool urg = nested_cpu_has2(vmcs12,
					   SECONDARY_EXEC_UNRESTRICTED_GUEST);
		bool prot_mode = !urg || vmcs12->guest_cr0 & X86_CR0_PE;

		/* VM-entry interruption-info field: interruption type */
		if (CC(intr_type == INTR_TYPE_RESERVED) ||
		    CC(intr_type == INTR_TYPE_OTHER_EVENT &&
		       !nested_cpu_supports_monitor_trap_flag(vcpu)))
			return -EINVAL;

		/* VM-entry interruption-info field: vector */
		if (CC(intr_type == INTR_TYPE_NMI_INTR && vector != NMI_VECTOR) ||
		    CC(intr_type == INTR_TYPE_HARD_EXCEPTION && vector > 31) ||
		    CC(intr_type == INTR_TYPE_OTHER_EVENT && vector != 0))
			return -EINVAL;

		/* VM-entry interruption-info field: deliver error code */
		should_have_error_code =
			intr_type == INTR_TYPE_HARD_EXCEPTION && prot_mode &&
			x86_exception_has_error_code(vector);
		if (CC(has_error_code != should_have_error_code))
			return -EINVAL;

		/* VM-entry exception error code */
		if (CC(has_error_code &&
		       vmcs12->vm_entry_exception_error_code & GENMASK(31, 16)))
			return -EINVAL;

		/* VM-entry interruption-info field: reserved bits */
		if (CC(intr_info & INTR_INFO_RESVD_BITS_MASK))
			return -EINVAL;

		/* VM-entry instruction length */
		switch (intr_type) {
		case INTR_TYPE_SOFT_EXCEPTION:
		case INTR_TYPE_SOFT_INTR:
		case INTR_TYPE_PRIV_SW_EXCEPTION:
			if (CC(vmcs12->vm_entry_instruction_len > 15) ||
			    CC(vmcs12->vm_entry_instruction_len == 0 &&
			    CC(!nested_cpu_has_zero_length_injection(vcpu))))
				return -EINVAL;
		}
	}

	if (nested_vmx_check_entry_msr_switch_controls(vcpu, vmcs12))
		return -EINVAL;

	return 0;
}