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
struct gpio_chip {unsigned int ngpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int GPIO_DATA_HI_REG ; 
 int /*<<< orphan*/  bcm63xx_gpio_lock ; 
 int /*<<< orphan*/  bcm_gpio_writel (int,int) ; 
 int gpio_out_high ; 
 int gpio_out_low ; 
 int gpio_out_low_reg ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm63xx_gpio_set(struct gpio_chip *chip,
			     unsigned gpio, int val)
{
	u32 reg;
	u32 mask;
	u32 *v;
	unsigned long flags;

	if (gpio >= chip->ngpio)
		BUG();

	if (gpio < 32) {
		reg = gpio_out_low_reg;
		mask = 1 << gpio;
		v = &gpio_out_low;
	} else {
		reg = GPIO_DATA_HI_REG;
		mask = 1 << (gpio - 32);
		v = &gpio_out_high;
	}

	spin_lock_irqsave(&bcm63xx_gpio_lock, flags);
	if (val)
		*v |= mask;
	else
		*v &= ~mask;
	bcm_gpio_writel(*v, reg);
	spin_unlock_irqrestore(&bcm63xx_gpio_lock, flags);
}