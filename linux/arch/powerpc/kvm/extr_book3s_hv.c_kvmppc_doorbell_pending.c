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
struct kvmppc_vcore {int first_vcpuid; int dpdes; } ;
struct TYPE_2__ {struct kvmppc_vcore* vcore; scalar_t__ doorbell_request; } ;
struct kvm_vcpu {int vcpu_id; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static bool kvmppc_doorbell_pending(struct kvm_vcpu *vcpu)
{
	int thr;
	struct kvmppc_vcore *vc;

	if (vcpu->arch.doorbell_request)
		return true;
	/*
	 * Ensure that the read of vcore->dpdes comes after the read
	 * of vcpu->doorbell_request.  This barrier matches the
	 * smp_wmb() in kvmppc_guest_entry_inject().
	 */
	smp_rmb();
	vc = vcpu->arch.vcore;
	thr = vcpu->vcpu_id - vc->first_vcpuid;
	return !!(vc->dpdes & (1 << thr));
}