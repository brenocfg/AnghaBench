#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct jz4780_gpio_softc {TYPE_1__* pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  pin_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int GPIOMAXNAME ; 
 size_t JZ4780_GPIO_PINS ; 
 struct jz4780_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
jz4780_gpio_pin_getname(device_t dev, uint32_t pin, char *name)
{
	struct jz4780_gpio_softc *sc;

	if (pin >= JZ4780_GPIO_PINS)
		return (EINVAL);

	sc = device_get_softc(dev);
	strncpy(name, sc->pins[pin].pin_name, GPIOMAXNAME - 1);
	name[GPIOMAXNAME - 1] = '\0';

	return (0);
}