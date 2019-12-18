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

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 

__attribute__((used)) static int opal_event_set_type(struct irq_data *d, unsigned int flow_type)
{
	/*
	 * For now we only support level triggered events. The irq
	 * handler will be called continuously until the event has
	 * been cleared in OPAL.
	 */
	if (flow_type != IRQ_TYPE_LEVEL_HIGH)
		return -EINVAL;

	return 0;
}