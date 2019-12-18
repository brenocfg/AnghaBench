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
struct gpiobus_softc {int /*<<< orphan*/  sc_dev; } ;
struct gpiobus_ivar {size_t npins; int /*<<< orphan*/ * pins; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 struct gpiobus_ivar* GPIOBUS_IVAR (int /*<<< orphan*/ ) ; 
 struct gpiobus_softc* GPIOBUS_SOFTC (int /*<<< orphan*/ ) ; 
 int GPIO_PIN_GETFLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
gpiobus_pin_getflags(device_t dev, device_t child, uint32_t pin, 
    uint32_t *flags)
{
	struct gpiobus_softc *sc = GPIOBUS_SOFTC(dev);
	struct gpiobus_ivar *devi = GPIOBUS_IVAR(child);

	if (pin >= devi->npins)
		return (EINVAL);

	return GPIO_PIN_GETFLAGS(sc->sc_dev, devi->pins[pin], flags);
}