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
struct adp5520_gpio {int /*<<< orphan*/ * lut; int /*<<< orphan*/  master; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP5520_GPIO_CFG_2 ; 
 int adp5520_clr_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 struct adp5520_gpio* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int adp5520_gpio_direction_input(struct gpio_chip *chip, unsigned off)
{
	struct adp5520_gpio *dev;
	dev = gpiochip_get_data(chip);

	clear_bit(off, &dev->output);

	return adp5520_clr_bits(dev->master, ADP5520_GPIO_CFG_2,
				dev->lut[off]);
}