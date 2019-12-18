#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvmppc_xive_vcpu {int valid; int /*<<< orphan*/  vp_id; scalar_t__* esc_virq; struct kvmppc_xive_vcpu** esc_virq_names; TYPE_1__* xive; int /*<<< orphan*/  server_num; } ;
struct TYPE_4__ {struct kvmppc_xive_vcpu* xive_vcpu; int /*<<< orphan*/  irq_type; scalar_t__ xive_cam_word; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {scalar_t__ single_escalation; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVMPPC_IRQ_DEFAULT ; 
 int KVMPPC_XIVE_Q_COUNT ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct kvmppc_xive_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_xive_disable_vcpu_interrupts (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_xive_enabled (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_xive_native_cleanup_queue (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_cleanup_single_escalation (struct kvm_vcpu*,struct kvmppc_xive_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  xive_native_disable_vp (int /*<<< orphan*/ ) ; 

void kvmppc_xive_native_cleanup_vcpu(struct kvm_vcpu *vcpu)
{
	struct kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	int i;

	if (!kvmppc_xive_enabled(vcpu))
		return;

	if (!xc)
		return;

	pr_devel("native_cleanup_vcpu(cpu=%d)\n", xc->server_num);

	/* Ensure no interrupt is still routed to that VP */
	xc->valid = false;
	kvmppc_xive_disable_vcpu_interrupts(vcpu);

	/* Free escalations */
	for (i = 0; i < KVMPPC_XIVE_Q_COUNT; i++) {
		/* Free the escalation irq */
		if (xc->esc_virq[i]) {
			if (xc->xive->single_escalation)
				xive_cleanup_single_escalation(vcpu, xc,
							xc->esc_virq[i]);
			free_irq(xc->esc_virq[i], vcpu);
			irq_dispose_mapping(xc->esc_virq[i]);
			kfree(xc->esc_virq_names[i]);
			xc->esc_virq[i] = 0;
		}
	}

	/* Disable the VP */
	xive_native_disable_vp(xc->vp_id);

	/* Clear the cam word so guest entry won't try to push context */
	vcpu->arch.xive_cam_word = 0;

	/* Free the queues */
	for (i = 0; i < KVMPPC_XIVE_Q_COUNT; i++) {
		kvmppc_xive_native_cleanup_queue(vcpu, i);
	}

	/* Free the VP */
	kfree(xc);

	/* Cleanup the vcpu */
	vcpu->arch.irq_type = KVMPPC_IRQ_DEFAULT;
	vcpu->arch.xive_vcpu = NULL;
}