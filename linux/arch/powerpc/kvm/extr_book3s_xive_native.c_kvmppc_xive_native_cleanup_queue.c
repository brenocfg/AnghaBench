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
struct xive_q {int /*<<< orphan*/ * qpage; } ;
struct kvmppc_xive_vcpu {int /*<<< orphan*/  vp_id; struct xive_q* queues; } ;
struct TYPE_2__ {struct kvmppc_xive_vcpu* xive_vcpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xive_native_disable_queue (int /*<<< orphan*/ ,struct xive_q*,int) ; 

__attribute__((used)) static void kvmppc_xive_native_cleanup_queue(struct kvm_vcpu *vcpu, int prio)
{
	struct kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	struct xive_q *q = &xc->queues[prio];

	xive_native_disable_queue(xc->vp_id, q, prio);
	if (q->qpage) {
		put_page(virt_to_page(q->qpage));
		q->qpage = NULL;
	}
}