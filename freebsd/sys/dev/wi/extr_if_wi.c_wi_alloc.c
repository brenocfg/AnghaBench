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
struct wi_softc {scalar_t__ wi_bus_type; int iobase_rid; int mem_rid; int irq_rid; int /*<<< orphan*/  sc_unit; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * irq; int /*<<< orphan*/ * mem; void* wi_bhandle; void* wi_btag; int /*<<< orphan*/ * iobase; int /*<<< orphan*/  wi_io_addr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ WI_BUS_PCCARD ; 
 scalar_t__ WI_BUS_PCI_NATIVE ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/ * bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 struct wi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ *) ; 
 void* rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ *) ; 
 int rman_make_alignment_flags (int) ; 
 int /*<<< orphan*/  wi_free (int /*<<< orphan*/ ) ; 

int
wi_alloc(device_t dev, int rid)
{
	struct wi_softc	*sc = device_get_softc(dev);

	if (sc->wi_bus_type != WI_BUS_PCI_NATIVE) {
		sc->iobase_rid = rid;
		sc->iobase = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT,
		    &sc->iobase_rid, (1 << 6),
		    rman_make_alignment_flags(1 << 6) | RF_ACTIVE);
		if (sc->iobase == NULL) {
			device_printf(dev, "No I/O space?!\n");
			return ENXIO;
		}

		sc->wi_io_addr = rman_get_start(sc->iobase);
		sc->wi_btag = rman_get_bustag(sc->iobase);
		sc->wi_bhandle = rman_get_bushandle(sc->iobase);
	} else {
		sc->mem_rid = rid;
		sc->mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
		    &sc->mem_rid, RF_ACTIVE);
		if (sc->mem == NULL) {
			device_printf(dev, "No Mem space on prism2.5?\n");
			return ENXIO;
		}

		sc->wi_btag = rman_get_bustag(sc->mem);
		sc->wi_bhandle = rman_get_bushandle(sc->mem);
	}

	sc->irq_rid = 0;
	sc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irq_rid,
	    RF_ACTIVE |
	    ((sc->wi_bus_type == WI_BUS_PCCARD) ? 0 : RF_SHAREABLE));
	if (sc->irq == NULL) {
		wi_free(dev);
		device_printf(dev, "No irq?!\n");
		return ENXIO;
	}

	sc->sc_dev = dev;
	sc->sc_unit = device_get_unit(dev);
	return 0;
}