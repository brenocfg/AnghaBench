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
struct gpiobacklight_softc {scalar_t__ sc_pin; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct gpiobacklight_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_pin_release (scalar_t__) ; 

__attribute__((used)) static int
gpiobacklight_detach(device_t dev)
{
	struct gpiobacklight_softc *sc;

	sc = device_get_softc(dev);

	if (sc->sc_pin)
		gpio_pin_release(sc->sc_pin);

	return (0);
}