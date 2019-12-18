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
struct intelspi_softc {int /*<<< orphan*/ * sc_irq_res; scalar_t__ sc_irq_rid; int /*<<< orphan*/ * sc_mem_res; scalar_t__ sc_mem_rid; int /*<<< orphan*/  sc_irq_ih; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_handle; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTELSPI_LOCK_DESTROY (struct intelspi_softc*) ; 
 int /*<<< orphan*/  INTELSPI_LOCK_INIT (struct intelspi_softc*) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct intelspi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct intelspi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  intelspi_init (struct intelspi_softc*) ; 
 int /*<<< orphan*/  intelspi_intr ; 

__attribute__((used)) static int
intelspi_attach(device_t dev)
{
	struct intelspi_softc	*sc;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_handle = acpi_get_handle(dev);

	INTELSPI_LOCK_INIT(sc);

	sc->sc_mem_rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(sc->sc_dev,
	    SYS_RES_MEMORY, &sc->sc_mem_rid, RF_ACTIVE);
	if (sc->sc_mem_res == NULL) {
		device_printf(dev, "can't allocate memory resource\n");
		goto error;
	}

	sc->sc_irq_rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(sc->sc_dev,
	    SYS_RES_IRQ, &sc->sc_irq_rid, RF_ACTIVE);
	if (sc->sc_irq_res == NULL) {
		device_printf(dev, "can't allocate IRQ resource\n");
		goto error;
	}

	/* Hook up our interrupt handler. */
	if (bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, intelspi_intr, sc, &sc->sc_irq_ih)) {
		device_printf(dev, "cannot setup the interrupt handler\n");
		goto error;
	}

	intelspi_init(sc);

	device_add_child(dev, "spibus", -1);

	return (bus_generic_attach(dev));

error:
	INTELSPI_LOCK_DESTROY(sc);

	if (sc->sc_mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    sc->sc_mem_rid, sc->sc_mem_res);

	if (sc->sc_irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ,
		    sc->sc_irq_rid, sc->sc_irq_res);

	return (ENXIO);
}