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
struct rb4xx_cpld {unsigned int config; int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct rb4xx_cpld* gpio_to_cpld (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rb4xx_cpld_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct rb4xx_cpld *cpld = gpio_to_cpld(chip);
	int ret;

	mutex_lock(&cpld->lock);
	ret = (cpld->config >> offset) & 1;
	mutex_unlock(&cpld->lock);

	return ret;
}