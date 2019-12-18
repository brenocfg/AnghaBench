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
struct gpiobus_softc {size_t sc_npins; TYPE_1__* sc_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ mapped; } ;

/* Variables and functions */
 struct gpiobus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t,...) ; 

int
gpiobus_release_pin(device_t bus, uint32_t pin)
{
	struct gpiobus_softc *sc;

	sc = device_get_softc(bus);
	/* Consistency check. */
	if (pin >= sc->sc_npins) {
		device_printf(bus,
		    "gpiobus_acquire_pin: invalid pin %d, max=%d\n",
		    pin, sc->sc_npins - 1);
		return (-1);
	}

	if (!sc->sc_pins[pin].mapped) {
		device_printf(bus, "gpiobus_acquire_pin: pin %d is not mapped\n", pin);
		return (-1);
	}
	sc->sc_pins[pin].mapped = 0;

	return (0);
}