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
struct TYPE_2__ {int irq_type; int /*<<< orphan*/  mpic; int /*<<< orphan*/  dec_timer; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
#define  KVMPPC_IRQ_MPIC 130 
#define  KVMPPC_IRQ_XICS 129 
#define  KVMPPC_IRQ_XIVE 128 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_core_vcpu_free (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_mpic_disconnect_vcpu (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_remove_vcpu_debugfs (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_xics_free_icp (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_xive_cleanup_vcpu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_xive_native_cleanup_vcpu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  xics_on_xive () ; 

void kvm_arch_vcpu_free(struct kvm_vcpu *vcpu)
{
	/* Make sure we're not using the vcpu anymore */
	hrtimer_cancel(&vcpu->arch.dec_timer);

	kvmppc_remove_vcpu_debugfs(vcpu);

	switch (vcpu->arch.irq_type) {
	case KVMPPC_IRQ_MPIC:
		kvmppc_mpic_disconnect_vcpu(vcpu->arch.mpic, vcpu);
		break;
	case KVMPPC_IRQ_XICS:
		if (xics_on_xive())
			kvmppc_xive_cleanup_vcpu(vcpu);
		else
			kvmppc_xics_free_icp(vcpu);
		break;
	case KVMPPC_IRQ_XIVE:
		kvmppc_xive_native_cleanup_vcpu(vcpu);
		break;
	}

	kvmppc_core_vcpu_free(vcpu);
}