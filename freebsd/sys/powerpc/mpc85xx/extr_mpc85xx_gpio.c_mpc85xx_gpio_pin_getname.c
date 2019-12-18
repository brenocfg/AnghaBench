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
 int EINVAL ; 
 int GPIOMAXNAME ; 
 int /*<<< orphan*/  VALID_PIN (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
mpc85xx_gpio_pin_getname(device_t dev, uint32_t pin, char *name)
{

	if (!VALID_PIN(pin))
		return (EINVAL);

	snprintf(name, GPIOMAXNAME, "GPIO%d", pin);
	name[GPIOMAXNAME-1] = '\0';

	return (0);
}