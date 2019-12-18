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
struct irq_domain {int dummy; } ;
struct irq_alloc_info {int /*<<< orphan*/  pin; int /*<<< orphan*/  nasid; int /*<<< orphan*/  ctrl; } ;
struct bridge_irq_chip_data {int /*<<< orphan*/  nasid; int /*<<< orphan*/  bc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bridge_irq_chip ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,unsigned int,void*) ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bridge_irq_chip_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bridge_irq_chip_data*) ; 
 struct bridge_irq_chip_data* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bridge_domain_alloc(struct irq_domain *domain, unsigned int virq,
			       unsigned int nr_irqs, void *arg)
{
	struct bridge_irq_chip_data *data;
	struct irq_alloc_info *info = arg;
	int ret;

	if (nr_irqs > 1 || !info)
		return -EINVAL;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	ret = irq_domain_alloc_irqs_parent(domain, virq, nr_irqs, arg);
	if (ret >= 0) {
		data->bc = info->ctrl;
		data->nasid = info->nasid;
		irq_domain_set_info(domain, virq, info->pin, &bridge_irq_chip,
				    data, handle_level_irq, NULL, NULL);
	} else {
		kfree(data);
	}

	return ret;
}