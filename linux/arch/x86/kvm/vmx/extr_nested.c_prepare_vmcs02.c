#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vmcs12 {int vm_entry_controls; scalar_t__ virtual_processor_id; int /*<<< orphan*/  guest_rip; int /*<<< orphan*/  guest_rsp; int /*<<< orphan*/  guest_pdptr3; int /*<<< orphan*/  guest_pdptr2; int /*<<< orphan*/  guest_pdptr1; int /*<<< orphan*/  guest_pdptr0; int /*<<< orphan*/  guest_cr3; int /*<<< orphan*/  guest_cr4; int /*<<< orphan*/  guest_cr0; int /*<<< orphan*/  guest_ia32_pat; int /*<<< orphan*/  cr0_guest_host_mask; int /*<<< orphan*/  guest_rflags; int /*<<< orphan*/  guest_ia32_debugctl; int /*<<< orphan*/  guest_dr7; } ;
struct TYPE_9__ {int dirty_vmcs12; scalar_t__ last_vpid; scalar_t__ nested_run_pending; int /*<<< orphan*/  vmcs01_guest_bndcfgs; int /*<<< orphan*/  vmcs01_debugctl; struct hv_enlightened_vmcs* hv_evmcs; } ;
struct TYPE_7__ {int /*<<< orphan*/  pat; } ;
struct TYPE_8__ {TYPE_1__ arch; } ;
struct vcpu_vmx {scalar_t__ emulation_required; TYPE_3__ nested; TYPE_2__ vcpu; } ;
struct TYPE_11__ {TYPE_4__* walk_mmu; int /*<<< orphan*/  efer; int /*<<< orphan*/  tsc_offset; int /*<<< orphan*/  pat; int /*<<< orphan*/  cr0_guest_owned_bits; int /*<<< orphan*/  dr7; } ;
struct kvm_vcpu {TYPE_5__ arch; } ;
struct hv_enlightened_vmcs {int hv_clean_fields; } ;
struct TYPE_12__ {int vmentry_ctrl; } ;
struct TYPE_10__ {int /*<<< orphan*/  inject_page_fault; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR0_GUEST_HOST_MASK ; 
 int /*<<< orphan*/  CR0_READ_SHADOW ; 
 int /*<<< orphan*/  CR4_READ_SHADOW ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENTRY_FAIL_DEFAULT ; 
 int /*<<< orphan*/  GUEST_BNDCFGS ; 
 int /*<<< orphan*/  GUEST_IA32_DEBUGCTL ; 
 int /*<<< orphan*/  GUEST_IA32_PAT ; 
 int /*<<< orphan*/  GUEST_PDPTR0 ; 
 int /*<<< orphan*/  GUEST_PDPTR1 ; 
 int /*<<< orphan*/  GUEST_PDPTR2 ; 
 int /*<<< orphan*/  GUEST_PDPTR3 ; 
 int HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP1 ; 
 int /*<<< orphan*/  KVM_REQ_TLB_FLUSH ; 
 int /*<<< orphan*/  SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES ; 
 int /*<<< orphan*/  TSC_OFFSET ; 
 int VM_ENTRY_LOAD_BNDCFGS ; 
 int VM_ENTRY_LOAD_DEBUG_CONTROLS ; 
 int VM_ENTRY_LOAD_IA32_PAT ; 
 int /*<<< orphan*/  __vmx_flush_tlb (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  decache_tsc_multiplier (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  enable_ept ; 
 scalar_t__ enable_vpid ; 
 scalar_t__ is_pae_paging (struct kvm_vcpu*) ; 
 scalar_t__ kvm_has_tsc_control ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 scalar_t__ kvm_mpx_supported () ; 
 int /*<<< orphan*/  kvm_rip_write (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_rsp_write (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_dr (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nested_cpu_has2 (struct vmcs12*,int /*<<< orphan*/ ) ; 
 scalar_t__ nested_cpu_has_ept (struct vmcs12*) ; 
 scalar_t__ nested_cpu_has_vpid (struct vmcs12*) ; 
 int /*<<< orphan*/  nested_ept_init_mmu_context (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_get_vpid02 (struct kvm_vcpu*) ; 
 scalar_t__ nested_has_guest_tlb_tag (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_read_cr0 (struct vmcs12*) ; 
 int /*<<< orphan*/  nested_read_cr4 (struct vmcs12*) ; 
 int /*<<< orphan*/  nested_vmx_calc_efer (struct vcpu_vmx*,struct vmcs12*) ; 
 scalar_t__ nested_vmx_load_cr3 (struct kvm_vcpu*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_vmcs02_rare (struct vcpu_vmx*,struct vmcs12*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  update_exception_bitmap (struct kvm_vcpu*) ; 
 TYPE_6__ vmcs_config ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_flush_tlb (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  vmx_inject_page_fault_nested ; 
 int /*<<< orphan*/  vmx_set_cr0 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_set_cr4 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_set_efer (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_set_rflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prepare_vmcs02(struct kvm_vcpu *vcpu, struct vmcs12 *vmcs12,
			  u32 *entry_failure_code)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct hv_enlightened_vmcs *hv_evmcs = vmx->nested.hv_evmcs;
	bool load_guest_pdptrs_vmcs12 = false;

	if (vmx->nested.dirty_vmcs12 || hv_evmcs) {
		prepare_vmcs02_rare(vmx, vmcs12);
		vmx->nested.dirty_vmcs12 = false;

		load_guest_pdptrs_vmcs12 = !hv_evmcs ||
			!(hv_evmcs->hv_clean_fields &
			  HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP1);
	}

	if (vmx->nested.nested_run_pending &&
	    (vmcs12->vm_entry_controls & VM_ENTRY_LOAD_DEBUG_CONTROLS)) {
		kvm_set_dr(vcpu, 7, vmcs12->guest_dr7);
		vmcs_write64(GUEST_IA32_DEBUGCTL, vmcs12->guest_ia32_debugctl);
	} else {
		kvm_set_dr(vcpu, 7, vcpu->arch.dr7);
		vmcs_write64(GUEST_IA32_DEBUGCTL, vmx->nested.vmcs01_debugctl);
	}
	if (kvm_mpx_supported() && (!vmx->nested.nested_run_pending ||
	    !(vmcs12->vm_entry_controls & VM_ENTRY_LOAD_BNDCFGS)))
		vmcs_write64(GUEST_BNDCFGS, vmx->nested.vmcs01_guest_bndcfgs);
	vmx_set_rflags(vcpu, vmcs12->guest_rflags);

	/* EXCEPTION_BITMAP and CR0_GUEST_HOST_MASK should basically be the
	 * bitwise-or of what L1 wants to trap for L2, and what we want to
	 * trap. Note that CR0.TS also needs updating - we do this later.
	 */
	update_exception_bitmap(vcpu);
	vcpu->arch.cr0_guest_owned_bits &= ~vmcs12->cr0_guest_host_mask;
	vmcs_writel(CR0_GUEST_HOST_MASK, ~vcpu->arch.cr0_guest_owned_bits);

	if (vmx->nested.nested_run_pending &&
	    (vmcs12->vm_entry_controls & VM_ENTRY_LOAD_IA32_PAT)) {
		vmcs_write64(GUEST_IA32_PAT, vmcs12->guest_ia32_pat);
		vcpu->arch.pat = vmcs12->guest_ia32_pat;
	} else if (vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_IA32_PAT) {
		vmcs_write64(GUEST_IA32_PAT, vmx->vcpu.arch.pat);
	}

	vmcs_write64(TSC_OFFSET, vcpu->arch.tsc_offset);

	if (kvm_has_tsc_control)
		decache_tsc_multiplier(vmx);

	if (enable_vpid) {
		/*
		 * There is no direct mapping between vpid02 and vpid12, the
		 * vpid02 is per-vCPU for L0 and reused while the value of
		 * vpid12 is changed w/ one invvpid during nested vmentry.
		 * The vpid12 is allocated by L1 for L2, so it will not
		 * influence global bitmap(for vpid01 and vpid02 allocation)
		 * even if spawn a lot of nested vCPUs.
		 */
		if (nested_cpu_has_vpid(vmcs12) && nested_has_guest_tlb_tag(vcpu)) {
			if (vmcs12->virtual_processor_id != vmx->nested.last_vpid) {
				vmx->nested.last_vpid = vmcs12->virtual_processor_id;
				__vmx_flush_tlb(vcpu, nested_get_vpid02(vcpu), false);
			}
		} else {
			/*
			 * If L1 use EPT, then L0 needs to execute INVEPT on
			 * EPTP02 instead of EPTP01. Therefore, delay TLB
			 * flush until vmcs02->eptp is fully updated by
			 * KVM_REQ_LOAD_CR3. Note that this assumes
			 * KVM_REQ_TLB_FLUSH is evaluated after
			 * KVM_REQ_LOAD_CR3 in vcpu_enter_guest().
			 */
			kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
		}
	}

	if (nested_cpu_has_ept(vmcs12))
		nested_ept_init_mmu_context(vcpu);
	else if (nested_cpu_has2(vmcs12,
				 SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES))
		vmx_flush_tlb(vcpu, true);

	/*
	 * This sets GUEST_CR0 to vmcs12->guest_cr0, possibly modifying those
	 * bits which we consider mandatory enabled.
	 * The CR0_READ_SHADOW is what L2 should have expected to read given
	 * the specifications by L1; It's not enough to take
	 * vmcs12->cr0_read_shadow because on our cr0_guest_host_mask we we
	 * have more bits than L1 expected.
	 */
	vmx_set_cr0(vcpu, vmcs12->guest_cr0);
	vmcs_writel(CR0_READ_SHADOW, nested_read_cr0(vmcs12));

	vmx_set_cr4(vcpu, vmcs12->guest_cr4);
	vmcs_writel(CR4_READ_SHADOW, nested_read_cr4(vmcs12));

	vcpu->arch.efer = nested_vmx_calc_efer(vmx, vmcs12);
	/* Note: may modify VM_ENTRY/EXIT_CONTROLS and GUEST/HOST_IA32_EFER */
	vmx_set_efer(vcpu, vcpu->arch.efer);

	/*
	 * Guest state is invalid and unrestricted guest is disabled,
	 * which means L1 attempted VMEntry to L2 with invalid state.
	 * Fail the VMEntry.
	 */
	if (vmx->emulation_required) {
		*entry_failure_code = ENTRY_FAIL_DEFAULT;
		return -EINVAL;
	}

	/* Shadow page tables on either EPT or shadow page tables. */
	if (nested_vmx_load_cr3(vcpu, vmcs12->guest_cr3, nested_cpu_has_ept(vmcs12),
				entry_failure_code))
		return -EINVAL;

	/* Late preparation of GUEST_PDPTRs now that EFER and CRs are set. */
	if (load_guest_pdptrs_vmcs12 && nested_cpu_has_ept(vmcs12) &&
	    is_pae_paging(vcpu)) {
		vmcs_write64(GUEST_PDPTR0, vmcs12->guest_pdptr0);
		vmcs_write64(GUEST_PDPTR1, vmcs12->guest_pdptr1);
		vmcs_write64(GUEST_PDPTR2, vmcs12->guest_pdptr2);
		vmcs_write64(GUEST_PDPTR3, vmcs12->guest_pdptr3);
	}

	if (!enable_ept)
		vcpu->arch.walk_mmu->inject_page_fault = vmx_inject_page_fault_nested;

	kvm_rsp_write(vcpu, vmcs12->guest_rsp);
	kvm_rip_write(vcpu, vmcs12->guest_rip);
	return 0;
}