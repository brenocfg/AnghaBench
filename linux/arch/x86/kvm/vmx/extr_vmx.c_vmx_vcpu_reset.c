#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_9__ {int cr0; int /*<<< orphan*/ * regs; } ;
struct TYPE_10__ {TYPE_4__ arch; } ;
struct TYPE_6__ {scalar_t__ vm86_active; } ;
struct vcpu_vmx {int hv_deadline_tsc; int vpid; TYPE_5__ vcpu; scalar_t__ msr_ia32_umwait_control; scalar_t__ spec_ctrl; TYPE_1__ rmode; } ;
struct msr_data {int data; int host_initiated; } ;
struct TYPE_8__ {int microcode_version; TYPE_2__* apic; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_7__ {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int APIC_DEFAULT_PHYS_BASE ; 
 int GUEST_ACTIVITY_ACTIVE ; 
 int /*<<< orphan*/  GUEST_ACTIVITY_STATE ; 
 int /*<<< orphan*/  GUEST_BNDCFGS ; 
 int /*<<< orphan*/  GUEST_CS_BASE ; 
 int /*<<< orphan*/  GUEST_CS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_GDTR_BASE ; 
 int /*<<< orphan*/  GUEST_GDTR_LIMIT ; 
 int /*<<< orphan*/  GUEST_IA32_DEBUGCTL ; 
 int /*<<< orphan*/  GUEST_IDTR_BASE ; 
 int /*<<< orphan*/  GUEST_IDTR_LIMIT ; 
 int /*<<< orphan*/  GUEST_INTERRUPTIBILITY_INFO ; 
 int /*<<< orphan*/  GUEST_LDTR_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_LDTR_BASE ; 
 int /*<<< orphan*/  GUEST_LDTR_LIMIT ; 
 int /*<<< orphan*/  GUEST_LDTR_SELECTOR ; 
 int /*<<< orphan*/  GUEST_PENDING_DBG_EXCEPTIONS ; 
 int /*<<< orphan*/  GUEST_SYSENTER_CS ; 
 int /*<<< orphan*/  GUEST_SYSENTER_EIP ; 
 int /*<<< orphan*/  GUEST_SYSENTER_ESP ; 
 int /*<<< orphan*/  GUEST_TR_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_TR_BASE ; 
 int /*<<< orphan*/  GUEST_TR_LIMIT ; 
 int /*<<< orphan*/  GUEST_TR_SELECTOR ; 
 int /*<<< orphan*/  KVM_REQ_APIC_PAGE_RELOAD ; 
 int MSR_IA32_APICBASE_BSP ; 
 int MSR_IA32_APICBASE_ENABLE ; 
 int /*<<< orphan*/  TPR_THRESHOLD ; 
 size_t VCPU_REGS_RDX ; 
 int /*<<< orphan*/  VCPU_SREG_CS ; 
 int /*<<< orphan*/  VCPU_SREG_DS ; 
 int /*<<< orphan*/  VCPU_SREG_ES ; 
 int /*<<< orphan*/  VCPU_SREG_FS ; 
 int /*<<< orphan*/  VCPU_SREG_GS ; 
 int /*<<< orphan*/  VCPU_SREG_SS ; 
 int /*<<< orphan*/  VIRTUAL_APIC_PAGE_ADDR ; 
 int /*<<< orphan*/  VIRTUAL_PROCESSOR_ID ; 
 int /*<<< orphan*/  VM_ENTRY_INTR_INFO_FIELD ; 
 int X86_CR0_CD ; 
 int X86_CR0_ET ; 
 int X86_CR0_NW ; 
 int /*<<< orphan*/  X86_EFLAGS_FIXED ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has_vmx_tpr_shadow () ; 
 scalar_t__ cpu_need_tpr_shadow (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  get_rdx_init_val () ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 scalar_t__ kvm_mpx_supported () ; 
 int /*<<< orphan*/  kvm_rip_write (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_set_apic_base (struct kvm_vcpu*,struct msr_data*) ; 
 int /*<<< orphan*/  kvm_set_cr8 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_rflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_vcpu_is_reset_bsp (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  seg_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_msrs (struct vcpu_vmx*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  update_exception_bitmap (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_write16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmx_clear_hlt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_segment_cache_clear (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmx_set_cr0 (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  vmx_set_cr4 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_set_efer (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpid_sync_context (int) ; 

__attribute__((used)) static void vmx_vcpu_reset(struct kvm_vcpu *vcpu, bool init_event)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct msr_data apic_base_msr;
	u64 cr0;

	vmx->rmode.vm86_active = 0;
	vmx->spec_ctrl = 0;

	vmx->msr_ia32_umwait_control = 0;

	vcpu->arch.microcode_version = 0x100000000ULL;
	vmx->vcpu.arch.regs[VCPU_REGS_RDX] = get_rdx_init_val();
	vmx->hv_deadline_tsc = -1;
	kvm_set_cr8(vcpu, 0);

	if (!init_event) {
		apic_base_msr.data = APIC_DEFAULT_PHYS_BASE |
				     MSR_IA32_APICBASE_ENABLE;
		if (kvm_vcpu_is_reset_bsp(vcpu))
			apic_base_msr.data |= MSR_IA32_APICBASE_BSP;
		apic_base_msr.host_initiated = true;
		kvm_set_apic_base(vcpu, &apic_base_msr);
	}

	vmx_segment_cache_clear(vmx);

	seg_setup(VCPU_SREG_CS);
	vmcs_write16(GUEST_CS_SELECTOR, 0xf000);
	vmcs_writel(GUEST_CS_BASE, 0xffff0000ul);

	seg_setup(VCPU_SREG_DS);
	seg_setup(VCPU_SREG_ES);
	seg_setup(VCPU_SREG_FS);
	seg_setup(VCPU_SREG_GS);
	seg_setup(VCPU_SREG_SS);

	vmcs_write16(GUEST_TR_SELECTOR, 0);
	vmcs_writel(GUEST_TR_BASE, 0);
	vmcs_write32(GUEST_TR_LIMIT, 0xffff);
	vmcs_write32(GUEST_TR_AR_BYTES, 0x008b);

	vmcs_write16(GUEST_LDTR_SELECTOR, 0);
	vmcs_writel(GUEST_LDTR_BASE, 0);
	vmcs_write32(GUEST_LDTR_LIMIT, 0xffff);
	vmcs_write32(GUEST_LDTR_AR_BYTES, 0x00082);

	if (!init_event) {
		vmcs_write32(GUEST_SYSENTER_CS, 0);
		vmcs_writel(GUEST_SYSENTER_ESP, 0);
		vmcs_writel(GUEST_SYSENTER_EIP, 0);
		vmcs_write64(GUEST_IA32_DEBUGCTL, 0);
	}

	kvm_set_rflags(vcpu, X86_EFLAGS_FIXED);
	kvm_rip_write(vcpu, 0xfff0);

	vmcs_writel(GUEST_GDTR_BASE, 0);
	vmcs_write32(GUEST_GDTR_LIMIT, 0xffff);

	vmcs_writel(GUEST_IDTR_BASE, 0);
	vmcs_write32(GUEST_IDTR_LIMIT, 0xffff);

	vmcs_write32(GUEST_ACTIVITY_STATE, GUEST_ACTIVITY_ACTIVE);
	vmcs_write32(GUEST_INTERRUPTIBILITY_INFO, 0);
	vmcs_writel(GUEST_PENDING_DBG_EXCEPTIONS, 0);
	if (kvm_mpx_supported())
		vmcs_write64(GUEST_BNDCFGS, 0);

	setup_msrs(vmx);

	vmcs_write32(VM_ENTRY_INTR_INFO_FIELD, 0);  /* 22.2.1 */

	if (cpu_has_vmx_tpr_shadow() && !init_event) {
		vmcs_write64(VIRTUAL_APIC_PAGE_ADDR, 0);
		if (cpu_need_tpr_shadow(vcpu))
			vmcs_write64(VIRTUAL_APIC_PAGE_ADDR,
				     __pa(vcpu->arch.apic->regs));
		vmcs_write32(TPR_THRESHOLD, 0);
	}

	kvm_make_request(KVM_REQ_APIC_PAGE_RELOAD, vcpu);

	if (vmx->vpid != 0)
		vmcs_write16(VIRTUAL_PROCESSOR_ID, vmx->vpid);

	cr0 = X86_CR0_NW | X86_CR0_CD | X86_CR0_ET;
	vmx->vcpu.arch.cr0 = cr0;
	vmx_set_cr0(vcpu, cr0); /* enter rmode */
	vmx_set_cr4(vcpu, 0);
	vmx_set_efer(vcpu, 0);

	update_exception_bitmap(vcpu);

	vpid_sync_context(vmx->vpid);
	if (init_event)
		vmx_clear_hlt(vcpu);
}