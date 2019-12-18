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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct x86_exception {int dummy; } ;
struct vmcs12 {unsigned long long vmcs_link_pointer; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gva_t ;
struct TYPE_3__ {unsigned long long current_vmptr; } ;
struct TYPE_4__ {TYPE_1__ nested; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_QUALIFICATION ; 
 int /*<<< orphan*/  VMXERR_UNSUPPORTED_VMCS_COMPONENT ; 
 int /*<<< orphan*/  VMX_INSTRUCTION_INFO ; 
 int /*<<< orphan*/  copy_vmcs02_to_vmcs12_rare (struct kvm_vcpu*,struct vmcs12*) ; 
 struct vmcs12* get_shadow_vmcs12 (struct kvm_vcpu*) ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 scalar_t__ get_vmx_mem_address (struct kvm_vcpu*,unsigned long,int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ is_64_bit_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ is_vmcs12_ext_field (unsigned long) ; 
 int /*<<< orphan*/  kvm_inject_page_fault (struct kvm_vcpu*,struct x86_exception*) ; 
 unsigned long kvm_register_readl (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_register_writel (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_write_guest_virt_system (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct x86_exception*) ; 
 int /*<<< orphan*/  nested_vmx_check_permission (struct kvm_vcpu*) ; 
 int nested_vmx_failInvalid (struct kvm_vcpu*) ; 
 int nested_vmx_failValid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int nested_vmx_succeed (struct kvm_vcpu*) ; 
 TYPE_2__* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs12_read_any (struct vmcs12*,unsigned long,short) ; 
 short vmcs_field_to_offset (unsigned long) ; 
 int vmcs_read32 (int /*<<< orphan*/ ) ; 
 unsigned long vmcs_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_vmread(struct kvm_vcpu *vcpu)
{
	unsigned long field;
	u64 field_value;
	unsigned long exit_qualification = vmcs_readl(EXIT_QUALIFICATION);
	u32 vmx_instruction_info = vmcs_read32(VMX_INSTRUCTION_INFO);
	int len;
	gva_t gva = 0;
	struct vmcs12 *vmcs12;
	struct x86_exception e;
	short offset;

	if (!nested_vmx_check_permission(vcpu))
		return 1;

	if (to_vmx(vcpu)->nested.current_vmptr == -1ull)
		return nested_vmx_failInvalid(vcpu);

	if (!is_guest_mode(vcpu))
		vmcs12 = get_vmcs12(vcpu);
	else {
		/*
		 * When vmcs->vmcs_link_pointer is -1ull, any VMREAD
		 * to shadowed-field sets the ALU flags for VMfailInvalid.
		 */
		if (get_vmcs12(vcpu)->vmcs_link_pointer == -1ull)
			return nested_vmx_failInvalid(vcpu);
		vmcs12 = get_shadow_vmcs12(vcpu);
	}

	/* Decode instruction info and find the field to read */
	field = kvm_register_readl(vcpu, (((vmx_instruction_info) >> 28) & 0xf));

	offset = vmcs_field_to_offset(field);
	if (offset < 0)
		return nested_vmx_failValid(vcpu,
			VMXERR_UNSUPPORTED_VMCS_COMPONENT);

	if (!is_guest_mode(vcpu) && is_vmcs12_ext_field(field))
		copy_vmcs02_to_vmcs12_rare(vcpu, vmcs12);

	/* Read the field, zero-extended to a u64 field_value */
	field_value = vmcs12_read_any(vmcs12, field, offset);

	/*
	 * Now copy part of this value to register or memory, as requested.
	 * Note that the number of bits actually copied is 32 or 64 depending
	 * on the guest's mode (32 or 64 bit), not on the given field's length.
	 */
	if (vmx_instruction_info & (1u << 10)) {
		kvm_register_writel(vcpu, (((vmx_instruction_info) >> 3) & 0xf),
			field_value);
	} else {
		len = is_64_bit_mode(vcpu) ? 8 : 4;
		if (get_vmx_mem_address(vcpu, exit_qualification,
				vmx_instruction_info, true, len, &gva))
			return 1;
		/* _system ok, nested_vmx_check_permission has verified cpl=0 */
		if (kvm_write_guest_virt_system(vcpu, gva, &field_value, len, &e))
			kvm_inject_page_fault(vcpu, &e);
	}

	return nested_vmx_succeed(vcpu);
}