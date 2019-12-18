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
typedef  int /*<<< orphan*/  u32 ;
struct of_mm_gpio_chip {scalar_t__ regs; } ;
struct irq_data {int dummy; } ;
struct altera_gpio_chip {int /*<<< orphan*/  gpio_lock; struct of_mm_gpio_chip mmchip; } ;

/* Variables and functions */
 scalar_t__ ALTERA_GPIO_IRQ_MASK ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 struct altera_gpio_chip* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void altera_gpio_irq_unmask(struct irq_data *d)
{
	struct altera_gpio_chip *altera_gc;
	struct of_mm_gpio_chip *mm_gc;
	unsigned long flags;
	u32 intmask;

	altera_gc = gpiochip_get_data(irq_data_get_irq_chip_data(d));
	mm_gc = &altera_gc->mmchip;

	raw_spin_lock_irqsave(&altera_gc->gpio_lock, flags);
	intmask = readl(mm_gc->regs + ALTERA_GPIO_IRQ_MASK);
	/* Set ALTERA_GPIO_IRQ_MASK bit to unmask */
	intmask |= BIT(irqd_to_hwirq(d));
	writel(intmask, mm_gc->regs + ALTERA_GPIO_IRQ_MASK);
	raw_spin_unlock_irqrestore(&altera_gc->gpio_lock, flags);
}