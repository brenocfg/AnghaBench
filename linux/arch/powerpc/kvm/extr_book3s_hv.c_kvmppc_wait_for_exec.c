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
struct kvmppc_vcore {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  cpu_run; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 scalar_t__ KVMPPC_VCPU_RUNNABLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void kvmppc_wait_for_exec(struct kvmppc_vcore *vc,
				 struct kvm_vcpu *vcpu, int wait_state)
{
	DEFINE_WAIT(wait);

	prepare_to_wait(&vcpu->arch.cpu_run, &wait, wait_state);
	if (vcpu->arch.state == KVMPPC_VCPU_RUNNABLE) {
		spin_unlock(&vc->lock);
		schedule();
		spin_lock(&vc->lock);
	}
	finish_wait(&vcpu->arch.cpu_run, &wait);
}