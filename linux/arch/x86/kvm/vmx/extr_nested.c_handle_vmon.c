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
typedef  scalar_t__ uint32_t ;
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  vmxon_ptr; scalar_t__ vmxon; } ;
struct vcpu_vmx {int const msr_ia32_feature_control; TYPE_1__ nested; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
typedef  int /*<<< orphan*/  revision ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int FEATURE_CONTROL_LOCKED ; 
 int FEATURE_CONTROL_VMXON_ENABLED_OUTSIDE_SMX ; 
 int /*<<< orphan*/  UD_VECTOR ; 
 scalar_t__ VMCS12_REVISION ; 
 int /*<<< orphan*/  VMXERR_VMXON_IN_VMX_ROOT_OPERATION ; 
 int /*<<< orphan*/  X86_CR4_VMXE ; 
 int enter_vmx_operation (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_inject_gp (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_queue_exception (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_read_cr4_bits (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_read_guest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int nested_vmx_failInvalid (struct kvm_vcpu*) ; 
 int nested_vmx_failValid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ nested_vmx_get_vmptr (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int nested_vmx_succeed (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  page_address_valid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 scalar_t__ vmx_get_cpl (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_vmon(struct kvm_vcpu *vcpu)
{
	int ret;
	gpa_t vmptr;
	uint32_t revision;
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	const u64 VMXON_NEEDED_FEATURES = FEATURE_CONTROL_LOCKED
		| FEATURE_CONTROL_VMXON_ENABLED_OUTSIDE_SMX;

	/*
	 * The Intel VMX Instruction Reference lists a bunch of bits that are
	 * prerequisite to running VMXON, most notably cr4.VMXE must be set to
	 * 1 (see vmx_set_cr4() for when we allow the guest to set this).
	 * Otherwise, we should fail with #UD.  But most faulting conditions
	 * have already been checked by hardware, prior to the VM-exit for
	 * VMXON.  We do test guest cr4.VMXE because processor CR4 always has
	 * that bit set to 1 in non-root mode.
	 */
	if (!kvm_read_cr4_bits(vcpu, X86_CR4_VMXE)) {
		kvm_queue_exception(vcpu, UD_VECTOR);
		return 1;
	}

	/* CPL=0 must be checked manually. */
	if (vmx_get_cpl(vcpu)) {
		kvm_inject_gp(vcpu, 0);
		return 1;
	}

	if (vmx->nested.vmxon)
		return nested_vmx_failValid(vcpu,
			VMXERR_VMXON_IN_VMX_ROOT_OPERATION);

	if ((vmx->msr_ia32_feature_control & VMXON_NEEDED_FEATURES)
			!= VMXON_NEEDED_FEATURES) {
		kvm_inject_gp(vcpu, 0);
		return 1;
	}

	if (nested_vmx_get_vmptr(vcpu, &vmptr))
		return 1;

	/*
	 * SDM 3: 24.11.5
	 * The first 4 bytes of VMXON region contain the supported
	 * VMCS revision identifier
	 *
	 * Note - IA32_VMX_BASIC[48] will never be 1 for the nested case;
	 * which replaces physical address width with 32
	 */
	if (!page_address_valid(vcpu, vmptr))
		return nested_vmx_failInvalid(vcpu);

	if (kvm_read_guest(vcpu->kvm, vmptr, &revision, sizeof(revision)) ||
	    revision != VMCS12_REVISION)
		return nested_vmx_failInvalid(vcpu);

	vmx->nested.vmxon_ptr = vmptr;
	ret = enter_vmx_operation(vcpu);
	if (ret)
		return ret;

	return nested_vmx_succeed(vcpu);
}