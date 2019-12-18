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
typedef  scalar_t__ vm_paddr_t ;
struct resource {int dummy; } ;
struct ofw_pci_softc {int sc_nrange; struct ofw_pci_range* sc_range; } ;
struct ofw_pci_range {int pci_hi; scalar_t__ pci; scalar_t__ size; scalar_t__ host; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * bus_space_tag_t ;
typedef  scalar_t__ bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_GET_BUS_TAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int OFW_PCI_PHYS_HI_SPACEMASK ; 
#define  OFW_PCI_PHYS_HI_SPACE_IO 130 
#define  OFW_PCI_PHYS_HI_SPACE_MEM32 129 
#define  OFW_PCI_PHYS_HI_SPACE_MEM64 128 
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 int bus_generic_activate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int bus_space_map (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct ofw_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rman_activate_resource (struct resource*) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_set_virtual (struct resource*,void*) ; 

__attribute__((used)) static int
ofw_pci_activate_resource(device_t bus, device_t child, int type, int rid,
    struct resource *res)
{
	struct ofw_pci_softc *sc;
	bus_space_handle_t handle;
	bus_space_tag_t tag;
	struct ofw_pci_range *rp;
	vm_paddr_t start;
	int space;
	int rv;

	sc = device_get_softc(bus);

	if (type != SYS_RES_IOPORT && type != SYS_RES_MEMORY) {
		return (bus_generic_activate_resource(bus, child, type, rid,
		    res));
	}

	start = (vm_paddr_t)rman_get_start(res);

	/*
	 * Map this through the ranges list
	 */
	for (rp = sc->sc_range; rp < sc->sc_range + sc->sc_nrange &&
	    rp->pci_hi != 0; rp++) {
		if (start < rp->pci || start >= rp->pci + rp->size)
			continue;

		switch (rp->pci_hi & OFW_PCI_PHYS_HI_SPACEMASK) {
		case OFW_PCI_PHYS_HI_SPACE_IO:
			space = SYS_RES_IOPORT;
			break;
		case OFW_PCI_PHYS_HI_SPACE_MEM32:
		case OFW_PCI_PHYS_HI_SPACE_MEM64:
			space = SYS_RES_MEMORY;
			break;
		default:
			space = -1;
			}

		if (type == space) {
			start += (rp->host - rp->pci);
			break;
		}
	}

	if (bootverbose)
		printf("ofw_pci mapdev: start %jx, len %jd\n",
		    (rman_res_t)start, rman_get_size(res));

	tag = BUS_GET_BUS_TAG(child, child);
	if (tag == NULL)
		return (ENOMEM);

	rman_set_bustag(res, tag);
	rv = bus_space_map(tag, start,
	    rman_get_size(res), 0, &handle);
	if (rv != 0)
		return (ENOMEM);

	rman_set_bushandle(res, handle);
	rman_set_virtual(res, (void *)handle); /* XXX  for powerpc only ? */

	return (rman_activate_resource(res));
}