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
struct kvmppc_vcore {scalar_t__ vcore_state; int /*<<< orphan*/  lock; struct kvm_vcpu* runner; } ;
struct TYPE_2__ {scalar_t__ state; struct kvmppc_vcore* vcore; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ KVMPPC_VCPU_RUNNABLE ; 
 scalar_t__ VCORE_INACTIVE ; 
 int kvm_vcpu_yield_to (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvm_arch_vcpu_yield_to(struct kvm_vcpu *target)
{
	struct kvmppc_vcore *vcore = target->arch.vcore;

	/*
	 * We expect to have been called by the real mode handler
	 * (kvmppc_rm_h_confer()) which would have directly returned
	 * H_SUCCESS if the source vcore wasn't idle (e.g. if it may
	 * have useful work to do and should not confer) so we don't
	 * recheck that here.
	 */

	spin_lock(&vcore->lock);
	if (target->arch.state == KVMPPC_VCPU_RUNNABLE &&
	    vcore->vcore_state != VCORE_INACTIVE &&
	    vcore->runner)
		target = vcore->runner;
	spin_unlock(&vcore->lock);

	return kvm_vcpu_yield_to(target);
}