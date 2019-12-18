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
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct dio48e_gpio {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_mask; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 struct dio48e_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 unsigned long irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dio48e_irq_unmask(struct irq_data *data)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(data);
	struct dio48e_gpio *const dio48egpio = gpiochip_get_data(chip);
	const unsigned long offset = irqd_to_hwirq(data);
	unsigned long flags;

	/* only bit 3 on each respective Port C supports interrupts */
	if (offset != 19 && offset != 43)
		return;

	raw_spin_lock_irqsave(&dio48egpio->lock, flags);

	if (!dio48egpio->irq_mask) {
		/* enable interrupts */
		outb(0x00, dio48egpio->base + 0xF);
		outb(0x00, dio48egpio->base + 0xB);
	}

	if (offset == 19)
		dio48egpio->irq_mask |= BIT(0);
	else
		dio48egpio->irq_mask |= BIT(1);

	raw_spin_unlock_irqrestore(&dio48egpio->lock, flags);
}