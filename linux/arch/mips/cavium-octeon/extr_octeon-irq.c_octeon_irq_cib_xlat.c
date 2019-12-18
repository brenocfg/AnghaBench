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
typedef  unsigned int u32 ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 

__attribute__((used)) static int octeon_irq_cib_xlat(struct irq_domain *d,
				   struct device_node *node,
				   const u32 *intspec,
				   unsigned int intsize,
				   unsigned long *out_hwirq,
				   unsigned int *out_type)
{
	unsigned int type = 0;

	if (intsize == 2)
		type = intspec[1];

	switch (type) {
	case 0: /* unofficial value, but we might as well let it work. */
	case 4: /* official value for level triggering. */
		*out_type = IRQ_TYPE_LEVEL_HIGH;
		break;
	case 1: /* official value for edge triggering. */
		*out_type = IRQ_TYPE_EDGE_RISING;
		break;
	default: /* Nothing else is acceptable. */
		return -EINVAL;
	}

	*out_hwirq = intspec[0];

	return 0;
}