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
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 scalar_t__ WARN (int,char*,int,...) ; 
 int of_irq_get (struct device_node*,int) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

void request_event_sources_irqs(struct device_node *np,
				irq_handler_t handler,
				const char *name)
{
	int i, virq, rc;

	for (i = 0; i < 16; i++) {
		virq = of_irq_get(np, i);
		if (virq < 0)
			return;
		if (WARN(!virq, "event-sources: Unable to allocate "
			        "interrupt number for %pOF\n", np))
			continue;

		rc = request_irq(virq, handler, 0, name, NULL);
		if (WARN(rc, "event-sources: Unable to request interrupt %d for %pOF\n",
		    virq, np))
			return;
	}
}