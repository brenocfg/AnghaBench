#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int limit; } ;
struct TYPE_13__ {int limit; } ;
struct TYPE_12__ {int selector; int base; int attrib; int limit; } ;
struct vmcb_save_area {int dr6; int rip; scalar_t__ cr4; scalar_t__ cr3; int /*<<< orphan*/  g_pat; int /*<<< orphan*/  tr; int /*<<< orphan*/  ldtr; TYPE_3__ idtr; TYPE_2__ gdtr; TYPE_1__ cs; int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; int /*<<< orphan*/  ds; int /*<<< orphan*/  ss; int /*<<< orphan*/  es; } ;
struct vmcb_control_area {int /*<<< orphan*/  nested_ctl; int /*<<< orphan*/  int_ctl; int /*<<< orphan*/  virt_ext; scalar_t__ pause_filter_thresh; scalar_t__ pause_filter_count; void* msrpm_base_pa; void* iopm_base_pa; } ;
struct TYPE_16__ {int* regs; scalar_t__ hflags; int /*<<< orphan*/  pat; } ;
struct TYPE_17__ {int /*<<< orphan*/  kvm; TYPE_5__ arch; } ;
struct TYPE_15__ {scalar_t__ vmcb; } ;
struct vcpu_svm {TYPE_8__* vmcb; TYPE_6__ vcpu; TYPE_4__ nested; scalar_t__ asid_generation; int /*<<< orphan*/  msrpm; } ;
struct TYPE_18__ {struct vmcb_control_area control; struct vmcb_save_area save; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VECTOR ; 
 int /*<<< orphan*/  DB_VECTOR ; 
 int /*<<< orphan*/  GP_VECTOR ; 
 int /*<<< orphan*/  INTERCEPT_CLGI ; 
 int /*<<< orphan*/  INTERCEPT_CPUID ; 
 int /*<<< orphan*/  INTERCEPT_CR0_READ ; 
 int /*<<< orphan*/  INTERCEPT_CR0_WRITE ; 
 int /*<<< orphan*/  INTERCEPT_CR3_READ ; 
 int /*<<< orphan*/  INTERCEPT_CR3_WRITE ; 
 int /*<<< orphan*/  INTERCEPT_CR4_READ ; 
 int /*<<< orphan*/  INTERCEPT_CR4_WRITE ; 
 int /*<<< orphan*/  INTERCEPT_CR8_WRITE ; 
 int /*<<< orphan*/  INTERCEPT_HLT ; 
 int /*<<< orphan*/  INTERCEPT_INTR ; 
 int /*<<< orphan*/  INTERCEPT_INVD ; 
 int /*<<< orphan*/  INTERCEPT_INVLPG ; 
 int /*<<< orphan*/  INTERCEPT_INVLPGA ; 
 int /*<<< orphan*/  INTERCEPT_IOIO_PROT ; 
 int /*<<< orphan*/  INTERCEPT_MONITOR ; 
 int /*<<< orphan*/  INTERCEPT_MSR_PROT ; 
 int /*<<< orphan*/  INTERCEPT_MWAIT ; 
 int /*<<< orphan*/  INTERCEPT_NMI ; 
 int /*<<< orphan*/  INTERCEPT_PAUSE ; 
 int /*<<< orphan*/  INTERCEPT_RDPMC ; 
 int /*<<< orphan*/  INTERCEPT_RDPRU ; 
 int /*<<< orphan*/  INTERCEPT_RSM ; 
 int /*<<< orphan*/  INTERCEPT_SELECTIVE_CR0 ; 
 int /*<<< orphan*/  INTERCEPT_SHUTDOWN ; 
 int /*<<< orphan*/  INTERCEPT_SKINIT ; 
 int /*<<< orphan*/  INTERCEPT_SMI ; 
 int /*<<< orphan*/  INTERCEPT_STGI ; 
 int /*<<< orphan*/  INTERCEPT_TASK_SWITCH ; 
 int /*<<< orphan*/  INTERCEPT_VMLOAD ; 
 int /*<<< orphan*/  INTERCEPT_VMMCALL ; 
 int /*<<< orphan*/  INTERCEPT_VMRUN ; 
 int /*<<< orphan*/  INTERCEPT_VMSAVE ; 
 int /*<<< orphan*/  INTERCEPT_WBINVD ; 
 int /*<<< orphan*/  INTERCEPT_XSETBV ; 
 int /*<<< orphan*/  MC_VECTOR ; 
 int /*<<< orphan*/  PF_VECTOR ; 
 int /*<<< orphan*/  SEG_TYPE_BUSY_TSS16 ; 
 int /*<<< orphan*/  SEG_TYPE_LDT ; 
 int /*<<< orphan*/  SVM_NESTED_CTL_NP_ENABLE ; 
 int /*<<< orphan*/  SVM_NESTED_CTL_SEV_ENABLE ; 
 int SVM_SELECTOR_CODE_MASK ; 
 int SVM_SELECTOR_P_MASK ; 
 int SVM_SELECTOR_READ_MASK ; 
 int SVM_SELECTOR_S_MASK ; 
 int /*<<< orphan*/  UD_VECTOR ; 
 size_t VCPU_REGS_RIP ; 
 int /*<<< orphan*/  VIRTUAL_VMLOAD_VMSAVE_ENABLE_MASK ; 
 int /*<<< orphan*/  V_GIF_ENABLE_MASK ; 
 int /*<<< orphan*/  V_INTR_MASKING_MASK ; 
 int X86_CR0_CD ; 
 int X86_CR0_ET ; 
 int X86_CR0_NW ; 
 scalar_t__ X86_CR4_PAE ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 void* __sme_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avic_init_vmcb (struct vcpu_svm*) ; 
 int /*<<< orphan*/  clr_cr_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clr_exception_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clr_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_gif (struct vcpu_svm*) ; 
 scalar_t__ enable_vmware_backdoor ; 
 int /*<<< orphan*/  init_seg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_sys_seg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iopm_base ; 
 int /*<<< orphan*/  kvm_hlt_in_guest (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mmu_reset_context (TYPE_6__*) ; 
 int /*<<< orphan*/  kvm_mwait_in_guest (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_rflags (TYPE_6__*,int) ; 
 scalar_t__ kvm_vcpu_apicv_active (TYPE_6__*) ; 
 int /*<<< orphan*/  mark_all_dirty (TYPE_8__*) ; 
 scalar_t__ npt_enabled ; 
 scalar_t__ pause_filter_count ; 
 scalar_t__ pause_filter_thresh ; 
 int /*<<< orphan*/  set_cr_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dr_intercepts (struct vcpu_svm*) ; 
 int /*<<< orphan*/  set_exception_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 
 scalar_t__ sev_guest (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svm_set_cr0 (TYPE_6__*,int) ; 
 int /*<<< orphan*/  svm_set_efer (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vgif ; 
 scalar_t__ vls ; 

__attribute__((used)) static void init_vmcb(struct vcpu_svm *svm)
{
	struct vmcb_control_area *control = &svm->vmcb->control;
	struct vmcb_save_area *save = &svm->vmcb->save;

	svm->vcpu.arch.hflags = 0;

	set_cr_intercept(svm, INTERCEPT_CR0_READ);
	set_cr_intercept(svm, INTERCEPT_CR3_READ);
	set_cr_intercept(svm, INTERCEPT_CR4_READ);
	set_cr_intercept(svm, INTERCEPT_CR0_WRITE);
	set_cr_intercept(svm, INTERCEPT_CR3_WRITE);
	set_cr_intercept(svm, INTERCEPT_CR4_WRITE);
	if (!kvm_vcpu_apicv_active(&svm->vcpu))
		set_cr_intercept(svm, INTERCEPT_CR8_WRITE);

	set_dr_intercepts(svm);

	set_exception_intercept(svm, PF_VECTOR);
	set_exception_intercept(svm, UD_VECTOR);
	set_exception_intercept(svm, MC_VECTOR);
	set_exception_intercept(svm, AC_VECTOR);
	set_exception_intercept(svm, DB_VECTOR);
	/*
	 * Guest access to VMware backdoor ports could legitimately
	 * trigger #GP because of TSS I/O permission bitmap.
	 * We intercept those #GP and allow access to them anyway
	 * as VMware does.
	 */
	if (enable_vmware_backdoor)
		set_exception_intercept(svm, GP_VECTOR);

	set_intercept(svm, INTERCEPT_INTR);
	set_intercept(svm, INTERCEPT_NMI);
	set_intercept(svm, INTERCEPT_SMI);
	set_intercept(svm, INTERCEPT_SELECTIVE_CR0);
	set_intercept(svm, INTERCEPT_RDPMC);
	set_intercept(svm, INTERCEPT_CPUID);
	set_intercept(svm, INTERCEPT_INVD);
	set_intercept(svm, INTERCEPT_INVLPG);
	set_intercept(svm, INTERCEPT_INVLPGA);
	set_intercept(svm, INTERCEPT_IOIO_PROT);
	set_intercept(svm, INTERCEPT_MSR_PROT);
	set_intercept(svm, INTERCEPT_TASK_SWITCH);
	set_intercept(svm, INTERCEPT_SHUTDOWN);
	set_intercept(svm, INTERCEPT_VMRUN);
	set_intercept(svm, INTERCEPT_VMMCALL);
	set_intercept(svm, INTERCEPT_VMLOAD);
	set_intercept(svm, INTERCEPT_VMSAVE);
	set_intercept(svm, INTERCEPT_STGI);
	set_intercept(svm, INTERCEPT_CLGI);
	set_intercept(svm, INTERCEPT_SKINIT);
	set_intercept(svm, INTERCEPT_WBINVD);
	set_intercept(svm, INTERCEPT_XSETBV);
	set_intercept(svm, INTERCEPT_RDPRU);
	set_intercept(svm, INTERCEPT_RSM);

	if (!kvm_mwait_in_guest(svm->vcpu.kvm)) {
		set_intercept(svm, INTERCEPT_MONITOR);
		set_intercept(svm, INTERCEPT_MWAIT);
	}

	if (!kvm_hlt_in_guest(svm->vcpu.kvm))
		set_intercept(svm, INTERCEPT_HLT);

	control->iopm_base_pa = __sme_set(iopm_base);
	control->msrpm_base_pa = __sme_set(__pa(svm->msrpm));
	control->int_ctl = V_INTR_MASKING_MASK;

	init_seg(&save->es);
	init_seg(&save->ss);
	init_seg(&save->ds);
	init_seg(&save->fs);
	init_seg(&save->gs);

	save->cs.selector = 0xf000;
	save->cs.base = 0xffff0000;
	/* Executable/Readable Code Segment */
	save->cs.attrib = SVM_SELECTOR_READ_MASK | SVM_SELECTOR_P_MASK |
		SVM_SELECTOR_S_MASK | SVM_SELECTOR_CODE_MASK;
	save->cs.limit = 0xffff;

	save->gdtr.limit = 0xffff;
	save->idtr.limit = 0xffff;

	init_sys_seg(&save->ldtr, SEG_TYPE_LDT);
	init_sys_seg(&save->tr, SEG_TYPE_BUSY_TSS16);

	svm_set_efer(&svm->vcpu, 0);
	save->dr6 = 0xffff0ff0;
	kvm_set_rflags(&svm->vcpu, 2);
	save->rip = 0x0000fff0;
	svm->vcpu.arch.regs[VCPU_REGS_RIP] = save->rip;

	/*
	 * svm_set_cr0() sets PG and WP and clears NW and CD on save->cr0.
	 * It also updates the guest-visible cr0 value.
	 */
	svm_set_cr0(&svm->vcpu, X86_CR0_NW | X86_CR0_CD | X86_CR0_ET);
	kvm_mmu_reset_context(&svm->vcpu);

	save->cr4 = X86_CR4_PAE;
	/* rdx = ?? */

	if (npt_enabled) {
		/* Setup VMCB for Nested Paging */
		control->nested_ctl |= SVM_NESTED_CTL_NP_ENABLE;
		clr_intercept(svm, INTERCEPT_INVLPG);
		clr_exception_intercept(svm, PF_VECTOR);
		clr_cr_intercept(svm, INTERCEPT_CR3_READ);
		clr_cr_intercept(svm, INTERCEPT_CR3_WRITE);
		save->g_pat = svm->vcpu.arch.pat;
		save->cr3 = 0;
		save->cr4 = 0;
	}
	svm->asid_generation = 0;

	svm->nested.vmcb = 0;
	svm->vcpu.arch.hflags = 0;

	if (pause_filter_count) {
		control->pause_filter_count = pause_filter_count;
		if (pause_filter_thresh)
			control->pause_filter_thresh = pause_filter_thresh;
		set_intercept(svm, INTERCEPT_PAUSE);
	} else {
		clr_intercept(svm, INTERCEPT_PAUSE);
	}

	if (kvm_vcpu_apicv_active(&svm->vcpu))
		avic_init_vmcb(svm);

	/*
	 * If hardware supports Virtual VMLOAD VMSAVE then enable it
	 * in VMCB and clear intercepts to avoid #VMEXIT.
	 */
	if (vls) {
		clr_intercept(svm, INTERCEPT_VMLOAD);
		clr_intercept(svm, INTERCEPT_VMSAVE);
		svm->vmcb->control.virt_ext |= VIRTUAL_VMLOAD_VMSAVE_ENABLE_MASK;
	}

	if (vgif) {
		clr_intercept(svm, INTERCEPT_STGI);
		clr_intercept(svm, INTERCEPT_CLGI);
		svm->vmcb->control.int_ctl |= V_GIF_ENABLE_MASK;
	}

	if (sev_guest(svm->vcpu.kvm)) {
		svm->vmcb->control.nested_ctl |= SVM_NESTED_CTL_SEV_ENABLE;
		clr_exception_intercept(svm, UD_VECTOR);
	}

	mark_all_dirty(svm->vmcb);

	enable_gif(svm);

}