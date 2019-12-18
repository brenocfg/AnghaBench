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
struct adp5588_gpio {unsigned int* dir; int* dat_out; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 unsigned int ADP5588_BANK (unsigned int) ; 
 unsigned int ADP5588_BIT (unsigned int) ; 
 scalar_t__ GPIO_DAT_STAT1 ; 
 int adp5588_gpio_read (int /*<<< orphan*/ ,scalar_t__) ; 
 struct adp5588_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adp5588_gpio_get_value(struct gpio_chip *chip, unsigned off)
{
	struct adp5588_gpio *dev = gpiochip_get_data(chip);
	unsigned bank = ADP5588_BANK(off);
	unsigned bit = ADP5588_BIT(off);
	int val;

	mutex_lock(&dev->lock);

	if (dev->dir[bank] & bit)
		val = dev->dat_out[bank];
	else
		val = adp5588_gpio_read(dev->client, GPIO_DAT_STAT1 + bank);

	mutex_unlock(&dev->lock);

	return !!(val & bit);
}