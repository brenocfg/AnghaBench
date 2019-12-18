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
typedef  scalar_t__ u32 ;
struct kvmppc_vcpu_e500 {scalar_t__* pid; } ;
struct TYPE_2__ {scalar_t__ pid; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_e500_recalc_shadow_pid (struct kvmppc_vcpu_e500*) ; 
 struct kvmppc_vcpu_e500* to_e500 (struct kvm_vcpu*) ; 

void kvmppc_set_pid(struct kvm_vcpu *vcpu, u32 pid)
{
	struct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);

	if (vcpu->arch.pid != pid) {
		vcpu_e500->pid[0] = vcpu->arch.pid = pid;
		kvmppc_e500_recalc_shadow_pid(vcpu_e500);
	}
}