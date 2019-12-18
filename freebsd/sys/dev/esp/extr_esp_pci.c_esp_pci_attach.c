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
struct ncr53c9x_softc {int sc_id; int sc_cfg1; int sc_cfg2; int sc_cfg3; int sc_cfg4; int sc_features; int sc_freq; int sc_minsync; int sc_maxoffset; int sc_extended_geom; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_maxxfer; int /*<<< orphan*/  sc_cfg3_fscsi; int /*<<< orphan*/  sc_rev; int /*<<< orphan*/ * sc_glue; } ;
struct esp_pci_softc {int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_pdmat; int /*<<< orphan*/  sc_xferdmat; int /*<<< orphan*/  sc_xferdmam; int /*<<< orphan*/  sc_ih; int /*<<< orphan*/  sc_dev; struct ncr53c9x_softc sc_ncr53c9x; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int BUS_SPACE_UNRESTRICTED ; 
 int /*<<< orphan*/  DFLTPHYS ; 
 size_t ESP_PCI_RES_INTR ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int /*<<< orphan*/  MDL_SEG_SIZE ; 
 int NCRAMDCFG3_FCLK ; 
 int /*<<< orphan*/  NCRAMDCFG3_FSCSI ; 
 int NCRAMDCFG3_IDM ; 
 int NCRAMDCFG4_GE12NS ; 
 int NCRAMDCFG4_RADE ; 
 int NCRCFG1_PARENB ; 
 int NCRCFG2_FE ; 
 int NCRCFG2_SCSI2 ; 
 int NCR_F_DMASELECT ; 
 int NCR_F_FASTSCSI ; 
 int /*<<< orphan*/  NCR_LOCK_DESTROY (struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  NCR_LOCK_INIT (struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  NCR_VARIANT_AM53C974 ; 
 int PAGE_SIZE ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ncr53c9x_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * busdma_lock_mutex ; 
 struct esp_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  esp_pci_glue ; 
 int /*<<< orphan*/  esp_pci_res_spec ; 
 int ncr53c9x_attach (struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  ncr53c9x_intr ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
esp_pci_attach(device_t dev)
{
	struct esp_pci_softc *esc;
	struct ncr53c9x_softc *sc;
	int error;

	esc = device_get_softc(dev);
	sc = &esc->sc_ncr53c9x;

	NCR_LOCK_INIT(sc);

	esc->sc_dev = dev;
	sc->sc_glue = &esp_pci_glue;

	pci_enable_busmaster(dev);

	error = bus_alloc_resources(dev, esp_pci_res_spec, esc->sc_res);
	if (error != 0) {
		device_printf(dev, "failed to allocate resources\n");
		bus_release_resources(dev, esp_pci_res_spec, esc->sc_res);
		return (error);
	}

	error = bus_dma_tag_create(bus_get_dma_tag(dev), 1, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    BUS_SPACE_MAXSIZE_32BIT, BUS_SPACE_UNRESTRICTED,
	    BUS_SPACE_MAXSIZE_32BIT, 0, NULL, NULL, &esc->sc_pdmat);
	if (error != 0) {
		device_printf(dev, "cannot create parent DMA tag\n");
		goto fail_res;
	}

	/*
	 * XXX More of this should be in ncr53c9x_attach(), but
	 * XXX should we really poke around the chip that much in
	 * XXX the MI code?  Think about this more...
	 */

	/*
	 * Set up static configuration info.
	 *
	 * XXX we should read the configuration from the EEPROM.
	 */
	sc->sc_id = 7;
	sc->sc_cfg1 = sc->sc_id | NCRCFG1_PARENB;
	sc->sc_cfg2 = NCRCFG2_SCSI2 | NCRCFG2_FE;
	sc->sc_cfg3 = NCRAMDCFG3_IDM | NCRAMDCFG3_FCLK;
	sc->sc_cfg4 = NCRAMDCFG4_GE12NS | NCRAMDCFG4_RADE;
	sc->sc_rev = NCR_VARIANT_AM53C974;
	sc->sc_features = NCR_F_FASTSCSI | NCR_F_DMASELECT;
	sc->sc_cfg3_fscsi = NCRAMDCFG3_FSCSI;
	sc->sc_freq = 40; /* MHz */

	/*
	 * This is the value used to start sync negotiations
	 * Note that the NCR register "SYNCTP" is programmed
	 * in "clocks per byte", and has a minimum value of 4.
	 * The SCSI period used in negotiation is one-fourth
	 * of the time (in nanoseconds) needed to transfer one byte.
	 * Since the chip's clock is given in MHz, we have the following
	 * formula: 4 * period = (1000 / freq) * 4
	 */
	sc->sc_minsync = 1000 / sc->sc_freq;

	sc->sc_maxxfer = DFLTPHYS;	/* see below */
	sc->sc_maxoffset = 15;
	sc->sc_extended_geom = 1;

#define	MDL_SEG_SIZE	0x1000	/* 4kbyte per segment */

	/*
	 * Create the DMA tag and map for the data transfers.
	 *
	 * Note: given that bus_dma(9) only adheres to the requested alignment
	 * for the first segment (and that also only for bus_dmamem_alloc()ed
	 * DMA maps) we can't use the Memory Descriptor List.  However, also
	 * when not using the MDL, the maximum transfer size apparently is
	 * limited to 4k so we have to split transfers up, which plain sucks.
	 */
	error = bus_dma_tag_create(esc->sc_pdmat, PAGE_SIZE, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    MDL_SEG_SIZE, 1, MDL_SEG_SIZE, BUS_DMA_ALLOCNOW,
	    busdma_lock_mutex, &sc->sc_lock, &esc->sc_xferdmat);
	if (error != 0) {
		device_printf(dev, "cannot create transfer DMA tag\n");
		goto fail_pdmat;
	}
	error = bus_dmamap_create(esc->sc_xferdmat, 0, &esc->sc_xferdmam);
	if (error != 0) {
		device_printf(dev, "cannot create transfer DMA map\n");
		goto fail_xferdmat;
	}

	error = bus_setup_intr(dev, esc->sc_res[ESP_PCI_RES_INTR],
	    INTR_MPSAFE | INTR_TYPE_CAM, NULL, ncr53c9x_intr, sc,
	    &esc->sc_ih);
	if (error != 0) {
		device_printf(dev, "cannot set up interrupt\n");
		goto fail_xferdmam;
	}

	/* Do the common parts of attachment. */
	sc->sc_dev = esc->sc_dev;
	error = ncr53c9x_attach(sc);
	if (error != 0) {
		device_printf(esc->sc_dev, "ncr53c9x_attach failed\n");
		goto fail_intr;
	}

	return (0);

 fail_intr:
	 bus_teardown_intr(esc->sc_dev, esc->sc_res[ESP_PCI_RES_INTR],
	    esc->sc_ih);
 fail_xferdmam:
	bus_dmamap_destroy(esc->sc_xferdmat, esc->sc_xferdmam);
 fail_xferdmat:
	bus_dma_tag_destroy(esc->sc_xferdmat);
 fail_pdmat:
	bus_dma_tag_destroy(esc->sc_pdmat);
 fail_res:
	bus_release_resources(dev, esp_pci_res_spec, esc->sc_res);
	NCR_LOCK_DESTROY(sc);

	return (error);
}