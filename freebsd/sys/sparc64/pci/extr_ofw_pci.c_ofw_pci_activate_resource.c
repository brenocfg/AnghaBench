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
struct resource {int dummy; } ;
struct ofw_pci_softc {scalar_t__* sc_pci_bh; struct bus_space_tag* sc_pci_iot; } ;
struct bus_space_tag {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 size_t OFW_PCI_CS_IO ; 
 size_t OFW_PCI_CS_MEM32 ; 
 int /*<<< orphan*/  PCI_MEMORY_BUS_SPACE ; 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 int bus_generic_activate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 struct ofw_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int rman_activate_resource (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,struct bus_space_tag*) ; 
 struct bus_space_tag* sparc64_alloc_bus_tag (struct resource*,int /*<<< orphan*/ ) ; 

int
ofw_pci_activate_resource(device_t bus, device_t child, int type, int rid,
    struct resource *r)
{
	struct ofw_pci_softc *sc;
	struct bus_space_tag *tag;

	sc = device_get_softc(bus);
	switch (type) {
	case SYS_RES_IRQ:
		return (bus_generic_activate_resource(bus, child, type, rid,
		    r));
	case SYS_RES_MEMORY:
		tag = sparc64_alloc_bus_tag(r, PCI_MEMORY_BUS_SPACE);
		if (tag == NULL)
			return (ENOMEM);
		rman_set_bustag(r, tag);
		rman_set_bushandle(r, sc->sc_pci_bh[OFW_PCI_CS_MEM32] +
		    rman_get_start(r));
		break;
	case SYS_RES_IOPORT:
		rman_set_bustag(r, sc->sc_pci_iot);
		rman_set_bushandle(r, sc->sc_pci_bh[OFW_PCI_CS_IO] +
		    rman_get_start(r));
		break;
	}
	return (rman_activate_resource(r));
}