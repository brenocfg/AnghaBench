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
typedef  int uint8_t ;
typedef  size_t uint32_t ;
struct as3722_softc {size_t gpio_npins; TYPE_1__** gpio_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int pin_ctrl_reg; } ;

/* Variables and functions */
 int AS3722_GPIO_INVERT ; 
 int AS3722_GPIO_MODE_MASK ; 
 int AS3722_GPIO_MODE_SHIFT ; 
 int /*<<< orphan*/  AS3722_GPIO_SIGNAL_IN ; 
 int /*<<< orphan*/  AS3722_GPIO_SIGNAL_OUT ; 
 int AS3722_MODE_PUSH_PULL ; 
 int AS3722_MODE_PUSH_PULL_LV ; 
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_LOCK (struct as3722_softc*) ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct as3722_softc*) ; 
 int RD1 (struct as3722_softc*,int /*<<< orphan*/ ,int*) ; 
 struct as3722_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
as3722_gpio_pin_get(device_t dev, uint32_t pin, uint32_t *val)
{
	struct as3722_softc *sc;
	uint8_t tmp, mode, ctrl;
	int rv;

	sc = device_get_softc(dev);
	if (pin >= sc->gpio_npins)
		return (EINVAL);

	GPIO_LOCK(sc);
	ctrl = sc->gpio_pins[pin]->pin_ctrl_reg;
	mode = (ctrl >> AS3722_GPIO_MODE_SHIFT) & AS3722_GPIO_MODE_MASK;
	if ((mode == AS3722_MODE_PUSH_PULL) ||
	    (mode == AS3722_MODE_PUSH_PULL_LV))
		rv = RD1(sc, AS3722_GPIO_SIGNAL_OUT, &tmp);
	else
		rv = RD1(sc, AS3722_GPIO_SIGNAL_IN, &tmp);
	GPIO_UNLOCK(sc);
	if (rv != 0)
		return (rv);

	*val = tmp & (1 << pin) ? 1 : 0;
	if (ctrl & AS3722_GPIO_INVERT)
		*val ^= 1;
	return (0);
}