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
struct gpioiic_softc {int /*<<< orphan*/  scl_pin; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_busdev; int /*<<< orphan*/  sda_pin; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOBUS_PIN_SETFLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_PIN_INPUT ; 
 struct gpioiic_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gpioiic_reset_bus(device_t dev)
{
	struct gpioiic_softc		*sc = device_get_softc(dev);

	GPIOBUS_PIN_SETFLAGS(sc->sc_busdev, sc->sc_dev, sc->sda_pin,
	    GPIO_PIN_INPUT);
	GPIOBUS_PIN_SETFLAGS(sc->sc_busdev, sc->sc_dev, sc->scl_pin,
	    GPIO_PIN_INPUT);
}