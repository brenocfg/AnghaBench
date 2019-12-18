#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
struct vmcb_state {scalar_t__ rip; int rflags; } ;
struct vmcb_ctrl {int eventinj; int v_tpr; scalar_t__ intr_shadow; } ;
struct vlapic {int dummy; } ;
struct svm_vcpu {scalar_t__ nextrip; } ;
struct svm_softc {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int IDT_NMI ; 
 int /*<<< orphan*/  IPI_AST ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PSL_I ; 
 int /*<<< orphan*/  VCPU_CTR0 (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  VCPU_CTR1 (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  VCPU_CTR2 (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/  VMCB_CACHE_TPR ; 
 int /*<<< orphan*/  VMCB_EVENTINJ_TYPE_INTR ; 
 int /*<<< orphan*/  VMCB_EVENTINJ_TYPE_NMI ; 
 int VMCB_EVENTINJ_VALID ; 
 int /*<<< orphan*/  curcpu ; 
 int /*<<< orphan*/  disable_intr_window_exiting (struct svm_softc*,int) ; 
 int /*<<< orphan*/  enable_intr_window_exiting (struct svm_softc*,int) ; 
 int /*<<< orphan*/  enable_nmi_blocking (struct svm_softc*,int) ; 
 int /*<<< orphan*/  ipi_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nmi_blocked (struct svm_softc*,int) ; 
 int /*<<< orphan*/  svm_eventinject (struct svm_softc*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct svm_vcpu* svm_get_vcpu (struct svm_softc*,int) ; 
 struct vmcb_ctrl* svm_get_vmcb_ctrl (struct svm_softc*,int) ; 
 struct vmcb_state* svm_get_vmcb_state (struct svm_softc*,int) ; 
 int /*<<< orphan*/  svm_inj_intinfo (struct svm_softc*,int) ; 
 int /*<<< orphan*/  svm_set_dirty (struct svm_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vatpic_intr_accepted (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vatpic_pending_intr (int /*<<< orphan*/ ,int*) ; 
 int vlapic_get_cr8 (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_intr_accepted (struct vlapic*,int) ; 
 int /*<<< orphan*/  vlapic_pending_intr (struct vlapic*,int*) ; 
 int /*<<< orphan*/  vm_extint_clear (int /*<<< orphan*/ ,int) ; 
 int vm_extint_pending (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_nmi_clear (int /*<<< orphan*/ ,int) ; 
 scalar_t__ vm_nmi_pending (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
svm_inj_interrupts(struct svm_softc *sc, int vcpu, struct vlapic *vlapic)
{
	struct vmcb_ctrl *ctrl;
	struct vmcb_state *state;
	struct svm_vcpu *vcpustate;
	uint8_t v_tpr;
	int vector, need_intr_window;
	int extint_pending;

	state = svm_get_vmcb_state(sc, vcpu);
	ctrl  = svm_get_vmcb_ctrl(sc, vcpu);
	vcpustate = svm_get_vcpu(sc, vcpu);

	need_intr_window = 0;

	if (vcpustate->nextrip != state->rip) {
		ctrl->intr_shadow = 0;
		VCPU_CTR2(sc->vm, vcpu, "Guest interrupt blocking "
		    "cleared due to rip change: %#lx/%#lx",
		    vcpustate->nextrip, state->rip);
	}

	/*
	 * Inject pending events or exceptions for this vcpu.
	 *
	 * An event might be pending because the previous #VMEXIT happened
	 * during event delivery (i.e. ctrl->exitintinfo).
	 *
	 * An event might also be pending because an exception was injected
	 * by the hypervisor (e.g. #PF during instruction emulation).
	 */
	svm_inj_intinfo(sc, vcpu);

	/* NMI event has priority over interrupts. */
	if (vm_nmi_pending(sc->vm, vcpu)) {
		if (nmi_blocked(sc, vcpu)) {
			/*
			 * Can't inject another NMI if the guest has not
			 * yet executed an "iret" after the last NMI.
			 */
			VCPU_CTR0(sc->vm, vcpu, "Cannot inject NMI due "
			    "to NMI-blocking");
		} else if (ctrl->intr_shadow) {
			/*
			 * Can't inject an NMI if the vcpu is in an intr_shadow.
			 */
			VCPU_CTR0(sc->vm, vcpu, "Cannot inject NMI due to "
			    "interrupt shadow");
			need_intr_window = 1;
			goto done;
		} else if (ctrl->eventinj & VMCB_EVENTINJ_VALID) {
			/*
			 * If there is already an exception/interrupt pending
			 * then defer the NMI until after that.
			 */
			VCPU_CTR1(sc->vm, vcpu, "Cannot inject NMI due to "
			    "eventinj %#lx", ctrl->eventinj);

			/*
			 * Use self-IPI to trigger a VM-exit as soon as
			 * possible after the event injection is completed.
			 *
			 * This works only if the external interrupt exiting
			 * is at a lower priority than the event injection.
			 *
			 * Although not explicitly specified in APMv2 the
			 * relative priorities were verified empirically.
			 */
			ipi_cpu(curcpu, IPI_AST);	/* XXX vmm_ipinum? */
		} else {
			vm_nmi_clear(sc->vm, vcpu);

			/* Inject NMI, vector number is not used */
			svm_eventinject(sc, vcpu, VMCB_EVENTINJ_TYPE_NMI,
			    IDT_NMI, 0, false);

			/* virtual NMI blocking is now in effect */
			enable_nmi_blocking(sc, vcpu);

			VCPU_CTR0(sc->vm, vcpu, "Injecting vNMI");
		}
	}

	extint_pending = vm_extint_pending(sc->vm, vcpu);
	if (!extint_pending) {
		if (!vlapic_pending_intr(vlapic, &vector))
			goto done;
		KASSERT(vector >= 16 && vector <= 255,
		    ("invalid vector %d from local APIC", vector));
	} else {
		/* Ask the legacy pic for a vector to inject */
		vatpic_pending_intr(sc->vm, &vector);
		KASSERT(vector >= 0 && vector <= 255,
		    ("invalid vector %d from INTR", vector));
	}

	/*
	 * If the guest has disabled interrupts or is in an interrupt shadow
	 * then we cannot inject the pending interrupt.
	 */
	if ((state->rflags & PSL_I) == 0) {
		VCPU_CTR2(sc->vm, vcpu, "Cannot inject vector %d due to "
		    "rflags %#lx", vector, state->rflags);
		need_intr_window = 1;
		goto done;
	}

	if (ctrl->intr_shadow) {
		VCPU_CTR1(sc->vm, vcpu, "Cannot inject vector %d due to "
		    "interrupt shadow", vector);
		need_intr_window = 1;
		goto done;
	}

	if (ctrl->eventinj & VMCB_EVENTINJ_VALID) {
		VCPU_CTR2(sc->vm, vcpu, "Cannot inject vector %d due to "
		    "eventinj %#lx", vector, ctrl->eventinj);
		need_intr_window = 1;
		goto done;
	}

	svm_eventinject(sc, vcpu, VMCB_EVENTINJ_TYPE_INTR, vector, 0, false);

	if (!extint_pending) {
		vlapic_intr_accepted(vlapic, vector);
	} else {
		vm_extint_clear(sc->vm, vcpu);
		vatpic_intr_accepted(sc->vm, vector);
	}

	/*
	 * Force a VM-exit as soon as the vcpu is ready to accept another
	 * interrupt. This is done because the PIC might have another vector
	 * that it wants to inject. Also, if the APIC has a pending interrupt
	 * that was preempted by the ExtInt then it allows us to inject the
	 * APIC vector as soon as possible.
	 */
	need_intr_window = 1;
done:
	/*
	 * The guest can modify the TPR by writing to %CR8. In guest mode
	 * the processor reflects this write to V_TPR without hypervisor
	 * intervention.
	 *
	 * The guest can also modify the TPR by writing to it via the memory
	 * mapped APIC page. In this case, the write will be emulated by the
	 * hypervisor. For this reason V_TPR must be updated before every
	 * VMRUN.
	 */
	v_tpr = vlapic_get_cr8(vlapic);
	KASSERT(v_tpr <= 15, ("invalid v_tpr %#x", v_tpr));
	if (ctrl->v_tpr != v_tpr) {
		VCPU_CTR2(sc->vm, vcpu, "VMCB V_TPR changed from %#x to %#x",
		    ctrl->v_tpr, v_tpr);
		ctrl->v_tpr = v_tpr;
		svm_set_dirty(sc, vcpu, VMCB_CACHE_TPR);
	}

	if (need_intr_window) {
		/*
		 * We use V_IRQ in conjunction with the VINTR intercept to
		 * trap into the hypervisor as soon as a virtual interrupt
		 * can be delivered.
		 *
		 * Since injected events are not subject to intercept checks
		 * we need to ensure that the V_IRQ is not actually going to
		 * be delivered on VM entry. The KASSERT below enforces this.
		 */
		KASSERT((ctrl->eventinj & VMCB_EVENTINJ_VALID) != 0 ||
		    (state->rflags & PSL_I) == 0 || ctrl->intr_shadow,
		    ("Bogus intr_window_exiting: eventinj (%#lx), "
		    "intr_shadow (%u), rflags (%#lx)",
		    ctrl->eventinj, ctrl->intr_shadow, state->rflags));
		enable_intr_window_exiting(sc, vcpu);
	} else {
		disable_intr_window_exiting(sc, vcpu);
	}
}