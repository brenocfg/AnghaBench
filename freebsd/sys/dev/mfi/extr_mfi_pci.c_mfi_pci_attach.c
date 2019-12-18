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
struct mfi_softc {int mfi_flags; int mfi_regs_rid; int mfi_irq_rid; int /*<<< orphan*/  mfi_dev; int /*<<< orphan*/ * mfi_irq; int /*<<< orphan*/  mfi_parent_dmat; int /*<<< orphan*/ * mfi_regs_resource; int /*<<< orphan*/  mfi_bhandle; int /*<<< orphan*/  mfi_btag; } ;
struct mfi_ident {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int MFI_FLAGS_1064R ; 
 int MFI_FLAGS_1078 ; 
 int MFI_FLAGS_GEN2 ; 
 int MFI_FLAGS_SKINNY ; 
 int MFI_FLAGS_TBOLT ; 
 void* PCIR_BAR (int) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct mfi_softc*,int) ; 
 struct mfi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mfi_attach (struct mfi_softc*) ; 
 struct mfi_ident* mfi_find_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_free (struct mfi_softc*) ; 
 scalar_t__ mfi_msi ; 
 int /*<<< orphan*/  mfi_pci_free (struct mfi_softc*) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mfi_pci_attach(device_t dev)
{
	struct mfi_softc *sc;
	struct mfi_ident *m;
	int count, error;

	sc = device_get_softc(dev);
	bzero(sc, sizeof(*sc));
	sc->mfi_dev = dev;
	m = mfi_find_ident(dev);
	sc->mfi_flags = m->flags;

	/* Ensure busmastering is enabled */
	pci_enable_busmaster(dev);

	/* Allocate PCI registers */
	if ((sc->mfi_flags & MFI_FLAGS_1064R) ||
	    (sc->mfi_flags & MFI_FLAGS_1078)) {
		/* 1068/1078: Memory mapped BAR is at offset 0x10 */
		sc->mfi_regs_rid = PCIR_BAR(0);
	}
	else if ((sc->mfi_flags & MFI_FLAGS_GEN2) ||
		 (sc->mfi_flags & MFI_FLAGS_SKINNY) ||
		(sc->mfi_flags & MFI_FLAGS_TBOLT)) { 
		/* Gen2/Skinny: Memory mapped BAR is at offset 0x14 */
		sc->mfi_regs_rid = PCIR_BAR(1);
	}
	if ((sc->mfi_regs_resource = bus_alloc_resource_any(sc->mfi_dev,
	    SYS_RES_MEMORY, &sc->mfi_regs_rid, RF_ACTIVE)) == NULL) {
		device_printf(dev, "Cannot allocate PCI registers\n");
		return (ENXIO);
	}
	sc->mfi_btag = rman_get_bustag(sc->mfi_regs_resource);
	sc->mfi_bhandle = rman_get_bushandle(sc->mfi_regs_resource);

	error = ENOMEM;

	/* Allocate parent DMA tag */
	if (bus_dma_tag_create(	bus_get_dma_tag(dev),	/* PCI parent */
				1, 0,			/* algnmnt, boundary */
				BUS_SPACE_MAXADDR,	/* lowaddr */
				BUS_SPACE_MAXADDR,	/* highaddr */
				NULL, NULL,		/* filter, filterarg */
				BUS_SPACE_MAXSIZE_32BIT,/* maxsize */
				BUS_SPACE_UNRESTRICTED,	/* nsegments */
				BUS_SPACE_MAXSIZE_32BIT,/* maxsegsize */
				0,			/* flags */
				NULL, NULL,		/* lockfunc, lockarg */
				&sc->mfi_parent_dmat)) {
		device_printf(dev, "Cannot allocate parent DMA tag\n");
		goto out;
	}

	/* Allocate IRQ resource. */
	sc->mfi_irq_rid = 0;
	count = 1;
	if (mfi_msi && pci_alloc_msi(sc->mfi_dev, &count) == 0) {
		device_printf(sc->mfi_dev, "Using MSI\n");
		sc->mfi_irq_rid = 1;
	}
	if ((sc->mfi_irq = bus_alloc_resource_any(sc->mfi_dev, SYS_RES_IRQ,
	    &sc->mfi_irq_rid, RF_SHAREABLE | RF_ACTIVE)) == NULL) {
		device_printf(sc->mfi_dev, "Cannot allocate interrupt\n");
		error = EINVAL;
		goto out;
	}

	error = mfi_attach(sc);
out:
	if (error) {
		mfi_free(sc);
		mfi_pci_free(sc);
	}

	return (error);
}