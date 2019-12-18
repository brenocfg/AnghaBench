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
typedef  int u32 ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int /*<<< orphan*/  bgpio_lock; } ;
struct cdns_gpio_chip {scalar_t__ regs; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ CDNS_GPIO_IRQ_TYPE ; 
 scalar_t__ CDNS_GPIO_IRQ_VALUE ; 
 int EINVAL ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 struct cdns_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cdns_gpio_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(d);
	struct cdns_gpio_chip *cgpio = gpiochip_get_data(chip);
	unsigned long flags;
	u32 int_value;
	u32 int_type;
	u32 mask = BIT(d->hwirq);
	int ret = 0;

	spin_lock_irqsave(&chip->bgpio_lock, flags);

	int_value = ioread32(cgpio->regs + CDNS_GPIO_IRQ_VALUE) & ~mask;
	int_type = ioread32(cgpio->regs + CDNS_GPIO_IRQ_TYPE) & ~mask;

	/*
	 * The GPIO controller doesn't have an ACK register.
	 * All interrupt statuses are cleared on a status register read.
	 * Don't support edge interrupts for now.
	 */

	if (type == IRQ_TYPE_LEVEL_HIGH) {
		int_type |= mask;
		int_value |= mask;
	} else if (type == IRQ_TYPE_LEVEL_LOW) {
		int_type |= mask;
	} else {
		ret = -EINVAL;
		goto err_irq_type;
	}

	iowrite32(int_value, cgpio->regs + CDNS_GPIO_IRQ_VALUE);
	iowrite32(int_type, cgpio->regs + CDNS_GPIO_IRQ_TYPE);

err_irq_type:
	spin_unlock_irqrestore(&chip->bgpio_lock, flags);
	return ret;
}