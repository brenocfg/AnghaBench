#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qman_portal {int dummy; } ;
struct caam_napi {int /*<<< orphan*/  irqtask; struct qman_portal* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  QM_PIRQ_DQRI ; 
 scalar_t__ in_irq () ; 
 int /*<<< orphan*/  in_serving_softirq () ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qman_p_irqsource_remove (struct qman_portal*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int caam_qi_napi_schedule(struct qman_portal *p, struct caam_napi *np)
{
	/*
	 * In case of threaded ISR, for RT kernels in_irq() does not return
	 * appropriate value, so use in_serving_softirq to distinguish between
	 * softirq and irq contexts.
	 */
	if (unlikely(in_irq() || !in_serving_softirq())) {
		/* Disable QMan IRQ source and invoke NAPI */
		qman_p_irqsource_remove(p, QM_PIRQ_DQRI);
		np->p = p;
		napi_schedule(&np->irqtask);
		return 1;
	}
	return 0;
}