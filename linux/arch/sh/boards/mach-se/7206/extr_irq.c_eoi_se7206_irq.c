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
 int /*<<< orphan*/  INTSTS0 ; 
 int /*<<< orphan*/  INTSTS1 ; 
#define  IRQ0_IRQ 130 
#define  IRQ1_IRQ 129 
#define  IRQ3_IRQ 128 
 unsigned short __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_se7206_irq (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_irq_disabled (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_irq_inprogress (struct irq_data*) ; 

__attribute__((used)) static void eoi_se7206_irq(struct irq_data *data)
{
	unsigned short sts0,sts1;
	unsigned int irq = data->irq;

	if (!irqd_irq_disabled(data) && !irqd_irq_inprogress(data))
		enable_se7206_irq(data);
	/* FPGA isr clear */
	sts0 = __raw_readw(INTSTS0);
	sts1 = __raw_readw(INTSTS1);

	switch (irq) {
	case IRQ0_IRQ:
		sts0 &= ~0x0010;
		break;
	case IRQ1_IRQ:
		sts0 &= ~0x000f;
		break;
	case IRQ3_IRQ:
		sts0 &= ~0x0f00;
		sts1 &= ~0x00ff;
		break;
	}
	__raw_writew(sts0, INTSTS0);
	__raw_writew(sts1, INTSTS1);
}