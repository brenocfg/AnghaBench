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
struct gpio_spi_softc {int sc_sclk; int sc_mosi; int sc_miso; int sc_cs0; int sc_cs1; int sc_cs2; int sc_cs3; int sc_freq; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_busdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GPIOBUS_PIN_SETFLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_OUTPUT ; 
 int GPIO_PIN_PULLDOWN ; 
 int GPIO_PIN_PULLUP ; 
 scalar_t__ bootverbose ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct gpio_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  gpio_spi_chip_deactivate (struct gpio_spi_softc*,int) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
gpio_spi_attach(device_t dev)
{
	uint32_t value;
	struct gpio_spi_softc *sc;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_busdev = device_get_parent(dev);

	/* Required variables */
	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "sclk", &value))
		 return (ENXIO);
	sc->sc_sclk = value & 0xff;

	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "mosi", &value))
		 return (ENXIO);
	sc->sc_mosi = value & 0xff;

	/* Handle no miso; we just never read back from the device */
	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "miso", &value))
		 value = 0xff;
	sc->sc_miso = value & 0xff;

	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "cs0", &value))
		 return (ENXIO);
	sc->sc_cs0 = value & 0xff;

	/* Optional variables */
	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "cs1", &value))
		value = 0xff;
	sc->sc_cs1 = value & 0xff;

	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "cs2", &value))
		value = 0xff;
	sc->sc_cs2 = value & 0xff;

	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "cs3", &value))
		value = 0xff;
	sc->sc_cs3 = value & 0xff;

	/* Default to 100KHz */
	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "freq", &value)) {
		value = 100000;
	}
	sc->sc_freq = value;

	if (bootverbose) {
		device_printf(dev, "frequency: %d Hz\n",
		    sc->sc_freq);
		device_printf(dev,
		    "Use GPIO pins: sclk=%d, mosi=%d, miso=%d, "
		    "cs0=%d, cs1=%d, cs2=%d, cs3=%d\n",
		    sc->sc_sclk, sc->sc_mosi, sc->sc_miso,
		    sc->sc_cs0, sc->sc_cs1, sc->sc_cs2, sc->sc_cs3);
	}

	/* Set directions */
	GPIOBUS_PIN_SETFLAGS(sc->sc_busdev, sc->sc_dev, sc->sc_sclk,
	    GPIO_PIN_OUTPUT|GPIO_PIN_PULLDOWN);
	GPIOBUS_PIN_SETFLAGS(sc->sc_busdev, sc->sc_dev, sc->sc_mosi,
	    GPIO_PIN_OUTPUT|GPIO_PIN_PULLDOWN);
	if (sc->sc_miso != 0xff) {
		GPIOBUS_PIN_SETFLAGS(sc->sc_busdev, sc->sc_dev, sc->sc_miso,
		    GPIO_PIN_INPUT|GPIO_PIN_PULLDOWN);
	}

	GPIOBUS_PIN_SETFLAGS(sc->sc_busdev, sc->sc_dev, sc->sc_cs0,
	    GPIO_PIN_OUTPUT|GPIO_PIN_PULLUP);

	if (sc->sc_cs1 != 0xff)
		GPIOBUS_PIN_SETFLAGS(sc->sc_busdev, sc->sc_dev, sc->sc_cs1,
		    GPIO_PIN_OUTPUT|GPIO_PIN_PULLUP);
	if (sc->sc_cs2 != 0xff)
		GPIOBUS_PIN_SETFLAGS(sc->sc_busdev, sc->sc_dev, sc->sc_cs2,
		    GPIO_PIN_OUTPUT|GPIO_PIN_PULLUP);
	if (sc->sc_cs3 != 0xff)
		GPIOBUS_PIN_SETFLAGS(sc->sc_busdev, sc->sc_dev, sc->sc_cs3,
		    GPIO_PIN_OUTPUT|GPIO_PIN_PULLUP);

	gpio_spi_chip_deactivate(sc, -1);

	device_add_child(dev, "spibus", -1);
	return (bus_generic_attach(dev));
}