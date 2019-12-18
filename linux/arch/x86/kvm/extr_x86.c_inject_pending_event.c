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
struct TYPE_6__ {int injected; int pending; scalar_t__ nr; int /*<<< orphan*/  error_code; int /*<<< orphan*/  has_error_code; } ;
struct TYPE_5__ {scalar_t__ injected; } ;
struct TYPE_7__ {int nmi_injected; int dr7; int smi_pending; scalar_t__ nmi_pending; int /*<<< orphan*/  smi_count; TYPE_2__ exception; TYPE_1__ interrupt; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_8__ {int (* check_nested_events ) (struct kvm_vcpu*,int) ;int /*<<< orphan*/  (* set_irq ) (struct kvm_vcpu*) ;scalar_t__ (* interrupt_allowed ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* set_nmi ) (struct kvm_vcpu*) ;scalar_t__ (* nmi_allowed ) (struct kvm_vcpu*) ;scalar_t__ (* smi_allowed ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* queue_exception ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 scalar_t__ DB_VECTOR ; 
 int DR7_GD ; 
 scalar_t__ EXCPT_FAULT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int X86_EFLAGS_RF ; 
 int /*<<< orphan*/  __kvm_set_rflags (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  enter_smm (struct kvm_vcpu*) ; 
 scalar_t__ exception_type (scalar_t__) ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_smm (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_cpu_get_interrupt (struct kvm_vcpu*) ; 
 scalar_t__ kvm_cpu_has_injectable_intr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_deliver_exception_payload (struct kvm_vcpu*) ; 
 scalar_t__ kvm_event_needs_reinjection (struct kvm_vcpu*) ; 
 int kvm_get_rflags (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_queue_interrupt (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvm_update_dr7 (struct kvm_vcpu*) ; 
 TYPE_4__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 
 scalar_t__ stub10 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub11 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub3 (struct kvm_vcpu*) ; 
 int stub4 (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  stub5 (struct kvm_vcpu*) ; 
 scalar_t__ stub6 (struct kvm_vcpu*) ; 
 scalar_t__ stub7 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub8 (struct kvm_vcpu*) ; 
 int stub9 (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  trace_kvm_inj_exception (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inject_pending_event(struct kvm_vcpu *vcpu, bool req_int_win)
{
	int r;

	/* try to reinject previous events if any */

	if (vcpu->arch.exception.injected)
		kvm_x86_ops->queue_exception(vcpu);
	/*
	 * Do not inject an NMI or interrupt if there is a pending
	 * exception.  Exceptions and interrupts are recognized at
	 * instruction boundaries, i.e. the start of an instruction.
	 * Trap-like exceptions, e.g. #DB, have higher priority than
	 * NMIs and interrupts, i.e. traps are recognized before an
	 * NMI/interrupt that's pending on the same instruction.
	 * Fault-like exceptions, e.g. #GP and #PF, are the lowest
	 * priority, but are only generated (pended) during instruction
	 * execution, i.e. a pending fault-like exception means the
	 * fault occurred on the *previous* instruction and must be
	 * serviced prior to recognizing any new events in order to
	 * fully complete the previous instruction.
	 */
	else if (!vcpu->arch.exception.pending) {
		if (vcpu->arch.nmi_injected)
			kvm_x86_ops->set_nmi(vcpu);
		else if (vcpu->arch.interrupt.injected)
			kvm_x86_ops->set_irq(vcpu);
	}

	/*
	 * Call check_nested_events() even if we reinjected a previous event
	 * in order for caller to determine if it should require immediate-exit
	 * from L2 to L1 due to pending L1 events which require exit
	 * from L2 to L1.
	 */
	if (is_guest_mode(vcpu) && kvm_x86_ops->check_nested_events) {
		r = kvm_x86_ops->check_nested_events(vcpu, req_int_win);
		if (r != 0)
			return r;
	}

	/* try to inject new event if pending */
	if (vcpu->arch.exception.pending) {
		trace_kvm_inj_exception(vcpu->arch.exception.nr,
					vcpu->arch.exception.has_error_code,
					vcpu->arch.exception.error_code);

		WARN_ON_ONCE(vcpu->arch.exception.injected);
		vcpu->arch.exception.pending = false;
		vcpu->arch.exception.injected = true;

		if (exception_type(vcpu->arch.exception.nr) == EXCPT_FAULT)
			__kvm_set_rflags(vcpu, kvm_get_rflags(vcpu) |
					     X86_EFLAGS_RF);

		if (vcpu->arch.exception.nr == DB_VECTOR) {
			/*
			 * This code assumes that nSVM doesn't use
			 * check_nested_events(). If it does, the
			 * DR6/DR7 changes should happen before L1
			 * gets a #VMEXIT for an intercepted #DB in
			 * L2.  (Under VMX, on the other hand, the
			 * DR6/DR7 changes should not happen in the
			 * event of a VM-exit to L1 for an intercepted
			 * #DB in L2.)
			 */
			kvm_deliver_exception_payload(vcpu);
			if (vcpu->arch.dr7 & DR7_GD) {
				vcpu->arch.dr7 &= ~DR7_GD;
				kvm_update_dr7(vcpu);
			}
		}

		kvm_x86_ops->queue_exception(vcpu);
	}

	/* Don't consider new event if we re-injected an event */
	if (kvm_event_needs_reinjection(vcpu))
		return 0;

	if (vcpu->arch.smi_pending && !is_smm(vcpu) &&
	    kvm_x86_ops->smi_allowed(vcpu)) {
		vcpu->arch.smi_pending = false;
		++vcpu->arch.smi_count;
		enter_smm(vcpu);
	} else if (vcpu->arch.nmi_pending && kvm_x86_ops->nmi_allowed(vcpu)) {
		--vcpu->arch.nmi_pending;
		vcpu->arch.nmi_injected = true;
		kvm_x86_ops->set_nmi(vcpu);
	} else if (kvm_cpu_has_injectable_intr(vcpu)) {
		/*
		 * Because interrupts can be injected asynchronously, we are
		 * calling check_nested_events again here to avoid a race condition.
		 * See https://lkml.org/lkml/2014/7/2/60 for discussion about this
		 * proposal and current concerns.  Perhaps we should be setting
		 * KVM_REQ_EVENT only on certain events and not unconditionally?
		 */
		if (is_guest_mode(vcpu) && kvm_x86_ops->check_nested_events) {
			r = kvm_x86_ops->check_nested_events(vcpu, req_int_win);
			if (r != 0)
				return r;
		}
		if (kvm_x86_ops->interrupt_allowed(vcpu)) {
			kvm_queue_interrupt(vcpu, kvm_cpu_get_interrupt(vcpu),
					    false);
			kvm_x86_ops->set_irq(vcpu);
		}
	}

	return 0;
}