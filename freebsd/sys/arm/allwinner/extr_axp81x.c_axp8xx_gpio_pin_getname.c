#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIOMAXNAME ; 
 TYPE_1__* axp8xx_pins ; 
 size_t nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
axp8xx_gpio_pin_getname(device_t dev, uint32_t pin, char *name)
{
	if (pin >= nitems(axp8xx_pins))
		return (EINVAL);

	snprintf(name, GPIOMAXNAME, "%s", axp8xx_pins[pin].name);

	return (0);
}