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
struct as3722_softc {int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * irq_h; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_addr; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  LOCK_DESTROY (struct as3722_softc*) ; 
 int /*<<< orphan*/  LOCK_INIT (struct as3722_softc*) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int as3722_get_version (struct as3722_softc*) ; 
 int as3722_gpio_attach (struct as3722_softc*,int /*<<< orphan*/ ) ; 
 int as3722_init (struct as3722_softc*) ; 
 int /*<<< orphan*/  as3722_intr ; 
 int as3722_parse_fdt (struct as3722_softc*,int /*<<< orphan*/ ) ; 
 int as3722_regulator_attach (struct as3722_softc*,int /*<<< orphan*/ ) ; 
 int as3722_rtc_attach (struct as3722_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct as3722_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* device_get_name (int /*<<< orphan*/ ) ; 
 struct as3722_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fdt_pinctrl_configure_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fdt_pinctrl_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iicbus_get_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
as3722_attach(device_t dev)
{
	struct as3722_softc *sc;
	const char *dname;
	int dunit, rv, rid;
	phandle_t node;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->bus_addr = iicbus_get_addr(dev);
	node = ofw_bus_get_node(sc->dev);
	dname = device_get_name(dev);
	dunit = device_get_unit(dev);
	rv = 0;
	LOCK_INIT(sc);

	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "Cannot allocate interrupt.\n");
		rv = ENXIO;
		goto fail;
	}

	rv = as3722_parse_fdt(sc, node);
	if (rv != 0)
		goto fail;
	rv = as3722_get_version(sc);
	if (rv != 0)
		goto fail;
	rv = as3722_init(sc);
	if (rv != 0)
		goto fail;
	rv = as3722_regulator_attach(sc, node);
	if (rv != 0)
		goto fail;
	rv = as3722_gpio_attach(sc, node);
	if (rv != 0)
		goto fail;
	rv = as3722_rtc_attach(sc, node);
	if (rv != 0)
		goto fail;

	fdt_pinctrl_register(dev, NULL);
	fdt_pinctrl_configure_by_name(dev, "default");

	/* Setup  interrupt. */
	rv = bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, as3722_intr, sc, &sc->irq_h);
	if (rv) {
		device_printf(dev, "Cannot setup interrupt.\n");
		goto fail;
	}
	return (bus_generic_attach(dev));

fail:
	if (sc->irq_h != NULL)
		bus_teardown_intr(dev, sc->irq_res, sc->irq_h);
	if (sc->irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq_res);
	LOCK_DESTROY(sc);
	return (rv);
}