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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ GPIOMAXNAME ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,int) ; 

__attribute__((used)) static int
rt1310_gpio_pin_getname(device_t dev, uint32_t pin, char *name)
{
	snprintf(name, GPIOMAXNAME - 1, "GPIO_%02d", pin);

	return (0);
}