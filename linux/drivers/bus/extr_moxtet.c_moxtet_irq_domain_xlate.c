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
typedef  int u32 ;
struct TYPE_2__ {int exists; } ;
struct moxtet {TYPE_1__ irq; } ;
struct irq_domain {struct moxtet* host_data; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 unsigned int IRQ_TYPE_NONE ; 
 int MOXTET_NIRQS ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static int moxtet_irq_domain_xlate(struct irq_domain *d,
				   struct device_node *ctrlr,
				   const u32 *intspec, unsigned int intsize,
				   unsigned long *out_hwirq,
				   unsigned int *out_type)
{
	struct moxtet *moxtet = d->host_data;
	int irq;

	if (WARN_ON(intsize < 1))
		return -EINVAL;

	irq = intspec[0];

	if (irq >= MOXTET_NIRQS || !(moxtet->irq.exists & BIT(irq)))
		return -EINVAL;

	*out_hwirq = irq;
	*out_type = IRQ_TYPE_NONE;
	return 0;
}