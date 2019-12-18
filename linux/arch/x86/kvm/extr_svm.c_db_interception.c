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
struct kvm_vcpu {int guest_debug; struct kvm_run* run; } ;
struct vcpu_svm {TYPE_3__* vmcb; struct kvm_vcpu vcpu; scalar_t__ nmi_singlestep; } ;
struct TYPE_9__ {int /*<<< orphan*/  exception; scalar_t__ pc; } ;
struct TYPE_10__ {TYPE_4__ arch; } ;
struct kvm_run {TYPE_5__ debug; int /*<<< orphan*/  exit_reason; } ;
struct TYPE_6__ {scalar_t__ base; } ;
struct TYPE_7__ {scalar_t__ rip; TYPE_1__ cs; } ;
struct TYPE_8__ {TYPE_2__ save; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_VECTOR ; 
 int /*<<< orphan*/  KVM_EXIT_DEBUG ; 
 int KVM_GUESTDBG_SINGLESTEP ; 
 int KVM_GUESTDBG_USE_HW_BP ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  disable_nmi_singlestep (struct vcpu_svm*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_queue_exception (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db_interception(struct vcpu_svm *svm)
{
	struct kvm_run *kvm_run = svm->vcpu.run;
	struct kvm_vcpu *vcpu = &svm->vcpu;

	if (!(svm->vcpu.guest_debug &
	      (KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP)) &&
		!svm->nmi_singlestep) {
		kvm_queue_exception(&svm->vcpu, DB_VECTOR);
		return 1;
	}

	if (svm->nmi_singlestep) {
		disable_nmi_singlestep(svm);
		/* Make sure we check for pending NMIs upon entry */
		kvm_make_request(KVM_REQ_EVENT, vcpu);
	}

	if (svm->vcpu.guest_debug &
	    (KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP)) {
		kvm_run->exit_reason = KVM_EXIT_DEBUG;
		kvm_run->debug.arch.pc =
			svm->vmcb->save.cs.base + svm->vmcb->save.rip;
		kvm_run->debug.arch.exception = DB_VECTOR;
		return 0;
	}

	return 1;
}