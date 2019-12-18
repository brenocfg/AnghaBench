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
struct gpiopower_softc {int sc_rbmask; int /*<<< orphan*/  sc_pin; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int RB_HALT ; 
 int RB_POWEROFF ; 
 struct gpiopower_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_pin_set_active (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gpiopower_assert(device_t dev, int howto)
{
	struct gpiopower_softc *sc;
	int do_assert;

	sc = device_get_softc(dev);
	do_assert = sc->sc_rbmask ? (sc->sc_rbmask & howto) :
	    ((howto & RB_HALT) == 0);

	if (!do_assert)
		return;

	if (howto & RB_POWEROFF)
		device_printf(dev, "powering system off\n");
	else if ((howto & RB_HALT) == 0)
		device_printf(dev, "resetting system\n");
	else
		return;

	gpio_pin_set_active(sc->sc_pin, true);

	/* Wait a second for it to trip */
	DELAY(10000000);
}