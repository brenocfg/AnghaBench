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
struct mtk_spi_softc {int nonflash; TYPE_1__* gpio_cs; int /*<<< orphan*/  sc_mem_res; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  pin; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_PIN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPIO_PIN_SETFLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct mtk_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mtk_spi_wait (struct mtk_spi_softc*) ; 
 scalar_t__ ofw_bus_has_prop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_gpiobus_parse_gpios (int /*<<< orphan*/ ,char*,TYPE_1__**) ; 

__attribute__((used)) static int
mtk_spi_attach(device_t dev)
{
	struct mtk_spi_softc *sc = device_get_softc(dev);
	int rid;

	sc->sc_dev = dev;
        rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_SHAREABLE | RF_ACTIVE);
	if (!sc->sc_mem_res) {
		device_printf(dev, "Could not map memory\n");
		return (ENXIO);
	}

	if (mtk_spi_wait(sc)) {
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_mem_res);
		return (EBUSY);
	}

	if (ofw_bus_has_prop(dev, "non-flash"))
		sc->nonflash = 1;
	else
		sc->nonflash = 0;

	ofw_gpiobus_parse_gpios(dev, "cs-gpios", &sc->gpio_cs);

	if (sc->gpio_cs != NULL) {
		GPIO_PIN_SETFLAGS(sc->gpio_cs->dev, sc->gpio_cs->pin,
		    GPIO_PIN_OUTPUT);
		GPIO_PIN_SET(sc->gpio_cs->dev, sc->gpio_cs->pin, 1);
	}

	device_add_child(dev, "spibus", -1);
	return (bus_generic_attach(dev));
}