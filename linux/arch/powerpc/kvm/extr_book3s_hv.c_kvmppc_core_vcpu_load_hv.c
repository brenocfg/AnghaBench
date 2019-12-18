#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kvmppc_vcore {scalar_t__ vcore_state; struct kvm_vcpu* runner; } ;
struct TYPE_2__ {scalar_t__ state; scalar_t__ busy_preempt; int /*<<< orphan*/  tbacct_lock; int /*<<< orphan*/  busy_stolen; struct kvmppc_vcore* vcore; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ KVMPPC_VCPU_BUSY_IN_HOST ; 
 scalar_t__ TB_NIL ; 
 scalar_t__ VCORE_SLEEPING ; 
 int /*<<< orphan*/  kvmppc_core_end_stolen (struct kvmppc_vcore*) ; 
 scalar_t__ mftb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void kvmppc_core_vcpu_load_hv(struct kvm_vcpu *vcpu, int cpu)
{
	struct kvmppc_vcore *vc = vcpu->arch.vcore;
	unsigned long flags;

	/*
	 * We can test vc->runner without taking the vcore lock,
	 * because only this task ever sets vc->runner to this
	 * vcpu, and once it is set to this vcpu, only this task
	 * ever sets it to NULL.
	 */
	if (vc->runner == vcpu && vc->vcore_state >= VCORE_SLEEPING)
		kvmppc_core_end_stolen(vc);

	spin_lock_irqsave(&vcpu->arch.tbacct_lock, flags);
	if (vcpu->arch.state == KVMPPC_VCPU_BUSY_IN_HOST &&
	    vcpu->arch.busy_preempt != TB_NIL) {
		vcpu->arch.busy_stolen += mftb() - vcpu->arch.busy_preempt;
		vcpu->arch.busy_preempt = TB_NIL;
	}
	spin_unlock_irqrestore(&vcpu->arch.tbacct_lock, flags);
}