#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  unsigned int u32 ;
struct x86_exception {int dummy; } ;
struct vmcs12 {unsigned long long vmcs_link_pointer; } ;
struct TYPE_6__ {unsigned long long current_vmptr; int dirty_vmcs12; } ;
struct TYPE_4__ {int /*<<< orphan*/  shadow_vmcs; } ;
struct vcpu_vmx {TYPE_3__ nested; TYPE_2__* loaded_vmcs; TYPE_1__ vmcs01; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gva_t ;
struct TYPE_5__ {int /*<<< orphan*/  vmcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_QUALIFICATION ; 
 unsigned long GUEST_ES_AR_BYTES ; 
 unsigned long GUEST_TR_AR_BYTES ; 
 int /*<<< orphan*/  VMXERR_UNSUPPORTED_VMCS_COMPONENT ; 
 int /*<<< orphan*/  VMXERR_VMWRITE_READ_ONLY_VMCS_COMPONENT ; 
 int /*<<< orphan*/  VMX_INSTRUCTION_INFO ; 
 int /*<<< orphan*/  __vmcs_writel (unsigned long,int) ; 
 int /*<<< orphan*/  copy_vmcs02_to_vmcs12_rare (struct kvm_vcpu*,struct vmcs12*) ; 
 scalar_t__ enable_shadow_vmcs ; 
 struct vmcs12* get_shadow_vmcs12 (struct kvm_vcpu*) ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 scalar_t__ get_vmx_mem_address (struct kvm_vcpu*,unsigned long,unsigned int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ is_64_bit_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ is_shadow_field_ro (unsigned long) ; 
 int /*<<< orphan*/  is_shadow_field_rw (unsigned long) ; 
 int /*<<< orphan*/  kvm_inject_page_fault (struct kvm_vcpu*,struct x86_exception*) ; 
 scalar_t__ kvm_read_guest_virt (struct kvm_vcpu*,int /*<<< orphan*/ ,int*,int,struct x86_exception*) ; 
 void* kvm_register_readl (struct kvm_vcpu*,unsigned int) ; 
 int /*<<< orphan*/  nested_cpu_has_vmwrite_any_field (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_vmx_check_permission (struct kvm_vcpu*) ; 
 int nested_vmx_failInvalid (struct kvm_vcpu*) ; 
 int nested_vmx_failValid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int nested_vmx_succeed (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs12_write_any (struct vmcs12*,unsigned long,short,int) ; 
 int /*<<< orphan*/  vmcs_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ vmcs_field_readonly (unsigned long) ; 
 short vmcs_field_to_offset (unsigned long) ; 
 int /*<<< orphan*/  vmcs_load (int /*<<< orphan*/ ) ; 
 unsigned int vmcs_read32 (int /*<<< orphan*/ ) ; 
 unsigned long vmcs_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_vmwrite(struct kvm_vcpu *vcpu)
{
	unsigned long field;
	int len;
	gva_t gva;
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	unsigned long exit_qualification = vmcs_readl(EXIT_QUALIFICATION);
	u32 vmx_instruction_info = vmcs_read32(VMX_INSTRUCTION_INFO);

	/* The value to write might be 32 or 64 bits, depending on L1's long
	 * mode, and eventually we need to write that into a field of several
	 * possible lengths. The code below first zero-extends the value to 64
	 * bit (field_value), and then copies only the appropriate number of
	 * bits into the vmcs12 field.
	 */
	u64 field_value = 0;
	struct x86_exception e;
	struct vmcs12 *vmcs12;
	short offset;

	if (!nested_vmx_check_permission(vcpu))
		return 1;

	if (vmx->nested.current_vmptr == -1ull)
		return nested_vmx_failInvalid(vcpu);

	if (vmx_instruction_info & (1u << 10))
		field_value = kvm_register_readl(vcpu,
			(((vmx_instruction_info) >> 3) & 0xf));
	else {
		len = is_64_bit_mode(vcpu) ? 8 : 4;
		if (get_vmx_mem_address(vcpu, exit_qualification,
				vmx_instruction_info, false, len, &gva))
			return 1;
		if (kvm_read_guest_virt(vcpu, gva, &field_value, len, &e)) {
			kvm_inject_page_fault(vcpu, &e);
			return 1;
		}
	}


	field = kvm_register_readl(vcpu, (((vmx_instruction_info) >> 28) & 0xf));
	/*
	 * If the vCPU supports "VMWRITE to any supported field in the
	 * VMCS," then the "read-only" fields are actually read/write.
	 */
	if (vmcs_field_readonly(field) &&
	    !nested_cpu_has_vmwrite_any_field(vcpu))
		return nested_vmx_failValid(vcpu,
			VMXERR_VMWRITE_READ_ONLY_VMCS_COMPONENT);

	if (!is_guest_mode(vcpu)) {
		vmcs12 = get_vmcs12(vcpu);

		/*
		 * Ensure vmcs12 is up-to-date before any VMWRITE that dirties
		 * vmcs12, else we may crush a field or consume a stale value.
		 */
		if (!is_shadow_field_rw(field))
			copy_vmcs02_to_vmcs12_rare(vcpu, vmcs12);
	} else {
		/*
		 * When vmcs->vmcs_link_pointer is -1ull, any VMWRITE
		 * to shadowed-field sets the ALU flags for VMfailInvalid.
		 */
		if (get_vmcs12(vcpu)->vmcs_link_pointer == -1ull)
			return nested_vmx_failInvalid(vcpu);
		vmcs12 = get_shadow_vmcs12(vcpu);
	}

	offset = vmcs_field_to_offset(field);
	if (offset < 0)
		return nested_vmx_failValid(vcpu,
			VMXERR_UNSUPPORTED_VMCS_COMPONENT);

	/*
	 * Some Intel CPUs intentionally drop the reserved bits of the AR byte
	 * fields on VMWRITE.  Emulate this behavior to ensure consistent KVM
	 * behavior regardless of the underlying hardware, e.g. if an AR_BYTE
	 * field is intercepted for VMWRITE but not VMREAD (in L1), then VMREAD
	 * from L1 will return a different value than VMREAD from L2 (L1 sees
	 * the stripped down value, L2 sees the full value as stored by KVM).
	 */
	if (field >= GUEST_ES_AR_BYTES && field <= GUEST_TR_AR_BYTES)
		field_value &= 0x1f0ff;

	vmcs12_write_any(vmcs12, field, offset, field_value);

	/*
	 * Do not track vmcs12 dirty-state if in guest-mode as we actually
	 * dirty shadow vmcs12 instead of vmcs12.  Fields that can be updated
	 * by L1 without a vmexit are always updated in the vmcs02, i.e. don't
	 * "dirty" vmcs12, all others go down the prepare_vmcs02() slow path.
	 */
	if (!is_guest_mode(vcpu) && !is_shadow_field_rw(field)) {
		/*
		 * L1 can read these fields without exiting, ensure the
		 * shadow VMCS is up-to-date.
		 */
		if (enable_shadow_vmcs && is_shadow_field_ro(field)) {
			preempt_disable();
			vmcs_load(vmx->vmcs01.shadow_vmcs);

			__vmcs_writel(field, field_value);

			vmcs_clear(vmx->vmcs01.shadow_vmcs);
			vmcs_load(vmx->loaded_vmcs->vmcs);
			preempt_enable();
		}
		vmx->nested.dirty_vmcs12 = true;
	}

	return nested_vmx_succeed(vcpu);
}