#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {scalar_t__ shadow_vmcs; } ;
struct vmcs12 {int launch_state; scalar_t__ guest_activity_state; int vm_entry_intr_info_field; int cpu_based_vm_exec_control; int guest_rflags; TYPE_1__ hdr; } ;
struct TYPE_8__ {unsigned long long current_vmptr; int nested_run_pending; scalar_t__ hv_evmcs; } ;
struct TYPE_6__ {int l1tf_flush_l1d; } ;
struct TYPE_7__ {TYPE_2__ arch; } ;
struct vcpu_vmx {TYPE_4__ nested; TYPE_3__ vcpu; } ;
struct kvm_vcpu {int dummy; } ;
typedef  enum nvmx_vmentry_status { ____Placeholder_nvmx_vmentry_status } nvmx_vmentry_status ;

/* Variables and functions */
 int CPU_BASED_VIRTUAL_INTR_PENDING ; 
 int CPU_BASED_VIRTUAL_NMI_PENDING ; 
 scalar_t__ GUEST_ACTIVITY_HLT ; 
 int INTR_INFO_VALID_MASK ; 
 int KVM_X86_SHADOW_INT_MOV_SS ; 
 int NVMX_VMENTRY_KVM_INTERNAL_ERROR ; 
 int NVMX_VMENTRY_SUCCESS ; 
 int NVMX_VMENTRY_VMEXIT ; 
 int NVMX_VMENTRY_VMFAIL ; 
 int /*<<< orphan*/  VMXERR_ENTRY_EVENTS_BLOCKED_BY_MOV_SS ; 
 int /*<<< orphan*/  VMXERR_ENTRY_INVALID_CONTROL_FIELD ; 
 int /*<<< orphan*/  VMXERR_ENTRY_INVALID_HOST_STATE_FIELD ; 
 int /*<<< orphan*/  VMXERR_VMLAUNCH_NONCLEAR_VMCS ; 
 int /*<<< orphan*/  VMXERR_VMRESUME_NONLAUNCHED_VMCS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int X86_EFLAGS_IF ; 
 int /*<<< orphan*/  copy_enlightened_to_vmcs12 (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  copy_shadow_to_vmcs12 (struct vcpu_vmx*) ; 
 scalar_t__ enable_shadow_vmcs ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 int kvm_vcpu_halt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_cache_shadow_vmcs12 (struct kvm_vcpu*,struct vmcs12*) ; 
 scalar_t__ nested_vmx_check_controls (struct kvm_vcpu*,struct vmcs12*) ; 
 scalar_t__ nested_vmx_check_host_state (struct kvm_vcpu*,struct vmcs12*) ; 
 int /*<<< orphan*/  nested_vmx_check_permission (struct kvm_vcpu*) ; 
 int nested_vmx_enter_non_root_mode (struct kvm_vcpu*,int) ; 
 int nested_vmx_failInvalid (struct kvm_vcpu*) ; 
 int nested_vmx_failValid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_vmx_handle_enlightened_vmptrld (struct kvm_vcpu*,int) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 
 int vmx_get_interrupt_shadow (struct kvm_vcpu*) ; 

__attribute__((used)) static int nested_vmx_run(struct kvm_vcpu *vcpu, bool launch)
{
	struct vmcs12 *vmcs12;
	enum nvmx_vmentry_status status;
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	u32 interrupt_shadow = vmx_get_interrupt_shadow(vcpu);

	if (!nested_vmx_check_permission(vcpu))
		return 1;

	if (!nested_vmx_handle_enlightened_vmptrld(vcpu, launch))
		return 1;

	if (!vmx->nested.hv_evmcs && vmx->nested.current_vmptr == -1ull)
		return nested_vmx_failInvalid(vcpu);

	vmcs12 = get_vmcs12(vcpu);

	/*
	 * Can't VMLAUNCH or VMRESUME a shadow VMCS. Despite the fact
	 * that there *is* a valid VMCS pointer, RFLAGS.CF is set
	 * rather than RFLAGS.ZF, and no error number is stored to the
	 * VM-instruction error field.
	 */
	if (vmcs12->hdr.shadow_vmcs)
		return nested_vmx_failInvalid(vcpu);

	if (vmx->nested.hv_evmcs) {
		copy_enlightened_to_vmcs12(vmx);
		/* Enlightened VMCS doesn't have launch state */
		vmcs12->launch_state = !launch;
	} else if (enable_shadow_vmcs) {
		copy_shadow_to_vmcs12(vmx);
	}

	/*
	 * The nested entry process starts with enforcing various prerequisites
	 * on vmcs12 as required by the Intel SDM, and act appropriately when
	 * they fail: As the SDM explains, some conditions should cause the
	 * instruction to fail, while others will cause the instruction to seem
	 * to succeed, but return an EXIT_REASON_INVALID_STATE.
	 * To speed up the normal (success) code path, we should avoid checking
	 * for misconfigurations which will anyway be caught by the processor
	 * when using the merged vmcs02.
	 */
	if (interrupt_shadow & KVM_X86_SHADOW_INT_MOV_SS)
		return nested_vmx_failValid(vcpu,
			VMXERR_ENTRY_EVENTS_BLOCKED_BY_MOV_SS);

	if (vmcs12->launch_state == launch)
		return nested_vmx_failValid(vcpu,
			launch ? VMXERR_VMLAUNCH_NONCLEAR_VMCS
			       : VMXERR_VMRESUME_NONLAUNCHED_VMCS);

	if (nested_vmx_check_controls(vcpu, vmcs12))
		return nested_vmx_failValid(vcpu, VMXERR_ENTRY_INVALID_CONTROL_FIELD);

	if (nested_vmx_check_host_state(vcpu, vmcs12))
		return nested_vmx_failValid(vcpu, VMXERR_ENTRY_INVALID_HOST_STATE_FIELD);

	/*
	 * We're finally done with prerequisite checking, and can start with
	 * the nested entry.
	 */
	vmx->nested.nested_run_pending = 1;
	status = nested_vmx_enter_non_root_mode(vcpu, true);
	if (unlikely(status != NVMX_VMENTRY_SUCCESS))
		goto vmentry_failed;

	/* Hide L1D cache contents from the nested guest.  */
	vmx->vcpu.arch.l1tf_flush_l1d = true;

	/*
	 * Must happen outside of nested_vmx_enter_non_root_mode() as it will
	 * also be used as part of restoring nVMX state for
	 * snapshot restore (migration).
	 *
	 * In this flow, it is assumed that vmcs12 cache was
	 * trasferred as part of captured nVMX state and should
	 * therefore not be read from guest memory (which may not
	 * exist on destination host yet).
	 */
	nested_cache_shadow_vmcs12(vcpu, vmcs12);

	/*
	 * If we're entering a halted L2 vcpu and the L2 vcpu won't be
	 * awakened by event injection or by an NMI-window VM-exit or
	 * by an interrupt-window VM-exit, halt the vcpu.
	 */
	if ((vmcs12->guest_activity_state == GUEST_ACTIVITY_HLT) &&
	    !(vmcs12->vm_entry_intr_info_field & INTR_INFO_VALID_MASK) &&
	    !(vmcs12->cpu_based_vm_exec_control & CPU_BASED_VIRTUAL_NMI_PENDING) &&
	    !((vmcs12->cpu_based_vm_exec_control & CPU_BASED_VIRTUAL_INTR_PENDING) &&
	      (vmcs12->guest_rflags & X86_EFLAGS_IF))) {
		vmx->nested.nested_run_pending = 0;
		return kvm_vcpu_halt(vcpu);
	}
	return 1;

vmentry_failed:
	vmx->nested.nested_run_pending = 0;
	if (status == NVMX_VMENTRY_KVM_INTERNAL_ERROR)
		return 0;
	if (status == NVMX_VMENTRY_VMEXIT)
		return 1;
	WARN_ON_ONCE(status != NVMX_VMENTRY_VMFAIL);
	return nested_vmx_failValid(vcpu, VMXERR_ENTRY_INVALID_CONTROL_FIELD);
}