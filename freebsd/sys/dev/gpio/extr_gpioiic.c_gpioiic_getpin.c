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
struct gpioiic_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_busdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOBUS_PIN_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  GPIOBUS_PIN_SETFLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_PIN_INPUT ; 

__attribute__((used)) static int
gpioiic_getpin(struct gpioiic_softc *sc, int pin)
{
	unsigned int			val;

	GPIOBUS_PIN_SETFLAGS(sc->sc_busdev, sc->sc_dev, pin, GPIO_PIN_INPUT);
	GPIOBUS_PIN_GET(sc->sc_busdev, sc->sc_dev, pin, &val);
	return ((int)val);
}