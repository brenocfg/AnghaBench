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
typedef  int uint16_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TB0219_GPIO_OUTPUT ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tb0219_lock ; 
 int tb0219_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb0219_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int set_gpio_output_pin(unsigned int pin, char command)
{
	unsigned long flags;
	uint16_t value;

	if (command != '0' && command != '1')
		return -EINVAL;

	spin_lock_irqsave(&tb0219_lock, flags);
	value = tb0219_read(TB0219_GPIO_OUTPUT);
	if (command == '0')
		value &= ~(1 << pin);
	else
		value |= 1 << pin;
	tb0219_write(TB0219_GPIO_OUTPUT, value);
	spin_unlock_irqrestore(&tb0219_lock, flags);

	return 0;

}