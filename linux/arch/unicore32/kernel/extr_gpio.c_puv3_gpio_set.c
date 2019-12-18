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

/* Variables and functions */
 int /*<<< orphan*/  GPIO_GPCR ; 
 int /*<<< orphan*/  GPIO_GPIO (unsigned int) ; 
 int /*<<< orphan*/  GPIO_GPSR ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void puv3_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	if (value)
		writel(GPIO_GPIO(offset), GPIO_GPSR);
	else
		writel(GPIO_GPIO(offset), GPIO_GPCR);
}