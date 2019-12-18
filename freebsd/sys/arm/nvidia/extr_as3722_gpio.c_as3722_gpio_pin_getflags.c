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
 int AS3722_GPIO_IOSF_MASK ; 
 int AS3722_GPIO_IOSF_SHIFT ; 
 int AS3722_GPIO_MODE_MASK ; 
 int AS3722_GPIO_MODE_SHIFT ; 
 int AS3722_IOSF_GPIO ; 
#define  AS3722_MODE_INPUT 135 
#define  AS3722_MODE_INPUT_PULL_DOWN 134 
#define  AS3722_MODE_INPUT_PULL_UP_LV 133 
#define  AS3722_MODE_OPEN_DRAIN 132 
#define  AS3722_MODE_OPEN_DRAIN_LV 131 
#define  AS3722_MODE_PUSH_PULL 130 
#define  AS3722_MODE_PUSH_PULL_LV 129 
#define  AS3722_MODE_TRISTATE 128 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_LOCK (struct as3722_softc*) ; 
 size_t GPIO_PIN_INPUT ; 
 size_t GPIO_PIN_INVIN ; 
 size_t GPIO_PIN_INVOUT ; 
 size_t GPIO_PIN_OPENDRAIN ; 
 size_t GPIO_PIN_OUTPUT ; 
 size_t GPIO_PIN_PULLDOWN ; 
 size_t GPIO_PIN_PULLUP ; 
 size_t GPIO_PIN_TRISTATE ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct as3722_softc*) ; 
 struct as3722_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
as3722_gpio_pin_getflags(device_t dev, uint32_t pin, uint32_t *out_flags)
{
	struct as3722_softc *sc;
	uint8_t tmp, mode, iosf;
	uint32_t flags;
	bool inverted;

	sc = device_get_softc(dev);
	if (pin >= sc->gpio_npins)
		return (EINVAL);

	GPIO_LOCK(sc);
	tmp = sc->gpio_pins[pin]->pin_ctrl_reg;
	GPIO_UNLOCK(sc);
	iosf = (tmp >> AS3722_GPIO_IOSF_SHIFT) & AS3722_GPIO_IOSF_MASK;
	mode = (tmp >> AS3722_GPIO_MODE_SHIFT) & AS3722_GPIO_MODE_MASK;
	inverted = (tmp & AS3722_GPIO_INVERT) != 0;
	/* Is pin in GPIO mode ? */
	if (iosf != AS3722_IOSF_GPIO)
		return (ENXIO);

	flags = 0;
	switch (mode) {
	case AS3722_MODE_INPUT:
		flags = GPIO_PIN_INPUT;
		break;
	case AS3722_MODE_PUSH_PULL:
	case AS3722_MODE_PUSH_PULL_LV:
		flags = GPIO_PIN_OUTPUT;
		break;
	case AS3722_MODE_OPEN_DRAIN:
	case AS3722_MODE_OPEN_DRAIN_LV:
		flags = GPIO_PIN_INPUT | GPIO_PIN_OUTPUT | GPIO_PIN_OPENDRAIN;
		break;
	case AS3722_MODE_TRISTATE:
		flags = GPIO_PIN_TRISTATE;
		break;
	case AS3722_MODE_INPUT_PULL_UP_LV:
		flags = GPIO_PIN_INPUT | GPIO_PIN_PULLUP;
		break;

	case AS3722_MODE_INPUT_PULL_DOWN:
		flags = GPIO_PIN_OUTPUT | GPIO_PIN_PULLDOWN;
		break;
	}
	if (inverted)
		flags |= GPIO_PIN_INVIN | GPIO_PIN_INVOUT;
	*out_flags = flags;
	return (0);
}