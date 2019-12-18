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
struct bwi_softc {int sc_invalid; int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_irq_handle; int /*<<< orphan*/  sc_pci_subdid; int /*<<< orphan*/  sc_pci_subvid; int /*<<< orphan*/  sc_pci_revid; int /*<<< orphan*/  sc_pci_did; scalar_t__ sc_irq_rid; int /*<<< orphan*/  sc_mem_bh; int /*<<< orphan*/  sc_mem_bt; scalar_t__ sc_mem_rid; int /*<<< orphan*/  sc_dev; } ;
struct bwi_pci_softc {struct bwi_softc sc_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BS_BAR ; 
 scalar_t__ BWI_PCIR_BAR ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bwi_softc*,int /*<<< orphan*/ *) ; 
 int bwi_attach (struct bwi_softc*) ; 
 int /*<<< orphan*/  bwi_intr ; 
 struct bwi_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_revid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subvendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bwi_pci_attach(device_t dev)
{
	struct bwi_pci_softc *psc = device_get_softc(dev);
	struct bwi_softc *sc = &psc->sc_sc;
	int error = ENXIO;

	sc->sc_dev = dev;

	/*
	 * Enable bus mastering.
	 */
	pci_enable_busmaster(dev);

	/* 
	 * Setup memory-mapping of PCI registers.
	 */
	sc->sc_mem_rid = BWI_PCIR_BAR;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
		&sc->sc_mem_rid, RF_ACTIVE);
	if (sc->sc_mem_res == NULL) {
		device_printf(dev, "cannot map register space\n");
		goto bad;
	}
	sc->sc_mem_bt = rman_get_bustag(sc->sc_mem_res);
	sc->sc_mem_bh = rman_get_bushandle(sc->sc_mem_res);
	/*
	 * Mark device invalid so any interrupts (shared or otherwise)
	 * that arrive before the card is setup are discarded.
	 */
	sc->sc_invalid = 1;

	/*
	 * Arrange interrupt line.
	 */
	sc->sc_irq_rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
						&sc->sc_irq_rid,
						RF_SHAREABLE|RF_ACTIVE);
	if (sc->sc_irq_res == NULL) {
		device_printf(dev, "could not map interrupt\n");
		goto bad1;
	}

	/* Get more PCI information */
	sc->sc_pci_did = pci_get_device(dev);
	sc->sc_pci_revid = pci_get_revid(dev);
	sc->sc_pci_subvid = pci_get_subvendor(dev);
	sc->sc_pci_subdid = pci_get_subdevice(dev);

	if ((error = bwi_attach(sc)) != 0)
		goto bad2;

	if (bus_setup_intr(dev, sc->sc_irq_res,
			   INTR_TYPE_NET | INTR_MPSAFE,
			   NULL, bwi_intr, sc, &sc->sc_irq_handle)) {
		device_printf(dev, "could not establish interrupt\n");
		goto bad2;
	}
	return (0);

bad2:
	bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_irq_res);
bad1:
	bus_release_resource(dev, SYS_RES_MEMORY, BS_BAR, sc->sc_mem_res);
bad:
	return (error);
}