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
typedef  int u_int32_t ;
struct aac_softc {int aac_hwif; int /*<<< orphan*/  flags; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/  aac_parent_dmat; int /*<<< orphan*/ * aac_regs_res1; void* aac_bhandle1; void* aac_btag1; void* aac_regs_rid1; int /*<<< orphan*/ * aac_regs_res0; void* aac_bhandle0; void* aac_btag0; void* aac_regs_rid0; int /*<<< orphan*/  aac_if; } ;
struct aac_ident {int hwif; int /*<<< orphan*/  quirks; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  AAC_HWIF_SRC 129 
#define  AAC_HWIF_SRCV 128 
 int AAC_HWIF_UNKNOWN ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_UNRESTRICTED ; 
 int ENOMEM ; 
 int ENXIO ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 char* HBA_FLAGS_DBG_INIT_B ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PCIM_CMD_BUSMASTEREN ; 
 void* PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct aac_ident* aac_find_ident (int /*<<< orphan*/ ) ; 
 int aacraid_attach (struct aac_softc*) ; 
 int /*<<< orphan*/  aacraid_free (struct aac_softc*) ; 
 int /*<<< orphan*/  aacraid_src_interface ; 
 int /*<<< orphan*/  aacraid_srcv_interface ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct aac_softc*,int) ; 
 struct aac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ *) ; 
 void* rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aacraid_pci_attach(device_t dev)
{
	struct aac_softc *sc;
	struct aac_ident *id;
	int error;
	u_int32_t command;

	fwprintf(NULL, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/*
	 * Initialise softc.
	 */
	sc = device_get_softc(dev);
	bzero(sc, sizeof(*sc));
	sc->aac_dev = dev;

	/* assume failure is 'not configured' */
	error = ENXIO;

	/* 
	 * Verify that the adapter is correctly set up in PCI space.
	 */
	pci_enable_busmaster(dev);
	command = pci_read_config(sc->aac_dev, PCIR_COMMAND, 2);
	if (!(command & PCIM_CMD_BUSMASTEREN)) {
		device_printf(sc->aac_dev, "can't enable bus-master feature\n");
		goto out;
	}

	/* 
	 * Detect the hardware interface version, set up the bus interface
	 * indirection.
	 */
	id = aac_find_ident(dev);
	sc->aac_hwif = id->hwif;
	switch(sc->aac_hwif) {
	case AAC_HWIF_SRC:
		fwprintf(sc, HBA_FLAGS_DBG_INIT_B, "set hardware up for PMC SRC");
		sc->aac_if = aacraid_src_interface;
		break;
	case AAC_HWIF_SRCV:
		fwprintf(sc, HBA_FLAGS_DBG_INIT_B, "set hardware up for PMC SRCv");
		sc->aac_if = aacraid_srcv_interface;
		break;
	default:
		sc->aac_hwif = AAC_HWIF_UNKNOWN;
		device_printf(sc->aac_dev, "unknown hardware type\n");
		error = ENXIO;
		goto out;
	}

	/* assume failure is 'out of memory' */
	error = ENOMEM;

	/*
	 * Allocate the PCI register window.
	 */
	sc->aac_regs_rid0 = PCIR_BAR(0);
	if ((sc->aac_regs_res0 = bus_alloc_resource_any(sc->aac_dev,
	    SYS_RES_MEMORY, &sc->aac_regs_rid0, RF_ACTIVE)) == NULL) {
		device_printf(sc->aac_dev,
		    "couldn't allocate register window 0\n");
		goto out;
	}
	sc->aac_btag0 = rman_get_bustag(sc->aac_regs_res0);
	sc->aac_bhandle0 = rman_get_bushandle(sc->aac_regs_res0);

	sc->aac_regs_rid1 = PCIR_BAR(2);
	if ((sc->aac_regs_res1 = bus_alloc_resource_any(sc->aac_dev,
	    SYS_RES_MEMORY, &sc->aac_regs_rid1, RF_ACTIVE)) == NULL) {
		device_printf(sc->aac_dev,
		    "couldn't allocate register window 1\n");
		goto out;
	}
	sc->aac_btag1 = rman_get_bustag(sc->aac_regs_res1);
	sc->aac_bhandle1 = rman_get_bushandle(sc->aac_regs_res1);

	/*
	 * Allocate the parent bus DMA tag appropriate for our PCI interface.
	 * 
	 * Note that some of these controllers are 64-bit capable.
	 */
	if (bus_dma_tag_create(bus_get_dma_tag(dev), 	/* parent */
			       PAGE_SIZE, 0,		/* algnmnt, boundary */
			       BUS_SPACE_MAXADDR,	/* lowaddr */
			       BUS_SPACE_MAXADDR, 	/* highaddr */
			       NULL, NULL, 		/* filter, filterarg */
			       BUS_SPACE_MAXSIZE_32BIT,	/* maxsize */
			       BUS_SPACE_UNRESTRICTED,	/* nsegments */
			       BUS_SPACE_MAXSIZE_32BIT,	/* maxsegsize */
			       0,			/* flags */
			       NULL, NULL,		/* No locking needed */
			       &sc->aac_parent_dmat)) {
		device_printf(sc->aac_dev, "can't allocate parent DMA tag\n");
		goto out;
	}

	/* Set up quirks */
	sc->flags = id->quirks;

	/*
	 * Do bus-independent initialisation.
	 */
	error = aacraid_attach(sc);

out:
	if (error)
		aacraid_free(sc);
	return(error);
}