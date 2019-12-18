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
typedef  size_t uint32_t ;
struct nct_softc {struct gpio_pin* pins; } ;
struct gpio_pin {size_t gp_caps; size_t gp_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_ASSERT_UNLOCKED (struct nct_softc*) ; 
 int /*<<< orphan*/  GPIO_LOCK (struct nct_softc*) ; 
 size_t GPIO_PIN_INPUT ; 
 size_t GPIO_PIN_INVIN ; 
 size_t GPIO_PIN_INVOUT ; 
 size_t GPIO_PIN_OPENDRAIN ; 
 size_t GPIO_PIN_OUTPUT ; 
 size_t GPIO_PIN_PUSHPULL ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct nct_softc*) ; 
 int /*<<< orphan*/  NCT_IS_VALID_PIN (size_t) ; 
 struct nct_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nct_set_pin_input (struct nct_softc*,size_t,int) ; 
 int /*<<< orphan*/  nct_set_pin_inverted (struct nct_softc*,size_t,int) ; 
 int /*<<< orphan*/  nct_set_pin_opendrain (struct nct_softc*,size_t) ; 
 int /*<<< orphan*/  nct_set_pin_pushpull (struct nct_softc*,size_t) ; 

__attribute__((used)) static int
nct_gpio_pin_setflags(device_t dev, uint32_t pin_num, uint32_t flags)
{
	struct nct_softc *sc;
	struct gpio_pin *pin;

	if (!NCT_IS_VALID_PIN(pin_num))
		return (EINVAL);

	sc = device_get_softc(dev);
	pin = &sc->pins[pin_num];
	if ((flags & pin->gp_caps) != flags)
		return (EINVAL);

	if ((flags & (GPIO_PIN_INPUT | GPIO_PIN_OUTPUT)) ==
		(GPIO_PIN_INPUT | GPIO_PIN_OUTPUT)) {
			return (EINVAL);
	}
	if ((flags & (GPIO_PIN_OPENDRAIN | GPIO_PIN_PUSHPULL)) ==
		(GPIO_PIN_OPENDRAIN | GPIO_PIN_PUSHPULL)) {
			return (EINVAL);
	}
	if ((flags & (GPIO_PIN_INVIN | GPIO_PIN_INVOUT)) ==
		(GPIO_PIN_INVIN | GPIO_PIN_INVOUT)) {
			return (EINVAL);
	}

	GPIO_ASSERT_UNLOCKED(sc);
	GPIO_LOCK(sc);
	if ((flags & (GPIO_PIN_INPUT | GPIO_PIN_OUTPUT)) != 0) {
		nct_set_pin_input(sc, pin_num, (flags & GPIO_PIN_INPUT) != 0);
		pin->gp_flags &= ~(GPIO_PIN_INPUT | GPIO_PIN_OUTPUT);
		pin->gp_flags |= flags & (GPIO_PIN_INPUT | GPIO_PIN_OUTPUT);
	}
	if ((flags & (GPIO_PIN_INVIN | GPIO_PIN_INVOUT)) != 0) {
		nct_set_pin_inverted(sc, pin_num,
		    (flags & GPIO_PIN_INVIN) != 0);
		pin->gp_flags &= ~(GPIO_PIN_INVIN | GPIO_PIN_INVOUT);
		pin->gp_flags |= flags & (GPIO_PIN_INVIN | GPIO_PIN_INVOUT);
	}
	if ((flags & (GPIO_PIN_OPENDRAIN | GPIO_PIN_PUSHPULL)) != 0) {
		if (flags & GPIO_PIN_OPENDRAIN)
			nct_set_pin_opendrain(sc, pin_num);
		else
			nct_set_pin_pushpull(sc, pin_num);
		pin->gp_flags &= ~(GPIO_PIN_OPENDRAIN | GPIO_PIN_PUSHPULL);
		pin->gp_flags |=
		    flags & (GPIO_PIN_OPENDRAIN | GPIO_PIN_PUSHPULL);
	}
	GPIO_UNLOCK(sc);

	return (0);
}