#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct sbni_softc {TYPE_1__* slave_sc; scalar_t__ io_res; int /*<<< orphan*/  io_rid; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int io_off; scalar_t__ io_res; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 scalar_t__ SBNI_PCI_DEVICE ; 
 scalar_t__ SBNI_PCI_VENDOR ; 
 int SBNI_PORTS ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 scalar_t__ bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sbni_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_subdevice (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 scalar_t__ sbni_probe (struct sbni_softc*) ; 
 int /*<<< orphan*/  sbni_release_resources (struct sbni_softc*) ; 

__attribute__((used)) static int
sbni_pci_probe(device_t dev)
{
	struct sbni_softc  *sc;
	u_int32_t  ports;
 
	ports = SBNI_PORTS;
	if (pci_get_vendor(dev) != SBNI_PCI_VENDOR ||
	    pci_get_device(dev) != SBNI_PCI_DEVICE)
		return (ENXIO);

	sc = device_get_softc(dev);
	if (pci_get_subdevice(dev) == 2) {
		ports <<= 1;
		sc->slave_sc = malloc(sizeof(struct sbni_softc),
				      M_DEVBUF, M_NOWAIT | M_ZERO);
		if (!sc->slave_sc)
			return (ENOMEM);
		device_set_desc(dev, "Granch SBNI12/PCI Dual adapter");
	} else
		device_set_desc(dev, "Granch SBNI12/PCI adapter");

	sc->io_rid = PCIR_BAR(0);
 	sc->io_res = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
					    &sc->io_rid, RF_ACTIVE);
	if (!sc->io_res) {
		device_printf(dev, "cannot allocate io ports!\n");
		if (sc->slave_sc)
			free(sc->slave_sc, M_DEVBUF);
		return (ENOENT);
	}

	if (sc->slave_sc) {
		sc->slave_sc->io_res = sc->io_res;
		sc->slave_sc->io_off = 4;
	}
	if (sbni_probe(sc) != 0) {
		sbni_release_resources(sc);
		if (sc->slave_sc)
			free(sc->slave_sc, M_DEVBUF);
		return (ENXIO);
	}

	return (0);
}