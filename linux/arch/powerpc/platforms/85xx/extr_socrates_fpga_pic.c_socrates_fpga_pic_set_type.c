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
struct irq_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FPGA_PIC_IRQCFG ; 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 scalar_t__ IRQ_TYPE_NONE ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 TYPE_1__* fpga_irqs ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  socrates_fpga_pic_lock ; 
 int socrates_fpga_pic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socrates_fpga_pic_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int socrates_fpga_pic_set_type(struct irq_data *d,
		unsigned int flow_type)
{
	unsigned long flags;
	unsigned int hwirq = irqd_to_hwirq(d);
	int polarity;
	u32 mask;

	if (fpga_irqs[hwirq].type != IRQ_TYPE_NONE)
		return -EINVAL;

	switch (flow_type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_LEVEL_HIGH:
		polarity = 1;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		polarity = 0;
		break;
	default:
		return -EINVAL;
	}
	raw_spin_lock_irqsave(&socrates_fpga_pic_lock, flags);
	mask = socrates_fpga_pic_read(FPGA_PIC_IRQCFG);
	if (polarity)
		mask |= (1 << hwirq);
	else
		mask &= ~(1 << hwirq);
	socrates_fpga_pic_write(FPGA_PIC_IRQCFG, mask);
	raw_spin_unlock_irqrestore(&socrates_fpga_pic_lock, flags);
	return 0;
}