#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int retry; int /*<<< orphan*/ * irq; int /*<<< orphan*/ * port1; int /*<<< orphan*/ * port0; } ;
typedef  TYPE_1__ atkbdc_softc_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int atkbdc_attach_unit (int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* atkbdc_get_softc (int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atkbdc_isa_attach(device_t dev)
{
	atkbdc_softc_t	*sc;
	int		unit;
	int		error;
	int		rid;

	unit = device_get_unit(dev);
	sc = *(atkbdc_softc_t **)device_get_softc(dev);
	if (sc == NULL) {
		/*
		 * We have to maintain two copies of the kbdc_softc struct,
		 * as the low-level console needs to have access to the
		 * keyboard controller before kbdc is probed and attached.
		 * kbdc_soft[] contains the default entry for that purpose.
		 * See atkbdc.c. XXX
		 */
		sc = atkbdc_get_softc(unit);
		if (sc == NULL)
			return ENOMEM;
	}

	rid = 0;
	sc->retry = 5000;
	sc->port0 = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid,
					   RF_ACTIVE);
	if (sc->port0 == NULL)
		return ENXIO;
	rid = 1;
	sc->port1 = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid,
					   RF_ACTIVE);
	if (sc->port1 == NULL) {
		bus_release_resource(dev, SYS_RES_IOPORT, 0, sc->port0);
		return ENXIO;
	}

	/*
	 * If the device is not created by the PnP BIOS or ACPI, then
	 * the hint for the IRQ is on the child atkbd device, not the
	 * keyboard controller, so this can fail.
	 */
	rid = 0;
	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);

	error = atkbdc_attach_unit(unit, sc, sc->port0, sc->port1);
	if (error) {
		bus_release_resource(dev, SYS_RES_IOPORT, 0, sc->port0);
		bus_release_resource(dev, SYS_RES_IOPORT, 1, sc->port1);
		if (sc->irq != NULL)
			bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq);
		return error;
	}
	*(atkbdc_softc_t **)device_get_softc(dev) = sc;

	bus_generic_probe(dev);
	bus_generic_attach(dev);

	return 0;
}