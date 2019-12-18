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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int JZ4780_GPIO_PINS ; 

__attribute__((used)) static int
jz4780_gpio_pin_max(device_t dev, int *maxpin)
{

	*maxpin = JZ4780_GPIO_PINS - 1;
	return (0);
}