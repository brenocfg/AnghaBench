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
struct mwl_softc {int sc_invalid; int /*<<< orphan*/  sc_dmat; void* sc_io1h; void* sc_io1t; void* sc_io0h; void* sc_io0t; int /*<<< orphan*/  sc_dev; } ;
struct mwl_pci_softc {int /*<<< orphan*/ * sc_sr0; int /*<<< orphan*/ * sc_sr1; int /*<<< orphan*/ * sc_irq; int /*<<< orphan*/  sc_ih; struct mwl_softc sc_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BS_BAR0 ; 
 int BS_BAR1 ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MWL_LOCK_DESTROY (struct mwl_softc*) ; 
 int /*<<< orphan*/  MWL_LOCK_INIT (struct mwl_softc*) ; 
 int /*<<< orphan*/  MWL_TXDESC ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mwl_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mwl_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mwl_attach (int /*<<< orphan*/ ,struct mwl_softc*) ; 
 int /*<<< orphan*/  mwl_intr ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ *) ; 
 void* rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mwl_pci_attach(device_t dev)
{
	struct mwl_pci_softc *psc = device_get_softc(dev);
	struct mwl_softc *sc = &psc->sc_sc;
	int rid, error = ENXIO;

	sc->sc_dev = dev;

	pci_enable_busmaster(dev);

	/* 
	 * Setup memory-mapping of PCI registers.
	 */
	rid = BS_BAR0;
	psc->sc_sr0 = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
					    RF_ACTIVE);
	if (psc->sc_sr0 == NULL) {
		device_printf(dev, "cannot map BAR0 register space\n");
		goto bad;
	}
	rid = BS_BAR1;
	psc->sc_sr1 = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
					    RF_ACTIVE);
	if (psc->sc_sr1 == NULL) {
		device_printf(dev, "cannot map BAR1 register space\n");
		goto bad1;
	}
	sc->sc_invalid = 1;

	/*
	 * Arrange interrupt line.
	 */
	rid = 0;
	psc->sc_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
					     RF_SHAREABLE|RF_ACTIVE);
	if (psc->sc_irq == NULL) {
		device_printf(dev, "could not map interrupt\n");
		goto bad2;
	}
	if (bus_setup_intr(dev, psc->sc_irq,
			   INTR_TYPE_NET | INTR_MPSAFE,
			   NULL, mwl_intr, sc, &psc->sc_ih)) {
		device_printf(dev, "could not establish interrupt\n");
		goto bad3;
	}

	/*
	 * Setup DMA descriptor area.
	 */
	if (bus_dma_tag_create(bus_get_dma_tag(dev),	/* parent */
			       1, 0,			/* alignment, bounds */
			       BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
			       BUS_SPACE_MAXADDR,	/* highaddr */
			       NULL, NULL,		/* filter, filterarg */
			       BUS_SPACE_MAXSIZE,	/* maxsize */
			       MWL_TXDESC,		/* nsegments */
			       BUS_SPACE_MAXSIZE,	/* maxsegsize */
			       0,			/* flags */
			       NULL,			/* lockfunc */
			       NULL,			/* lockarg */
			       &sc->sc_dmat)) {
		device_printf(dev, "cannot allocate DMA tag\n");
		goto bad4;
	}

	/*
	 * Finish off the attach.
	 */
	MWL_LOCK_INIT(sc);
	sc->sc_io0t = rman_get_bustag(psc->sc_sr0);
	sc->sc_io0h = rman_get_bushandle(psc->sc_sr0);
	sc->sc_io1t = rman_get_bustag(psc->sc_sr1);
	sc->sc_io1h = rman_get_bushandle(psc->sc_sr1);
	if (mwl_attach(pci_get_device(dev), sc) == 0)
		return (0);

	MWL_LOCK_DESTROY(sc);
	bus_dma_tag_destroy(sc->sc_dmat);
bad4:
	bus_teardown_intr(dev, psc->sc_irq, psc->sc_ih);
bad3:
	bus_release_resource(dev, SYS_RES_IRQ, 0, psc->sc_irq);
bad2:
	bus_release_resource(dev, SYS_RES_MEMORY, BS_BAR1, psc->sc_sr1);
bad1:
	bus_release_resource(dev, SYS_RES_MEMORY, BS_BAR0, psc->sc_sr0);
bad:
	return (error);
}