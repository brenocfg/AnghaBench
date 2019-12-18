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
struct pci_softc {int /*<<< orphan*/  sc_dma_tag; int /*<<< orphan*/ * sc_bus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PCI_RES_BUS ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 struct pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int pcib_get_bus (int /*<<< orphan*/ ) ; 
 int pcib_get_domain (int /*<<< orphan*/ ) ; 

int
pci_attach_common(device_t dev)
{
	struct pci_softc *sc;
	int busno, domain;
#ifdef PCI_RES_BUS
	int rid;
#endif

	sc = device_get_softc(dev);
	domain = pcib_get_domain(dev);
	busno = pcib_get_bus(dev);
#ifdef PCI_RES_BUS
	rid = 0;
	sc->sc_bus = bus_alloc_resource(dev, PCI_RES_BUS, &rid, busno, busno,
	    1, 0);
	if (sc->sc_bus == NULL) {
		device_printf(dev, "failed to allocate bus number\n");
		return (ENXIO);
	}
#endif
	if (bootverbose)
		device_printf(dev, "domain=%d, physical bus=%d\n",
		    domain, busno);
	sc->sc_dma_tag = bus_get_dma_tag(dev);
	return (0);
}