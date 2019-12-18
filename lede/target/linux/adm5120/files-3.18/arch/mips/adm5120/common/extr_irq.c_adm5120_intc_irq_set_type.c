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
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM5120_INTC_IRQ_BASE ; 
#define  ADM5120_IRQ_GPIO2 132 
#define  ADM5120_IRQ_GPIO4 131 
 int EINVAL ; 
 int /*<<< orphan*/  INTC_REG_INT_MODE ; 
#define  IRQ_TYPE_LEVEL_HIGH 130 
#define  IRQ_TYPE_LEVEL_LOW 129 
#define  IRQ_TYPE_NONE 128 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 unsigned long intc_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intc_write_reg (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int adm5120_intc_irq_set_type(struct irq_data *d, unsigned int flow_type)
{
	unsigned int irq = d->irq;
	unsigned int sense;
	unsigned long mode;
	int err = 0;

	sense = flow_type & (IRQ_TYPE_SENSE_MASK);
	switch (sense) {
	case IRQ_TYPE_NONE:
	case IRQ_TYPE_LEVEL_HIGH:
		break;
	case IRQ_TYPE_LEVEL_LOW:
		switch (irq) {
		case ADM5120_IRQ_GPIO2:
		case ADM5120_IRQ_GPIO4:
			break;
		default:
			err = -EINVAL;
			break;
		}
		break;
	default:
		err = -EINVAL;
		break;
	}

	if (err)
		return err;

	switch (irq) {
	case ADM5120_IRQ_GPIO2:
	case ADM5120_IRQ_GPIO4:
		mode = intc_read_reg(INTC_REG_INT_MODE);
		if (sense == IRQ_TYPE_LEVEL_LOW)
			mode |= (1 << (irq - ADM5120_INTC_IRQ_BASE));
		else
			mode &= ~(1 << (irq - ADM5120_INTC_IRQ_BASE));

		intc_write_reg(INTC_REG_INT_MODE, mode);
		break;
	}

	return 0;
}