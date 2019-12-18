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
struct dln2_gpio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLN2_GPIO_PIN_GET_OUT_VAL ; 
 int dln2_gpio_pin_val (struct dln2_gpio*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int dln2_gpio_pin_get_out_val(struct dln2_gpio *dln2, unsigned int pin)
{
	int ret;

	ret = dln2_gpio_pin_val(dln2, DLN2_GPIO_PIN_GET_OUT_VAL, pin);
	if (ret < 0)
		return ret;
	return !!ret;
}