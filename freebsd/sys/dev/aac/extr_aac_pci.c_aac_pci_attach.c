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
typedef  int uint64_t ;
struct aac_softc {int aac_hwif; int flags; int /*<<< orphan*/  aac_parent_dmat; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/ * aac_irq; void* aac_bhandle0; void* aac_bhandle1; void* aac_btag0; void* aac_btag1; int /*<<< orphan*/ * aac_regs_res0; int /*<<< orphan*/ * aac_regs_res1; int /*<<< orphan*/ * aac_if; } ;
struct aac_ident {int hwif; int quirks; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int AAC_FLAGS_NOMSI ; 
#define  AAC_HWIF_I960RX 131 
#define  AAC_HWIF_NARK 130 
#define  AAC_HWIF_RKT 129 
#define  AAC_HWIF_STRONGARM 128 
 int AAC_HWIF_UNKNOWN ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int ENXIO ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 char* HBA_FLAGS_DBG_INIT_B ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int aac_attach (struct aac_softc*) ; 
 scalar_t__ aac_enable_msi ; 
 struct aac_ident* aac_find_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_free (struct aac_softc*) ; 
 int /*<<< orphan*/  aac_rkt_interface ; 
 int /*<<< orphan*/  aac_rx_interface ; 
 int /*<<< orphan*/  aac_sa_interface ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 struct aac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ *) ; 
 void* rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aac_pci_attach(device_t dev)
{
	struct aac_softc *sc;
	const struct aac_ident *id;
	int count, error, rid;

	fwprintf(NULL, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/*
	 * Initialise softc.
	 */
	sc = device_get_softc(dev);
	sc->aac_dev = dev;

	/* assume failure is 'not configured' */
	error = ENXIO;

	/*
	 * Verify that the adapter is correctly set up in PCI space.
	 */
	pci_enable_busmaster(dev);
	if (!(pci_read_config(dev, PCIR_COMMAND, 2) & PCIM_CMD_BUSMASTEREN)) {
		device_printf(dev, "can't enable bus-master feature\n");
		goto out;
	}

	/*
	 * Detect the hardware interface version, set up the bus interface
	 * indirection.
	 */
	id = aac_find_ident(dev);
	sc->aac_hwif = id->hwif;
	switch(sc->aac_hwif) {
	case AAC_HWIF_I960RX:
	case AAC_HWIF_NARK:
		fwprintf(sc, HBA_FLAGS_DBG_INIT_B,
		    "set hardware up for i960Rx/NARK");
		sc->aac_if = &aac_rx_interface;
		break;
	case AAC_HWIF_STRONGARM:
		fwprintf(sc, HBA_FLAGS_DBG_INIT_B,
		    "set hardware up for StrongARM");
		sc->aac_if = &aac_sa_interface;
		break;
	case AAC_HWIF_RKT:
		fwprintf(sc, HBA_FLAGS_DBG_INIT_B,
		    "set hardware up for Rocket/MIPS");
		sc->aac_if = &aac_rkt_interface;
		break;
	default:
		sc->aac_hwif = AAC_HWIF_UNKNOWN;
		device_printf(dev, "unknown hardware type\n");
		goto out;
	}

	/* Set up quirks */
	sc->flags = id->quirks;

	/*
	 * Allocate the PCI register window(s).
	 */
	rid = PCIR_BAR(0);
	if ((sc->aac_regs_res0 = bus_alloc_resource_any(dev,
	    SYS_RES_MEMORY, &rid, RF_ACTIVE)) == NULL) {
		device_printf(dev, "can't allocate register window 0\n");
		goto out;
	}
	sc->aac_btag0 = rman_get_bustag(sc->aac_regs_res0);
	sc->aac_bhandle0 = rman_get_bushandle(sc->aac_regs_res0);

	if (sc->aac_hwif == AAC_HWIF_NARK) {
		rid = PCIR_BAR(1);
		if ((sc->aac_regs_res1 = bus_alloc_resource_any(dev,
		    SYS_RES_MEMORY, &rid, RF_ACTIVE)) == NULL) {
			device_printf(dev,
			    "can't allocate register window 1\n");
			goto out;
		}
		sc->aac_btag1 = rman_get_bustag(sc->aac_regs_res1);
		sc->aac_bhandle1 = rman_get_bushandle(sc->aac_regs_res1);
	} else {
		sc->aac_regs_res1 = sc->aac_regs_res0;
		sc->aac_btag1 = sc->aac_btag0;
		sc->aac_bhandle1 = sc->aac_bhandle0;
	}

	/*
	 * Allocate the interrupt.
	 */
	rid = 0;
	if (aac_enable_msi != 0 && (sc->flags & AAC_FLAGS_NOMSI) == 0) {
		count = 1;
		if (pci_alloc_msi(dev, &count) == 0)
			rid = 1;
	}
	if ((sc->aac_irq = bus_alloc_resource_any(sc->aac_dev, SYS_RES_IRQ,
	    &rid, RF_ACTIVE | (rid != 0 ? 0 : RF_SHAREABLE))) == NULL) {
		device_printf(dev, "can't allocate interrupt\n");
		goto out;
	}

	/*
	 * Allocate the parent bus DMA tag appropriate for our PCI interface.
	 *
	 * Note that some of these controllers are 64-bit capable.
	 */
	if (bus_dma_tag_create(bus_get_dma_tag(dev),	/* parent */
			       PAGE_SIZE,		/* algnmnt */
			       ((bus_size_t)((uint64_t)1 << 32)), /* boundary*/
			       BUS_SPACE_MAXADDR,	/* lowaddr */
			       BUS_SPACE_MAXADDR, 	/* highaddr */
			       NULL, NULL, 		/* filter, filterarg */
			       BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
			       BUS_SPACE_UNRESTRICTED,	/* nsegments */
			       BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			       0,			/* flags */
			       NULL, NULL,		/* No locking needed */
			       &sc->aac_parent_dmat)) {
		device_printf(dev, "can't allocate parent DMA tag\n");
		goto out;
	}

	/*
	 * Do bus-independent initialisation.
	 */
	error = aac_attach(sc);

out:
	if (error)
		aac_free(sc);
	return(error);
}