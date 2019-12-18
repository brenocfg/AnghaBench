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
struct mpr_softc {int /*<<< orphan*/  mpr_parent_dmat; int /*<<< orphan*/ * mpr_regs_resource; int /*<<< orphan*/  mpr_bhandle; int /*<<< orphan*/  mpr_btag; int /*<<< orphan*/  mpr_regs_rid; int /*<<< orphan*/  mpr_flags; int /*<<< orphan*/  mpr_dev; } ;
struct mpr_ident {int device; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int ENOMEM ; 
 int ENXIO ; 
#define  MPI26_MFGPAGE_DEVID_CFG_SEC_SAS3816 133 
#define  MPI26_MFGPAGE_DEVID_CFG_SEC_SAS3916 132 
#define  MPI26_MFGPAGE_DEVID_INVALID0_SAS3816 131 
#define  MPI26_MFGPAGE_DEVID_INVALID0_SAS3916 130 
#define  MPI26_MFGPAGE_DEVID_INVALID1_SAS3816 129 
#define  MPI26_MFGPAGE_DEVID_INVALID1_SAS3916 128 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int PCI_MAXMAPS_0 ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct mpr_softc*,int) ; 
 struct mpr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mpr_attach (struct mpr_softc*) ; 
 struct mpr_ident* mpr_find_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpr_get_tunables (struct mpr_softc*) ; 
 int mpr_pci_alloc_interrupts (struct mpr_softc*) ; 
 int /*<<< orphan*/  mpr_pci_free (struct mpr_softc*) ; 
 int /*<<< orphan*/  mpr_printf (struct mpr_softc*,char*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mpr_pci_attach(device_t dev)
{
	struct mpr_softc *sc;
	struct mpr_ident *m;
	int error, i;

	sc = device_get_softc(dev);
	bzero(sc, sizeof(*sc));
	sc->mpr_dev = dev;
	m = mpr_find_ident(dev);
	sc->mpr_flags = m->flags;

	switch (m->device) {
	case MPI26_MFGPAGE_DEVID_INVALID0_SAS3816:
	case MPI26_MFGPAGE_DEVID_INVALID1_SAS3816:
	case MPI26_MFGPAGE_DEVID_INVALID0_SAS3916:
	case MPI26_MFGPAGE_DEVID_INVALID1_SAS3916:
		mpr_printf(sc, "HBA is in Non Secure mode\n");
		return (ENXIO);
	case MPI26_MFGPAGE_DEVID_CFG_SEC_SAS3816:
	case MPI26_MFGPAGE_DEVID_CFG_SEC_SAS3916:
		mpr_printf(sc, "HBA is in Configurable Secure mode\n");
		break;
	default:
		break;
	}

	mpr_get_tunables(sc);

	/* Twiddle basic PCI config bits for a sanity check */
	pci_enable_busmaster(dev);

	for (i = 0; i < PCI_MAXMAPS_0; i++) {
		sc->mpr_regs_rid = PCIR_BAR(i);

		if ((sc->mpr_regs_resource = bus_alloc_resource_any(dev,
		    SYS_RES_MEMORY, &sc->mpr_regs_rid, RF_ACTIVE)) != NULL)
			break;
	}

	if (sc->mpr_regs_resource == NULL) {
		mpr_printf(sc, "Cannot allocate PCI registers\n");
		return (ENXIO);
	}

	sc->mpr_btag = rman_get_bustag(sc->mpr_regs_resource);
	sc->mpr_bhandle = rman_get_bushandle(sc->mpr_regs_resource);

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
				&sc->mpr_parent_dmat)) {
		mpr_printf(sc, "Cannot allocate parent DMA tag\n");
		mpr_pci_free(sc);
		return (ENOMEM);
	}

	if (((error = mpr_pci_alloc_interrupts(sc)) != 0) ||
	    ((error = mpr_attach(sc)) != 0))
		mpr_pci_free(sc);

	return (error);
}