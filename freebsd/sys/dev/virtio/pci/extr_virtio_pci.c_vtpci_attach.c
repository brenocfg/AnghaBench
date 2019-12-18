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
struct vtpci_softc {int /*<<< orphan*/ * vtpci_child_dev; int /*<<< orphan*/  vtpci_flags; int /*<<< orphan*/ * vtpci_msix_res; int /*<<< orphan*/ * vtpci_res; int /*<<< orphan*/ * vtpci_dev; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIY_MSI ; 
 int /*<<< orphan*/  PCIY_MSIX ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_ACK ; 
 int /*<<< orphan*/  VIRTIO_CONFIG_STATUS_FAILED ; 
 int /*<<< orphan*/  VTPCI_FLAG_NO_MSI ; 
 int /*<<< orphan*/  VTPCI_FLAG_NO_MSIX ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct vtpci_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtpci_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtpci_probe_and_attach_child (struct vtpci_softc*) ; 
 int /*<<< orphan*/  vtpci_reset (struct vtpci_softc*) ; 
 int /*<<< orphan*/  vtpci_set_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtpci_attach(device_t dev)
{
	struct vtpci_softc *sc;
	device_t child;
	int rid;

	sc = device_get_softc(dev);
	sc->vtpci_dev = dev;

	pci_enable_busmaster(dev);

	rid = PCIR_BAR(0);
	sc->vtpci_res = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid,
	    RF_ACTIVE);
	if (sc->vtpci_res == NULL) {
		device_printf(dev, "cannot map I/O space\n");
		return (ENXIO);
	}

	if (pci_find_cap(dev, PCIY_MSI, NULL) != 0)
		sc->vtpci_flags |= VTPCI_FLAG_NO_MSI;

	if (pci_find_cap(dev, PCIY_MSIX, NULL) == 0) {
		rid = PCIR_BAR(1);
		sc->vtpci_msix_res = bus_alloc_resource_any(dev,
		    SYS_RES_MEMORY, &rid, RF_ACTIVE);
	}

	if (sc->vtpci_msix_res == NULL)
		sc->vtpci_flags |= VTPCI_FLAG_NO_MSIX;

	vtpci_reset(sc);

	/* Tell the host we've noticed this device. */
	vtpci_set_status(dev, VIRTIO_CONFIG_STATUS_ACK);

	if ((child = device_add_child(dev, NULL, -1)) == NULL) {
		device_printf(dev, "cannot create child device\n");
		vtpci_set_status(dev, VIRTIO_CONFIG_STATUS_FAILED);
		vtpci_detach(dev);
		return (ENOMEM);
	}

	sc->vtpci_child_dev = child;
	vtpci_probe_and_attach_child(sc);

	return (0);
}