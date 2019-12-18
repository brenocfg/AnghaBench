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
struct ti_gpio_softc {int /*<<< orphan*/ * sc_busdev; int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/  sc_irq_hdl; void* sc_irq_res; scalar_t__ sc_irq_rid; scalar_t__ sc_mem_rid; int /*<<< orphan*/  sc_maxpin; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TI_GPIO_LOCK_INIT (struct ti_gpio_softc*) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ti_gpio_softc*,int /*<<< orphan*/ *) ; 
 struct ti_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int ti_gpio_bank_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_gpio_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_gpio_intr ; 
 scalar_t__ ti_gpio_pic_attach (struct ti_gpio_softc*) ; 
 int /*<<< orphan*/  ti_gpio_pin_max (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ti_gpio_attach(device_t dev)
{
	struct ti_gpio_softc *sc;
	int err;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	TI_GPIO_LOCK_INIT(sc);
	ti_gpio_pin_max(dev, &sc->sc_maxpin);
	sc->sc_maxpin++;

	sc->sc_mem_rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->sc_mem_rid, RF_ACTIVE);
	if (!sc->sc_mem_res) {
		device_printf(dev, "Error: could not allocate mem resources\n");
		ti_gpio_detach(dev);
		return (ENXIO);
	}

	sc->sc_irq_rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &sc->sc_irq_rid, RF_ACTIVE);
	if (!sc->sc_irq_res) {
		device_printf(dev, "Error: could not allocate irq resources\n");
		ti_gpio_detach(dev);
		return (ENXIO);
	}

	/*
	 * Register our interrupt filter for each of the IRQ resources.
	 */
	if (bus_setup_intr(dev, sc->sc_irq_res,
	    INTR_TYPE_MISC | INTR_MPSAFE, ti_gpio_intr, NULL, sc,
	    &sc->sc_irq_hdl) != 0) {
		device_printf(dev,
		    "WARNING: unable to register interrupt filter\n");
		ti_gpio_detach(dev);
		return (ENXIO);
	}

	if (ti_gpio_pic_attach(sc) != 0) {
		device_printf(dev, "WARNING: unable to attach PIC\n");
		ti_gpio_detach(dev);
		return (ENXIO);
	}

	/* We need to go through each block and ensure the clocks are running and
	 * the module is enabled.  It might be better to do this only when the
	 * pins are configured which would result in less power used if the GPIO
	 * pins weren't used ... 
	 */
	if (sc->sc_mem_res != NULL) {
		/* Initialize the GPIO module. */
		err = ti_gpio_bank_init(dev);
		if (err != 0) {
			ti_gpio_detach(dev);
			return (err);
		}
	}

	sc->sc_busdev = gpiobus_attach_bus(dev);
	if (sc->sc_busdev == NULL) {
		ti_gpio_detach(dev);
		return (ENXIO);
	}

	return (0);
}