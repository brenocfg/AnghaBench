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
typedef  int /*<<< orphan*/  u64 ;
struct kvmppc_vcore {int /*<<< orphan*/ * runnable_threads; int /*<<< orphan*/  n_runnable; } ;
struct TYPE_2__ {scalar_t__ state; size_t ptid; int /*<<< orphan*/  tbacct_lock; int /*<<< orphan*/  busy_preempt; scalar_t__ stolen_logged; int /*<<< orphan*/  busy_stolen; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ KVMPPC_VCPU_BUSY_IN_HOST ; 
 scalar_t__ KVMPPC_VCPU_RUNNABLE ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mftb () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ vcore_stolen_time (struct kvmppc_vcore*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_remove_runnable(struct kvmppc_vcore *vc,
				   struct kvm_vcpu *vcpu)
{
	u64 now;

	if (vcpu->arch.state != KVMPPC_VCPU_RUNNABLE)
		return;
	spin_lock_irq(&vcpu->arch.tbacct_lock);
	now = mftb();
	vcpu->arch.busy_stolen += vcore_stolen_time(vc, now) -
		vcpu->arch.stolen_logged;
	vcpu->arch.busy_preempt = now;
	vcpu->arch.state = KVMPPC_VCPU_BUSY_IN_HOST;
	spin_unlock_irq(&vcpu->arch.tbacct_lock);
	--vc->n_runnable;
	WRITE_ONCE(vc->runnable_threads[vcpu->arch.ptid], NULL);
}