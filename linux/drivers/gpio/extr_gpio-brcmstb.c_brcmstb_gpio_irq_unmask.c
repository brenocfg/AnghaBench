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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int dummy; } ;
struct brcmstb_gpio_bank {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmstb_gpio_set_imask (struct brcmstb_gpio_bank*,int /*<<< orphan*/ ,int) ; 
 struct brcmstb_gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void brcmstb_gpio_irq_unmask(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct brcmstb_gpio_bank *bank = gpiochip_get_data(gc);

	brcmstb_gpio_set_imask(bank, d->hwirq, true);
}