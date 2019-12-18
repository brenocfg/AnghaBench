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
struct irq_data {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  force_external_irq_replay () ; 
 int /*<<< orphan*/  iosync () ; 
 scalar_t__ irqd_to_hwirq (struct irq_data*) ; 
 scalar_t__ opal_int_eoi (int) ; 
 int xics_pop_cppr () ; 

__attribute__((used)) static void icp_opal_eoi(struct irq_data *d)
{
	unsigned int hw_irq = (unsigned int)irqd_to_hwirq(d);
	int64_t rc;

	iosync();
	rc = opal_int_eoi((xics_pop_cppr() << 24) | hw_irq);

	/*
	 * EOI tells us whether there are more interrupts to fetch.
	 *
	 * Some HW implementations might not be able to send us another
	 * external interrupt in that case, so we force a replay.
	 */
	if (rc > 0)
		force_external_irq_replay();
}