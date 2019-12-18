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
typedef  int u64 ;
typedef  int u32 ;
struct xive_q {int idx; int msk; int /*<<< orphan*/  toggle; scalar_t__ qpage; } ;
struct xive_irq_data {int /*<<< orphan*/  eoi_page; } ;
struct seq_file {int dummy; } ;
struct kvmppc_xive_vcpu {scalar_t__* esc_virq; struct xive_q* queues; } ;
struct TYPE_2__ {struct kvmppc_xive_vcpu* xive_vcpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 unsigned int KVMPPC_XIVE_Q_COUNT ; 
 int /*<<< orphan*/  XIVE_ESB_GET ; 
 int XIVE_ESB_VAL_P ; 
 int XIVE_ESB_VAL_Q ; 
 int be32_to_cpup (scalar_t__) ; 
 struct xive_irq_data* irq_data_get_irq_handler_data (struct irq_data*) ; 
 struct irq_data* irq_get_irq_data (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int xive_vm_esb_load (struct xive_irq_data*,int /*<<< orphan*/ ) ; 

int kvmppc_xive_debug_show_queues(struct seq_file *m, struct kvm_vcpu *vcpu)
{
	struct kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	unsigned int i;

	for (i = 0; i < KVMPPC_XIVE_Q_COUNT; i++) {
		struct xive_q *q = &xc->queues[i];
		u32 i0, i1, idx;

		if (!q->qpage && !xc->esc_virq[i])
			continue;

		seq_printf(m, " [q%d]: ", i);

		if (q->qpage) {
			idx = q->idx;
			i0 = be32_to_cpup(q->qpage + idx);
			idx = (idx + 1) & q->msk;
			i1 = be32_to_cpup(q->qpage + idx);
			seq_printf(m, "T=%d %08x %08x...\n", q->toggle,
				   i0, i1);
		}
		if (xc->esc_virq[i]) {
			struct irq_data *d = irq_get_irq_data(xc->esc_virq[i]);
			struct xive_irq_data *xd =
				irq_data_get_irq_handler_data(d);
			u64 pq = xive_vm_esb_load(xd, XIVE_ESB_GET);

			seq_printf(m, "E:%c%c I(%d:%llx:%llx)",
				   (pq & XIVE_ESB_VAL_P) ? 'P' : 'p',
				   (pq & XIVE_ESB_VAL_Q) ? 'Q' : 'q',
				   xc->esc_virq[i], pq, xd->eoi_page);
			seq_puts(m, "\n");
		}
	}
	return 0;
}