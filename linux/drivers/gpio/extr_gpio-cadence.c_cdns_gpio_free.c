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
struct gpio_chip {int /*<<< orphan*/  bgpio_lock; } ;
struct cdns_gpio_chip {int bypass_orig; scalar_t__ regs; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ CDNS_GPIO_BYPASS_MODE ; 
 struct cdns_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cdns_gpio_free(struct gpio_chip *chip, unsigned int offset)
{
	struct cdns_gpio_chip *cgpio = gpiochip_get_data(chip);
	unsigned long flags;

	spin_lock_irqsave(&chip->bgpio_lock, flags);

	iowrite32(ioread32(cgpio->regs + CDNS_GPIO_BYPASS_MODE) |
		  (BIT(offset) & cgpio->bypass_orig),
		  cgpio->regs + CDNS_GPIO_BYPASS_MODE);

	spin_unlock_irqrestore(&chip->bgpio_lock, flags);
}