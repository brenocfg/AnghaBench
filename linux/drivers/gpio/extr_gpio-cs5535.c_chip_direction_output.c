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
struct gpio_chip {int dummy; } ;
struct cs5535_gpio_chip {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_INPUT_ENABLE ; 
 int /*<<< orphan*/  GPIO_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  GPIO_OUTPUT_VAL ; 
 int /*<<< orphan*/  __cs5535_gpio_clear (struct cs5535_gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cs5535_gpio_set (struct cs5535_gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 struct cs5535_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int chip_direction_output(struct gpio_chip *c, unsigned offset, int val)
{
	struct cs5535_gpio_chip *chip = gpiochip_get_data(c);
	unsigned long flags;

	spin_lock_irqsave(&chip->lock, flags);

	__cs5535_gpio_set(chip, offset, GPIO_INPUT_ENABLE);
	__cs5535_gpio_set(chip, offset, GPIO_OUTPUT_ENABLE);
	if (val)
		__cs5535_gpio_set(chip, offset, GPIO_OUTPUT_VAL);
	else
		__cs5535_gpio_clear(chip, offset, GPIO_OUTPUT_VAL);

	spin_unlock_irqrestore(&chip->lock, flags);

	return 0;
}