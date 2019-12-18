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
typedef  scalar_t__ uint32_t ;
typedef  int u_int ;
struct aw_gpio_softc {TYPE_1__* padconf; } ;
struct TYPE_2__ {scalar_t__ npins; } ;

/* Variables and functions */
 scalar_t__ AW_GPIO_INPUT ; 
 int /*<<< orphan*/  AW_GPIO_LOCK_ASSERT (struct aw_gpio_softc*) ; 
 int /*<<< orphan*/  AW_GPIO_NONE ; 
 scalar_t__ AW_GPIO_OUTPUT ; 
 int /*<<< orphan*/  AW_GPIO_PULLDOWN ; 
 int /*<<< orphan*/  AW_GPIO_PULLUP ; 
 int EINVAL ; 
 scalar_t__ GPIO_PIN_INPUT ; 
 scalar_t__ GPIO_PIN_OUTPUT ; 
 scalar_t__ GPIO_PIN_PRESET_HIGH ; 
 scalar_t__ GPIO_PIN_PRESET_LOW ; 
 scalar_t__ GPIO_PIN_PULLDOWN ; 
 scalar_t__ GPIO_PIN_PULLUP ; 
 scalar_t__ aw_gpio_get_function (struct aw_gpio_softc*,scalar_t__) ; 
 int /*<<< orphan*/  aw_gpio_pin_get_locked (struct aw_gpio_softc*,scalar_t__,int*) ; 
 int /*<<< orphan*/  aw_gpio_pin_set_locked (struct aw_gpio_softc*,scalar_t__,int) ; 
 int aw_gpio_set_function (struct aw_gpio_softc*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  aw_gpio_set_pud (struct aw_gpio_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_gpio_pin_configure(struct aw_gpio_softc *sc, uint32_t pin, uint32_t flags)
{
	u_int val;
	int err = 0;

	/* Must be called with lock held. */
	AW_GPIO_LOCK_ASSERT(sc);

	if (pin > sc->padconf->npins)
		return (EINVAL);

	/* Manage input/output. */
	if (flags & GPIO_PIN_INPUT) {
		err = aw_gpio_set_function(sc, pin, AW_GPIO_INPUT);
	} else if ((flags & GPIO_PIN_OUTPUT) &&
	    aw_gpio_get_function(sc, pin) != AW_GPIO_OUTPUT) {
		if (flags & GPIO_PIN_PRESET_LOW) {
			aw_gpio_pin_set_locked(sc, pin, 0);
		} else if (flags & GPIO_PIN_PRESET_HIGH) {
			aw_gpio_pin_set_locked(sc, pin, 1);
		} else {
			/* Read the pin and preset output to current state. */
			err = aw_gpio_set_function(sc, pin, AW_GPIO_INPUT);
			if (err == 0) {
				aw_gpio_pin_get_locked(sc, pin, &val);
				aw_gpio_pin_set_locked(sc, pin, val);
			}
		}
		if (err == 0)
			err = aw_gpio_set_function(sc, pin, AW_GPIO_OUTPUT);
	}

	if (err)
		return (err);

	/* Manage Pull-up/pull-down. */
	if (flags & GPIO_PIN_PULLUP)
		aw_gpio_set_pud(sc, pin, AW_GPIO_PULLUP);
	else if (flags & GPIO_PIN_PULLDOWN)
		aw_gpio_set_pud(sc, pin, AW_GPIO_PULLDOWN);
	else
		aw_gpio_set_pud(sc, pin, AW_GPIO_NONE);

	return (0);
}