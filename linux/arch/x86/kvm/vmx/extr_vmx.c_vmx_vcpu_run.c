#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_14__ {scalar_t__ nested_run_pending; scalar_t__ need_vmcs12_to_shadow_sync; } ;
struct vcpu_vmx {int ple_window_dirty; scalar_t__ host_pkru; int idt_vectoring_info; int exit_reason; TYPE_7__* loaded_vmcs; scalar_t__ fail; TYPE_6__ nested; scalar_t__ host_debugctlmsr; int /*<<< orphan*/  spec_ctrl; int /*<<< orphan*/  ple_window; scalar_t__ emulation_required; } ;
struct TYPE_12__ {int /*<<< orphan*/  vp_index; } ;
struct TYPE_13__ {unsigned long* regs; scalar_t__ pkru; scalar_t__ cr2; int regs_avail; scalar_t__ regs_dirty; TYPE_4__ hyperv; TYPE_3__* apic; } ;
struct kvm_vcpu {int guest_debug; TYPE_5__ arch; } ;
struct TYPE_16__ {int /*<<< orphan*/  hv_vp_id; int /*<<< orphan*/  hv_clean_fields; } ;
struct TYPE_9__ {unsigned long cr3; unsigned long cr4; } ;
struct TYPE_15__ {int launched; TYPE_1__ host_state; int /*<<< orphan*/  entry_time; scalar_t__ soft_vnmi_blocked; } ;
struct TYPE_10__ {scalar_t__ timer_advance_ns; } ;
struct TYPE_11__ {TYPE_2__ lapic_timer; } ;

