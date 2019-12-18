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
typedef  int /*<<< orphan*/  u16 ;
struct vmcs_host_state {int /*<<< orphan*/  es_sel; int /*<<< orphan*/  ds_sel; int /*<<< orphan*/  ldt_sel; } ;
struct vcpu_vmx {int req_immediate_exit; int guest_msrs_ready; int save_nmsrs; int guest_state_loaded; int /*<<< orphan*/  msr_guest_kernel_gs_base; void* msr_host_kernel_gs_base; TYPE_2__* loaded_vmcs; TYPE_1__* guest_msrs; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_7__ {unsigned long fsbase; void* gsbase; int /*<<< orphan*/  gsindex; int /*<<< orphan*/  fsindex; } ;
struct TYPE_8__ {TYPE_3__ thread; int /*<<< orphan*/  mm; } ;
struct TYPE_6__ {struct vmcs_host_state host_state; } ;
struct TYPE_5__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  data; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_FS_BASE ; 
 int /*<<< orphan*/  MSR_KERNEL_GS_BASE ; 
 unsigned long cpu_kernelmode_gs_base (int) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  ds ; 
 int /*<<< orphan*/  es ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  gs ; 
 int /*<<< orphan*/  is_64bit_mm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_read_ldt () ; 
 int /*<<< orphan*/  kvm_set_shared_msr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int raw_smp_processor_id () ; 
 void* read_msr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_fsgs_for_kvm () ; 
 int /*<<< orphan*/  savesegment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long segment_base (int /*<<< orphan*/ ) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_set_host_fs_gs (struct vmcs_host_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vmx_prepare_switch_to_guest(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct vmcs_host_state *host_state;
#ifdef CONFIG_X86_64
	int cpu = raw_smp_processor_id();
#endif
	unsigned long fs_base, gs_base;
	u16 fs_sel, gs_sel;
	int i;

	vmx->req_immediate_exit = false;

	/*
	 * Note that guest MSRs to be saved/restored can also be changed
	 * when guest state is loaded. This happens when guest transitions
	 * to/from long-mode by setting MSR_EFER.LMA.
	 */
	if (!vmx->guest_msrs_ready) {
		vmx->guest_msrs_ready = true;
		for (i = 0; i < vmx->save_nmsrs; ++i)
			kvm_set_shared_msr(vmx->guest_msrs[i].index,
					   vmx->guest_msrs[i].data,
					   vmx->guest_msrs[i].mask);

	}
	if (vmx->guest_state_loaded)
		return;

	host_state = &vmx->loaded_vmcs->host_state;

	/*
	 * Set host fs and gs selectors.  Unfortunately, 22.2.3 does not
	 * allow segment selectors with cpl > 0 or ti == 1.
	 */
	host_state->ldt_sel = kvm_read_ldt();

#ifdef CONFIG_X86_64
	savesegment(ds, host_state->ds_sel);
	savesegment(es, host_state->es_sel);

	gs_base = cpu_kernelmode_gs_base(cpu);
	if (likely(is_64bit_mm(current->mm))) {
		save_fsgs_for_kvm();
		fs_sel = current->thread.fsindex;
		gs_sel = current->thread.gsindex;
		fs_base = current->thread.fsbase;
		vmx->msr_host_kernel_gs_base = current->thread.gsbase;
	} else {
		savesegment(fs, fs_sel);
		savesegment(gs, gs_sel);
		fs_base = read_msr(MSR_FS_BASE);
		vmx->msr_host_kernel_gs_base = read_msr(MSR_KERNEL_GS_BASE);
	}

	wrmsrl(MSR_KERNEL_GS_BASE, vmx->msr_guest_kernel_gs_base);
#else
	savesegment(fs, fs_sel);
	savesegment(gs, gs_sel);
	fs_base = segment_base(fs_sel);
	gs_base = segment_base(gs_sel);
#endif

	vmx_set_host_fs_gs(host_state, fs_sel, gs_sel, fs_base, gs_base);
	vmx->guest_state_loaded = true;
}