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
struct gpioled_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_busdev; scalar_t__ sc_invert; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOBUS_PIN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GPIOBUS_PIN_SETFLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIOLED_LOCK (struct gpioled_softc*) ; 
 int /*<<< orphan*/  GPIOLED_PIN ; 
 int /*<<< orphan*/  GPIOLED_UNLOCK (struct gpioled_softc*) ; 
 int /*<<< orphan*/  GPIO_PIN_HIGH ; 
 int /*<<< orphan*/  GPIO_PIN_LOW ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 

__attribute__((used)) static void 
gpioled_control(void *priv, int onoff)
{
	struct gpioled_softc *sc;

	sc = (struct gpioled_softc *)priv;
	GPIOLED_LOCK(sc);
	if (GPIOBUS_PIN_SETFLAGS(sc->sc_busdev, sc->sc_dev, GPIOLED_PIN,
	    GPIO_PIN_OUTPUT) == 0) {
		if (sc->sc_invert)
			onoff = !onoff;
		GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev, GPIOLED_PIN,
		    onoff ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
	}
	GPIOLED_UNLOCK(sc);
}