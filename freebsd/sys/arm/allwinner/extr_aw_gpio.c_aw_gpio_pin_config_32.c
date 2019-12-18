#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct aw_gpio_softc {TYPE_2__* padconf; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {size_t npins; TYPE_1__* pins; } ;
struct TYPE_3__ {size_t port; scalar_t__ pin; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t GPIO_PIN_INPUT ; 
 size_t GPIO_PIN_OUTPUT ; 
 int aw_gpio_pin_configure (struct aw_gpio_softc*,size_t,size_t) ; 
 struct aw_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_gpio_pin_config_32(device_t dev, uint32_t first_pin, uint32_t num_pins,
    uint32_t *pin_flags)
{
	struct aw_gpio_softc *sc;
	uint32_t bank, pin;
	int err;

	sc = device_get_softc(dev);
	if (first_pin > sc->padconf->npins)
		return (EINVAL);

	bank = sc->padconf->pins[first_pin].port;
	if (sc->padconf->pins[first_pin].pin != 0)
		return (EINVAL);

	/*
	 * The configuration for a bank of pins is scattered among several
	 * registers; we cannot g'tee to simultaneously change the state of all
	 * the pins in the flags array.  So just loop through the array
	 * configuring each pin for now.  If there was a strong need, it might
	 * be possible to support some limited simultaneous config, such as
	 * adjacent groups of 8 pins that line up the same as the config regs.
	 */
	for (err = 0, pin = first_pin; err == 0 && pin < num_pins; ++pin) {
		if (pin_flags[pin] & (GPIO_PIN_INPUT | GPIO_PIN_OUTPUT))
			err = aw_gpio_pin_configure(sc, pin, pin_flags[pin]);
	}

	return (err);
}