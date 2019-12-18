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
struct mps_softc {int /*<<< orphan*/  mps_parent_dmat; int /*<<< orphan*/ * mps_regs_resource; int /*<<< orphan*/  mps_bhandle; int /*<<< orphan*/  mps_btag; int /*<<< orphan*/  mps_regs_rid; int /*<<< orphan*/  mps_flags; int /*<<< orphan*/  mps_dev; } ;
struct mps_ident {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct mps_softc*,int) ; 
 struct mps_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mps_attach (struct mps_softc*) ; 
 struct mps_ident* mps_find_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_get_tunables (struct mps_softc*) ; 
 int mps_pci_alloc_interrupts (struct mps_softc*) ; 
 int /*<<< orphan*/  mps_pci_free (struct mps_softc*) ; 
 int /*<<< orphan*/  mps_printf (struct mps_softc*,char*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mps_pci_attach(device_t dev)
{
	struct mps_softc *sc;
	struct mps_ident *m;
	int error;

	sc = device_get_softc(dev);
	bzero(sc, sizeof(*sc));
	sc->mps_dev = dev;
	m = mps_find_ident(dev);
	sc->mps_flags = m->flags;

	mps_get_tunables(sc);

	/* Twiddle basic PCI config bits for a sanity check */
	pci_enable_busmaster(dev);

	/* Allocate the System Interface Register Set */
	sc->mps_regs_rid = PCIR_BAR(1);
	if ((sc->mps_regs_resource = bus_alloc_resource_any(dev,
	    SYS_RES_MEMORY, &sc->mps_regs_rid, RF_ACTIVE)) == NULL) {
		mps_printf(sc, "Cannot allocate PCI registers\n");
		return (ENXIO);
	}
	sc->mps_btag = rman_get_bustag(sc->mps_regs_resource);
	sc->mps_bhandle = rman_get_bushandle(sc->mps_regs_resource);

	/* Allocate the parent DMA tag */
	if (bus_dma_tag_create( bus_get_dma_tag(dev),	/* parent */
				1, 0,			/* algnmnt, boundary */
				BUS_SPACE_MAXADDR,	/* lowaddr */
				BUS_SPACE_MAXADDR,	/* highaddr */
				NULL, NULL,		/* filter, filterarg */
				BUS_SPACE_MAXSIZE_32BIT,/* maxsize */
				BUS_SPACE_UNRESTRICTED,	/* nsegments */
				BUS_SPACE_MAXSIZE_32BIT,/* maxsegsize */
				0,			/* flags */
				NULL, NULL,		/* lockfunc, lockarg */
				&sc->mps_parent_dmat)) {
		mps_printf(sc, "Cannot allocate parent DMA tag\n");
		mps_pci_free(sc);
		return (ENOMEM);
	}

	if (((error = mps_pci_alloc_interrupts(sc)) != 0) ||
	    ((error = mps_attach(sc)) != 0))
		mps_pci_free(sc);

	return (error);
}