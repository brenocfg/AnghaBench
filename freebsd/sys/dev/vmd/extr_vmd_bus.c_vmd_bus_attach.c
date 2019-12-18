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
struct vmd_softc {int /*<<< orphan*/  vmd_io_resource; int /*<<< orphan*/ * vmd_regs_resource; } ;
struct pci_devinfo {int /*<<< orphan*/  resources; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ PCI_DOMAINMAX ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct vmd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_add_child (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 struct pci_devinfo* pci_read_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  resource_list_add_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ rman_get_end (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmd_bus_attach(device_t dev)
{
	struct vmd_softc *sc;
	struct pci_devinfo *dinfo;
	rman_res_t start, end;
	int b, s, f;

	sc = device_get_softc(device_get_parent(dev));

	/* Start at max PCI vmd_domain and work down */
	b = s = f = 0;
	dinfo = pci_read_device(device_get_parent(dev), dev,
	     PCI_DOMAINMAX - device_get_unit(device_get_parent(dev)),
	     b, s, f);
	if (dinfo == NULL) {
		device_printf(dev, "Cannot allocate dinfo!\n");
		return (ENOENT);
	}

	pci_add_child(dev, dinfo);

	start = rman_get_start(sc->vmd_regs_resource[1]);
	end = rman_get_end(sc->vmd_regs_resource[1]);
	resource_list_add_next(&dinfo->resources, SYS_RES_MEMORY, start, end,
	    end - start + 1);

	start = rman_get_start(sc->vmd_io_resource);
	end = rman_get_end(sc->vmd_io_resource);
	resource_list_add_next(&dinfo->resources, SYS_RES_IOPORT, start, end,
	    end - start + 1);
 
	bus_generic_attach(dev);

	return (0);
}