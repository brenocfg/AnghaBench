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
struct altera_jtag_uart_softc {int /*<<< orphan*/ * ajus_mem_res; scalar_t__ ajus_mem_rid; int /*<<< orphan*/ * ajus_irq_res; scalar_t__ ajus_irq_rid; int /*<<< orphan*/  ajus_unit; int /*<<< orphan*/  ajus_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int altera_jtag_uart_attach (struct altera_jtag_uart_softc*) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 struct altera_jtag_uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
altera_jtag_uart_fdt_attach(device_t dev)
{
	struct altera_jtag_uart_softc *sc;
	int error;

	error = 0;
	sc = device_get_softc(dev);
	sc->ajus_dev = dev;
	sc->ajus_unit = device_get_unit(dev);
	sc->ajus_mem_rid = 0;
	sc->ajus_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->ajus_mem_rid, RF_ACTIVE);
	if (sc->ajus_mem_res == NULL) {
		device_printf(dev, "couldn't map memory\n");
		error = ENXIO;
		goto out;
	}

	/*
	 * Interrupt support is optional -- if we can't allocate an IRQ, then
	 * we fall back on polling.
	 */
	sc->ajus_irq_rid = 0;
	sc->ajus_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &sc->ajus_irq_rid, RF_ACTIVE | RF_SHAREABLE);
	if (sc->ajus_irq_res == NULL)
		device_printf(dev,
		    "IRQ unavailable; selecting polled operation\n");
	error = altera_jtag_uart_attach(sc);
out:
	if (error) {
		if (sc->ajus_irq_res != NULL)
			bus_release_resource(dev, SYS_RES_IRQ,
			    sc->ajus_irq_rid, sc->ajus_irq_res);
		if (sc->ajus_mem_res != NULL)
			bus_release_resource(dev, SYS_RES_MEMORY,
			    sc->ajus_mem_rid, sc->ajus_mem_res);
	}
	return (error);
}