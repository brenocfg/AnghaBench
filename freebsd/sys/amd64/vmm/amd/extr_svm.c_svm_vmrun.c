#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct vmcb_state {int rip; } ;
struct vmcb_ctrl {int vmcb_clean; } ;
struct vm_exit {int dummy; } ;
struct vm_eventinfo {int dummy; } ;
struct vm {int dummy; } ;
struct vlapic {int dummy; } ;
struct TYPE_7__ {scalar_t__ gen; } ;
struct svm_vcpu {scalar_t__ lastcpu; int dirty; int nextrip; TYPE_2__ asid; } ;
struct svm_softc {TYPE_1__* vcpu; struct vm* vm; } ;
struct svm_regctx {int dummy; } ;
typedef  int register_t ;
typedef  TYPE_3__* pmap_t ;
struct TYPE_8__ {int /*<<< orphan*/  pm_active; } ;
struct TYPE_6__ {int /*<<< orphan*/  vmcb_pa; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR_ATOMIC (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET_ATOMIC_ACQ (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VCPU_CTR1 (struct vm*,int,char*,int) ; 
 int /*<<< orphan*/  VCPU_MIGRATIONS ; 
 int /*<<< orphan*/  check_asid (struct svm_softc*,int,TYPE_3__*,scalar_t__) ; 
 scalar_t__ curcpu ; 
 int /*<<< orphan*/  disable_gintr () ; 
 int /*<<< orphan*/  enable_gintr () ; 
 int /*<<< orphan*/  get_pcpu () ; 
 int /*<<< orphan*/  lldt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_host_tss () ; 
 int /*<<< orphan*/  sldt () ; 
 int /*<<< orphan*/  svm_dr_enter_guest (struct svm_regctx*) ; 
 int /*<<< orphan*/  svm_dr_leave_guest (struct svm_regctx*) ; 
 struct svm_regctx* svm_get_guest_regctx (struct svm_softc*,int) ; 
 struct svm_vcpu* svm_get_vcpu (struct svm_softc*,int) ; 
 struct vmcb_ctrl* svm_get_vmcb_ctrl (struct svm_softc*,int) ; 
 struct vmcb_state* svm_get_vmcb_state (struct svm_softc*,int) ; 
 int /*<<< orphan*/  svm_inj_interrupts (struct svm_softc*,int,struct vlapic*) ; 
 int /*<<< orphan*/  svm_launch (int /*<<< orphan*/ ,struct svm_regctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svm_msr_guest_enter (struct svm_softc*,int) ; 
 int /*<<< orphan*/  svm_msr_guest_exit (struct svm_softc*,int) ; 
 int /*<<< orphan*/  svm_set_dirty (struct svm_softc*,int,int) ; 
 int svm_vmexit (struct svm_softc*,int,struct vm_exit*) ; 
 scalar_t__ vcpu_debugged (struct vm*,int) ; 
 scalar_t__ vcpu_rendezvous_pending (struct vm_eventinfo*) ; 
 scalar_t__ vcpu_reqidle (struct vm_eventinfo*) ; 
 scalar_t__ vcpu_should_yield (struct vm*,int) ; 
 scalar_t__ vcpu_suspended (struct vm_eventinfo*) ; 
 int /*<<< orphan*/  vm_exit_astpending (struct vm*,int,int) ; 
 int /*<<< orphan*/  vm_exit_debug (struct vm*,int,int) ; 
 int /*<<< orphan*/  vm_exit_rendezvous (struct vm*,int,int) ; 
 int /*<<< orphan*/  vm_exit_reqidle (struct vm*,int,int) ; 
 int /*<<< orphan*/  vm_exit_suspended (struct vm*,int,int) ; 
 struct vm_exit* vm_exitinfo (struct vm*,int) ; 
 struct vlapic* vm_lapic (struct vm*,int) ; 
 int vmcb_clean ; 
 int /*<<< orphan*/  vmm_stat_incr (struct vm*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
svm_vmrun(void *arg, int vcpu, register_t rip, pmap_t pmap, 
	struct vm_eventinfo *evinfo)
{
	struct svm_regctx *gctx;
	struct svm_softc *svm_sc;
	struct svm_vcpu *vcpustate;
	struct vmcb_state *state;
	struct vmcb_ctrl *ctrl;
	struct vm_exit *vmexit;
	struct vlapic *vlapic;
	struct vm *vm;
	uint64_t vmcb_pa;
	int handled;
	uint16_t ldt_sel;

	svm_sc = arg;
	vm = svm_sc->vm;

	vcpustate = svm_get_vcpu(svm_sc, vcpu);
	state = svm_get_vmcb_state(svm_sc, vcpu);
	ctrl = svm_get_vmcb_ctrl(svm_sc, vcpu);
	vmexit = vm_exitinfo(vm, vcpu);
	vlapic = vm_lapic(vm, vcpu);

	gctx = svm_get_guest_regctx(svm_sc, vcpu);
	vmcb_pa = svm_sc->vcpu[vcpu].vmcb_pa;

	if (vcpustate->lastcpu != curcpu) {
		/*
		 * Force new ASID allocation by invalidating the generation.
		 */
		vcpustate->asid.gen = 0;

		/*
		 * Invalidate the VMCB state cache by marking all fields dirty.
		 */
		svm_set_dirty(svm_sc, vcpu, 0xffffffff);

		/*
		 * XXX
		 * Setting 'vcpustate->lastcpu' here is bit premature because
		 * we may return from this function without actually executing
		 * the VMRUN  instruction. This could happen if a rendezvous
		 * or an AST is pending on the first time through the loop.
		 *
		 * This works for now but any new side-effects of vcpu
		 * migration should take this case into account.
		 */
		vcpustate->lastcpu = curcpu;
		vmm_stat_incr(vm, vcpu, VCPU_MIGRATIONS, 1);
	}

	svm_msr_guest_enter(svm_sc, vcpu);

	/* Update Guest RIP */
	state->rip = rip;

	do {
		/*
		 * Disable global interrupts to guarantee atomicity during
		 * loading of guest state. This includes not only the state
		 * loaded by the "vmrun" instruction but also software state
		 * maintained by the hypervisor: suspended and rendezvous
		 * state, NPT generation number, vlapic interrupts etc.
		 */
		disable_gintr();

		if (vcpu_suspended(evinfo)) {
			enable_gintr();
			vm_exit_suspended(vm, vcpu, state->rip);
			break;
		}

		if (vcpu_rendezvous_pending(evinfo)) {
			enable_gintr();
			vm_exit_rendezvous(vm, vcpu, state->rip);
			break;
		}

		if (vcpu_reqidle(evinfo)) {
			enable_gintr();
			vm_exit_reqidle(vm, vcpu, state->rip);
			break;
		}

		/* We are asked to give the cpu by scheduler. */
		if (vcpu_should_yield(vm, vcpu)) {
			enable_gintr();
			vm_exit_astpending(vm, vcpu, state->rip);
			break;
		}

		if (vcpu_debugged(vm, vcpu)) {
			enable_gintr();
			vm_exit_debug(vm, vcpu, state->rip);
			break;
		}

		/*
		 * #VMEXIT resumes the host with the guest LDTR, so
		 * save the current LDT selector so it can be restored
		 * after an exit.  The userspace hypervisor probably
		 * doesn't use a LDT, but save and restore it to be
		 * safe.
		 */
		ldt_sel = sldt();

		svm_inj_interrupts(svm_sc, vcpu, vlapic);

		/* Activate the nested pmap on 'curcpu' */
		CPU_SET_ATOMIC_ACQ(curcpu, &pmap->pm_active);

		/*
		 * Check the pmap generation and the ASID generation to
		 * ensure that the vcpu does not use stale TLB mappings.
		 */
		check_asid(svm_sc, vcpu, pmap, curcpu);

		ctrl->vmcb_clean = vmcb_clean & ~vcpustate->dirty;
		vcpustate->dirty = 0;
		VCPU_CTR1(vm, vcpu, "vmcb clean %#x", ctrl->vmcb_clean);

		/* Launch Virtual Machine. */
		VCPU_CTR1(vm, vcpu, "Resume execution at %#lx", state->rip);
		svm_dr_enter_guest(gctx);
		svm_launch(vmcb_pa, gctx, get_pcpu());
		svm_dr_leave_guest(gctx);

		CPU_CLR_ATOMIC(curcpu, &pmap->pm_active);

		/*
		 * The host GDTR and IDTR is saved by VMRUN and restored
		 * automatically on #VMEXIT. However, the host TSS needs
		 * to be restored explicitly.
		 */
		restore_host_tss();

		/* Restore host LDTR. */
		lldt(ldt_sel);

		/* #VMEXIT disables interrupts so re-enable them here. */ 
		enable_gintr();

		/* Update 'nextrip' */
		vcpustate->nextrip = state->rip;

		/* Handle #VMEXIT and if required return to user space. */
		handled = svm_vmexit(svm_sc, vcpu, vmexit);
	} while (handled);

	svm_msr_guest_exit(svm_sc, vcpu);

	return (0);
}