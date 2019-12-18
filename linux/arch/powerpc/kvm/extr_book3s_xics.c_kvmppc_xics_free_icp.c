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
struct TYPE_2__ {int /*<<< orphan*/  irq_type; int /*<<< orphan*/ * icp; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVMPPC_IRQ_DEFAULT ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void kvmppc_xics_free_icp(struct kvm_vcpu *vcpu)
{
	if (!vcpu->arch.icp)
		return;
	kfree(vcpu->arch.icp);
	vcpu->arch.icp = NULL;
	vcpu->arch.irq_type = KVMPPC_IRQ_DEFAULT;
}