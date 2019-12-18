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
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;
typedef  enum irq_domain_bus_token { ____Placeholder_irq_domain_bus_token } irq_domain_bus_token ;
struct TYPE_2__ {int (* match ) (struct device_node*) ;} ;

/* Variables and functions */
 int stub1 (struct device_node*) ; 
 TYPE_1__* xive_ops ; 

__attribute__((used)) static int xive_irq_domain_match(struct irq_domain *h, struct device_node *node,
				 enum irq_domain_bus_token bus_token)
{
	return xive_ops->match(node);
}