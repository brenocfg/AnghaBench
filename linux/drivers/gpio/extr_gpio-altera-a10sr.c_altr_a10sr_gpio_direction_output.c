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
 unsigned int ALTR_A10SR_LED_VALID_SHIFT ; 
 unsigned int ALTR_A10SR_OUT_VALID_RANGE_HI ; 
 int EINVAL ; 
 int /*<<< orphan*/  altr_a10sr_gpio_set (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int altr_a10sr_gpio_direction_output(struct gpio_chip *gc,
					    unsigned int nr, int value)
{
	if (nr > (ALTR_A10SR_OUT_VALID_RANGE_HI - ALTR_A10SR_LED_VALID_SHIFT))
		return -EINVAL;

	altr_a10sr_gpio_set(gc, nr, value);
	return 0;
}