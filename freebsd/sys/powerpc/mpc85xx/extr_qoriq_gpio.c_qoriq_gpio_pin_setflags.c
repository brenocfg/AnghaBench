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
typedef  int uint32_t ;
struct qoriq_gpio_softc {int /*<<< orphan*/  sc_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_GPDIR ; 
 int /*<<< orphan*/  GPIO_GPODR ; 
 int /*<<< orphan*/  GPIO_LOCK (struct qoriq_gpio_softc*) ; 
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_OPENDRAIN ; 
 int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct qoriq_gpio_softc*) ; 
 int /*<<< orphan*/  VALID_PIN (int) ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct qoriq_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qoriq_gpio_pin_setflags(device_t dev, uint32_t pin, uint32_t flags)
{
	struct qoriq_gpio_softc *sc = device_get_softc(dev);
	uint32_t reg;

	if (!VALID_PIN(pin))
		return (EINVAL);

	if ((flags & (GPIO_PIN_INPUT | GPIO_PIN_OUTPUT)) ==
	    (GPIO_PIN_INPUT | GPIO_PIN_OUTPUT))
		return (EINVAL);

	GPIO_LOCK(sc);
	if (flags & GPIO_PIN_INPUT) {
		reg = bus_read_4(sc->sc_mem, GPIO_GPDIR);
		reg &= ~(1 << (31 - pin));
		bus_write_4(sc->sc_mem, GPIO_GPDIR, reg);
	}
	else if (flags & GPIO_PIN_OUTPUT) {
		reg = bus_read_4(sc->sc_mem, GPIO_GPDIR);
		reg |= (1 << (31 - pin));
		bus_write_4(sc->sc_mem, GPIO_GPDIR, reg);
		reg = bus_read_4(sc->sc_mem, GPIO_GPODR);
		if (flags & GPIO_PIN_OPENDRAIN)
			reg |= (1 << (31 - pin));
		else
			reg &= ~(1 << (31 - pin));
		bus_write_4(sc->sc_mem, GPIO_GPODR, reg);
	}
	GPIO_UNLOCK(sc);
	return (0);
}