/* Variables and functions */
 scalar_t__ EXIT_REASON_MCE_DURING_VMENTRY ; 
 int /*<<< orphan*/  GUEST_RIP ; 
 int /*<<< orphan*/  GUEST_RSP ; 
 int /*<<< orphan*/  HOST_CR3 ; 
 int /*<<< orphan*/  HOST_CR4 ; 
 int /*<<< orphan*/  HV_VMX_ENLIGHTENED_CLEAN_FIELD_ALL ; 
 int /*<<< orphan*/  IDT_VECTORING_INFO_FIELD ; 
 int KVM_GUESTDBG_SINGLESTEP ; 
 int /*<<< orphan*/  MSR_IA32_SPEC_CTRL ; 
 int /*<<< orphan*/  PLE_WINDOW ; 
 int VCPU_EXREG_CR3 ; 
 int VCPU_EXREG_PDPTR ; 
 int VCPU_EXREG_RFLAGS ; 
 int VCPU_EXREG_SEGMENTS ; 
 size_t VCPU_REGS_RIP ; 
 size_t VCPU_REGS_RSP ; 
 int VMX_EXIT_REASONS_FAILED_VMENTRY ; 
 int /*<<< orphan*/  VM_EXIT_REASON ; 
 int /*<<< orphan*/  X86_CR4_PKE ; 
 int /*<<< orphan*/  X86_FEATURE_PKU ; 
 int /*<<< orphan*/  __USER_DS ; 
 unsigned long __get_current_cr3_fast () ; 
 scalar_t__ __vmx_vcpu_run (struct vcpu_vmx*,unsigned long*,int) ; 
 int /*<<< orphan*/  __write_pkru (scalar_t__) ; 
 int /*<<< orphan*/  atomic_switch_perf_msrs (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  atomic_switch_umwait_control_msr (struct vcpu_vmx*) ; 
 unsigned long cr4_read_shadow () ; 
 TYPE_8__* current_evmcs ; 
 int /*<<< orphan*/  ds ; 
 int /*<<< orphan*/  enable_evmcs ; 
 scalar_t__ enable_preemption_timer ; 
 int /*<<< orphan*/  enable_vnmi ; 
 int /*<<< orphan*/  es ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  kvm_load_guest_xcr0 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_machine_check () ; 
 int /*<<< orphan*/  kvm_put_guest_xcr0 (struct kvm_vcpu*) ; 
 scalar_t__ kvm_read_cr4_bits (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_wait_lapic_expire (struct kvm_vcpu*) ; 
 scalar_t__ lapic_in_kernel (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  loadsegment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mds_clear_cpu_buffers () ; 
 int /*<<< orphan*/  mds_user_clear ; 
 int /*<<< orphan*/  msr_write_intercepted (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  native_read_msr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nested_sync_vmcs12_to_shadow (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pt_guest_enter (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  pt_guest_exit (struct vcpu_vmx*) ; 
 scalar_t__ rdpkru () ; 
 scalar_t__ read_cr2 () ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 
 scalar_t__ static_cpu_has (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (size_t,unsigned long*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_debugctlmsr (scalar_t__) ; 
 int vmcs_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vmx_complete_interrupts (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmx_l1d_flush (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_l1d_should_flush ; 
 int /*<<< orphan*/  vmx_recover_nmi_blocking (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmx_set_interrupt_shadow (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_update_hv_timer (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  write_cr2 (scalar_t__) ; 
 int /*<<< orphan*/  x86_spec_ctrl_restore_host (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86_spec_ctrl_set_guest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmx_vcpu_run(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	unsigned long cr3, cr4;

	/* Record the guest's net vcpu time for enforced NMI injections. */
	if (unlikely(!enable_vnmi &&
		     vmx->loaded_vmcs->soft_vnmi_blocked))
		vmx->loaded_vmcs->entry_time = ktime_get();

	/* Don't enter VMX if guest state is invalid, let the exit handler
	   start emulation until we arrive back to a valid state */
	if (vmx->emulation_required)
		return;

	if (vmx->ple_window_dirty) {
		vmx->ple_window_dirty = false;
		vmcs_write32(PLE_WINDOW, vmx->ple_window);
	}

	if (vmx->nested.need_vmcs12_to_shadow_sync)
		nested_sync_vmcs12_to_shadow(vcpu);

	if (test_bit(VCPU_REGS_RSP, (unsigned long *)&vcpu->arch.regs_dirty))
		vmcs_writel(GUEST_RSP, vcpu->arch.regs[VCPU_REGS_RSP]);
	if (test_bit(VCPU_REGS_RIP, (unsigned long *)&vcpu->arch.regs_dirty))
		vmcs_writel(GUEST_RIP, vcpu->arch.regs[VCPU_REGS_RIP]);

	cr3 = __get_current_cr3_fast();
	if (unlikely(cr3 != vmx->loaded_vmcs->host_state.cr3)) {
		vmcs_writel(HOST_CR3, cr3);
		vmx->loaded_vmcs->host_state.cr3 = cr3;
	}

	cr4 = cr4_read_shadow();
	if (unlikely(cr4 != vmx->loaded_vmcs->host_state.cr4)) {
		vmcs_writel(HOST_CR4, cr4);
		vmx->loaded_vmcs->host_state.cr4 = cr4;
	}

	/* When single-stepping over STI and MOV SS, we must clear the
	 * corresponding interruptibility bits in the guest state. Otherwise
	 * vmentry fails as it then expects bit 14 (BS) in pending debug
	 * exceptions being set, but that's not correct for the guest debugging
	 * case. */
	if (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP)
		vmx_set_interrupt_shadow(vcpu, 0);

	kvm_load_guest_xcr0(vcpu);

	if (static_cpu_has(X86_FEATURE_PKU) &&
	    kvm_read_cr4_bits(vcpu, X86_CR4_PKE) &&
	    vcpu->arch.pkru != vmx->host_pkru)
		__write_pkru(vcpu->arch.pkru);

	pt_guest_enter(vmx);

	atomic_switch_perf_msrs(vmx);
	atomic_switch_umwait_control_msr(vmx);

	if (enable_preemption_timer)
		vmx_update_hv_timer(vcpu);

	if (lapic_in_kernel(vcpu) &&
		vcpu->arch.apic->lapic_timer.timer_advance_ns)
		kvm_wait_lapic_expire(vcpu);

	/*
	 * If this vCPU has touched SPEC_CTRL, restore the guest's value if
	 * it's non-zero. Since vmentry is serialising on affected CPUs, there
	 * is no need to worry about the conditional branch over the wrmsr
	 * being speculatively taken.
	 */
	x86_spec_ctrl_set_guest(vmx->spec_ctrl, 0);

	/* L1D Flush includes CPU buffer clear to mitigate MDS */
	if (static_branch_unlikely(&vmx_l1d_should_flush))
		vmx_l1d_flush(vcpu);
	else if (static_branch_unlikely(&mds_user_clear))
		mds_clear_cpu_buffers();

	if (vcpu->arch.cr2 != read_cr2())
		write_cr2(vcpu->arch.cr2);

	vmx->fail = __vmx_vcpu_run(vmx, (unsigned long *)&vcpu->arch.regs,
				   vmx->loaded_vmcs->launched);

	vcpu->arch.cr2 = read_cr2();

	/*
	 * We do not use IBRS in the kernel. If this vCPU has used the
	 * SPEC_CTRL MSR it may have left it on; save the value and
	 * turn it off. This is much more efficient than blindly adding
	 * it to the atomic save/restore list. Especially as the former
	 * (Saving guest MSRs on vmexit) doesn't even exist in KVM.
	 *
	 * For non-nested case:
	 * If the L01 MSR bitmap does not intercept the MSR, then we need to
	 * save it.
	 *
	 * For nested case:
	 * If the L02 MSR bitmap does not intercept the MSR, then we need to
	 * save it.
	 */
	if (unlikely(!msr_write_intercepted(vcpu, MSR_IA32_SPEC_CTRL)))
		vmx->spec_ctrl = native_read_msr(MSR_IA32_SPEC_CTRL);

	x86_spec_ctrl_restore_host(vmx->spec_ctrl, 0);

	/* All fields are clean at this point */
	if (static_branch_unlikely(&enable_evmcs))
		current_evmcs->hv_clean_fields |=
			HV_VMX_ENLIGHTENED_CLEAN_FIELD_ALL;

	if (static_branch_unlikely(&enable_evmcs))
		current_evmcs->hv_vp_id = vcpu->arch.hyperv.vp_index;

	/* MSR_IA32_DEBUGCTLMSR is zeroed on vmexit. Restore it if needed */
	if (vmx->host_debugctlmsr)
		update_debugctlmsr(vmx->host_debugctlmsr);

#ifndef CONFIG_X86_64
	/*
	 * The sysexit path does not restore ds/es, so we must set them to
	 * a reasonable value ourselves.
	 *
	 * We can't defer this to vmx_prepare_switch_to_host() since that
	 * function may be executed in interrupt context, which saves and
	 * restore segments around it, nullifying its effect.
	 */
	loadsegment(ds, __USER_DS);
	loadsegment(es, __USER_DS);
#endif

	vcpu->arch.regs_avail = ~((1 << VCPU_REGS_RIP) | (1 << VCPU_REGS_RSP)
				  | (1 << VCPU_EXREG_RFLAGS)
				  | (1 << VCPU_EXREG_PDPTR)
				  | (1 << VCPU_EXREG_SEGMENTS)
				  | (1 << VCPU_EXREG_CR3));
	vcpu->arch.regs_dirty = 0;

	pt_guest_exit(vmx);

	/*
	 * eager fpu is enabled if PKEY is supported and CR4 is switched
	 * back on host, so it is safe to read guest PKRU from current
	 * XSAVE.
	 */
	if (static_cpu_has(X86_FEATURE_PKU) &&
	    kvm_read_cr4_bits(vcpu, X86_CR4_PKE)) {
		vcpu->arch.pkru = rdpkru();
		if (vcpu->arch.pkru != vmx->host_pkru)
			__write_pkru(vmx->host_pkru);
	}

	kvm_put_guest_xcr0(vcpu);

	vmx->nested.nested_run_pending = 0;
	vmx->idt_vectoring_info = 0;

	vmx->exit_reason = vmx->fail ? 0xdead : vmcs_read32(VM_EXIT_REASON);
	if ((u16)vmx->exit_reason == EXIT_REASON_MCE_DURING_VMENTRY)
		kvm_machine_check();

	if (vmx->fail || (vmx->exit_reason & VMX_EXIT_REASONS_FAILED_VMENTRY))
		return;

	vmx->loaded_vmcs->launched = 1;
	vmx->idt_vectoring_info = vmcs_read32(IDT_VECTORING_INFO_FIELD);

	vmx_recover_nmi_blocking(vmx);
	vmx_complete_interrupts(vmx);
}