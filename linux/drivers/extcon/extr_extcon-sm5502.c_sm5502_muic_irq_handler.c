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
struct sm5502_muic_info {int num_muic_irqs; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  dev; TYPE_1__* muic_irqs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int virq; int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int sm5502_parse_irq (struct sm5502_muic_info*,int) ; 

__attribute__((used)) static irqreturn_t sm5502_muic_irq_handler(int irq, void *data)
{
	struct sm5502_muic_info *info = data;
	int i, irq_type = -1, ret;

	for (i = 0; i < info->num_muic_irqs; i++)
		if (irq == info->muic_irqs[i].virq)
			irq_type = info->muic_irqs[i].irq;

	ret = sm5502_parse_irq(info, irq_type);
	if (ret < 0) {
		dev_warn(info->dev, "cannot handle is interrupt:%d\n",
				    irq_type);
		return IRQ_HANDLED;
	}
	schedule_work(&info->irq_work);

	return IRQ_HANDLED;
}