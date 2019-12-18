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
 int /*<<< orphan*/  GPIO_READ_BACK ; 
 int cs5535_gpio_isset (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chip_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	return cs5535_gpio_isset(offset, GPIO_READ_BACK);
}