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
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 struct device_node* irq_domain_get_of_node (struct irq_domain*) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*,unsigned int) ; 

__attribute__((used)) static int octeon_irq_gpio_xlat(struct irq_domain *d,
				struct device_node *node,
				const u32 *intspec,
				unsigned int intsize,
				unsigned long *out_hwirq,
				unsigned int *out_type)
{
	unsigned int type;
	unsigned int pin;
	unsigned int trigger;

	if (irq_domain_get_of_node(d) != node)
		return -EINVAL;

	if (intsize < 2)
		return -EINVAL;

	pin = intspec[0];
	if (pin >= 16)
		return -EINVAL;

	trigger = intspec[1];

	switch (trigger) {
	case 1:
		type = IRQ_TYPE_EDGE_RISING;
		break;
	case 2:
		type = IRQ_TYPE_EDGE_FALLING;
		break;
	case 4:
		type = IRQ_TYPE_LEVEL_HIGH;
		break;
	case 8:
		type = IRQ_TYPE_LEVEL_LOW;
		break;
	default:
		pr_err("Error: (%pOFn) Invalid irq trigger specification: %x\n",
		       node,
		       trigger);
		type = IRQ_TYPE_LEVEL_LOW;
		break;
	}
	*out_type = type;
	*out_hwirq = pin;

	return 0;
}