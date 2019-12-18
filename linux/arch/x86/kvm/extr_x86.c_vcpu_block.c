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
struct TYPE_6__ {int halted; } ;
struct TYPE_5__ {int pv_unhalted; } ;
struct TYPE_7__ {int mp_state; TYPE_2__ apf; TYPE_1__ pv; } ;
struct kvm_vcpu {TYPE_3__ arch; int /*<<< orphan*/  srcu_idx; } ;
struct kvm {int /*<<< orphan*/  srcu; } ;
struct TYPE_8__ {scalar_t__ (* pre_block ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* post_block ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int EINTR ; 
#define  KVM_MP_STATE_HALTED 130 
#define  KVM_MP_STATE_INIT_RECEIVED 129 
#define  KVM_MP_STATE_RUNNABLE 128 
 int /*<<< orphan*/  KVM_REQ_UNHALT ; 
 int /*<<< orphan*/  kvm_apic_accept_events (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_arch_vcpu_runnable (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_check_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_block (struct kvm_vcpu*) ; 
 TYPE_4__* kvm_x86_ops ; 
 int /*<<< orphan*/  srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*) ; 

__attribute__((used)) static inline int vcpu_block(struct kvm *kvm, struct kvm_vcpu *vcpu)
{
	if (!kvm_arch_vcpu_runnable(vcpu) &&
	    (!kvm_x86_ops->pre_block || kvm_x86_ops->pre_block(vcpu) == 0)) {
		srcu_read_unlock(&kvm->srcu, vcpu->srcu_idx);
		kvm_vcpu_block(vcpu);
		vcpu->srcu_idx = srcu_read_lock(&kvm->srcu);

		if (kvm_x86_ops->post_block)
			kvm_x86_ops->post_block(vcpu);

		if (!kvm_check_request(KVM_REQ_UNHALT, vcpu))
			return 1;
	}

	kvm_apic_accept_events(vcpu);
	switch(vcpu->arch.mp_state) {
	case KVM_MP_STATE_HALTED:
		vcpu->arch.pv.pv_unhalted = false;
		vcpu->arch.mp_state =
			KVM_MP_STATE_RUNNABLE;
		/* fall through */
	case KVM_MP_STATE_RUNNABLE:
		vcpu->arch.apf.halted = false;
		break;
	case KVM_MP_STATE_INIT_RECEIVED:
		break;
	default:
		return -EINTR;
		break;
	}
	return 1;
}