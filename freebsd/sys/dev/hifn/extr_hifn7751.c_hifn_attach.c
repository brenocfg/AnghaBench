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
typedef  int u_int16_t ;
struct hifn_softc {int sc_flags; int sc_pllconfig; scalar_t__ sc_st0; scalar_t__ sc_sh0; scalar_t__ sc_st1; scalar_t__ sc_sh1; int sc_drammodel; int sc_ramsize; scalar_t__ sc_cid; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_bar0res; int /*<<< orphan*/ * sc_bar1res; int /*<<< orphan*/  sc_dmat; int /*<<< orphan*/  sc_dmamap; struct hifn_dma* sc_dma; int /*<<< orphan*/ * sc_irq; int /*<<< orphan*/  sc_intrhand; int /*<<< orphan*/  sc_tickto; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_dma_physaddr; void* sc_bar1_lastreg; void* sc_bar0_lastreg; } ;
struct hifn_session {int dummy; } ;
struct hifn_dma {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  struct hifn_dma* caddr_t ;
typedef  void* bus_size_t ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  CRYPTOCAP_F_HARDWARE ; 
 int /*<<< orphan*/  CRYPTO_3DES_CBC ; 
 int /*<<< orphan*/  CRYPTO_AES_CBC ; 
 int /*<<< orphan*/  CRYPTO_ARC4 ; 
 int /*<<< orphan*/  CRYPTO_DES_CBC ; 
 int /*<<< orphan*/  CRYPTO_MD5 ; 
 int /*<<< orphan*/  CRYPTO_MD5_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA1 ; 
 int /*<<< orphan*/  CRYPTO_SHA1_HMAC ; 
 int ENXIO ; 
 int /*<<< orphan*/  HIFN_0_PUCNFG ; 
 int /*<<< orphan*/  HIFN_0_PUSTAT ; 
 int /*<<< orphan*/  HIFN_1_DMA_CNFG ; 
 int /*<<< orphan*/  HIFN_1_REVID ; 
 int HIFN_BAR0 ; 
 int HIFN_BAR1 ; 
 int HIFN_DMACNFG_DMARESET ; 
 int HIFN_DMACNFG_MODE ; 
 int HIFN_DMACNFG_MSTRESET ; 
 int HIFN_HAS_AES ; 
 int HIFN_HAS_PUBLIC ; 
 int HIFN_HAS_RNG ; 
 int HIFN_IS_7811 ; 
 int HIFN_IS_7956 ; 
 int /*<<< orphan*/  HIFN_MAX_DMALEN ; 
 int /*<<< orphan*/  HIFN_MAX_SEGLEN ; 
 int HIFN_PLL_ND ; 
 int HIFN_PLL_REF_SEL ; 
 int HIFN_PUCNFG_CHIPID ; 
 int HIFN_PUSTAT_CHIPENA ; 
#define  HIFN_PUSTAT_ENA_1 129 
#define  HIFN_PUSTAT_ENA_2 128 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MAX_SCATTER ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ PCI_PRODUCT_HIFN_7811 ; 
 scalar_t__ PCI_PRODUCT_HIFN_7951 ; 
 scalar_t__ PCI_PRODUCT_HIFN_7955 ; 
 scalar_t__ PCI_PRODUCT_HIFN_7956 ; 
 scalar_t__ PCI_PRODUCT_NETSEC_7751 ; 
 scalar_t__ PCI_VENDOR_HIFN ; 
 scalar_t__ PCI_VENDOR_NETSEC ; 
 int READ_REG_0 (struct hifn_softc*,int /*<<< orphan*/ ) ; 
 int READ_REG_1 (struct hifn_softc*,int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WRITE_REG_0 (struct hifn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_REG_1 (struct hifn_softc*,int /*<<< orphan*/ ,int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hifn_dma*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,struct hifn_dma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct hifn_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct hifn_dma*,int) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hifn_softc*) ; 
 scalar_t__ crypto_get_driverid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_register (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct hifn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hifn_dmamap_cb ; 
 int /*<<< orphan*/  hifn_dramsize (struct hifn_softc*) ; 
 scalar_t__ hifn_enable_crypto (struct hifn_softc*) ; 
 int /*<<< orphan*/  hifn_getpllconfig (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hifn_init_dma (struct hifn_softc*) ; 
 int /*<<< orphan*/  hifn_init_pci_registers (struct hifn_softc*) ; 
 int /*<<< orphan*/  hifn_init_pubrng (struct hifn_softc*) ; 
 int /*<<< orphan*/  hifn_intr ; 
 int /*<<< orphan*/  hifn_partname (struct hifn_softc*) ; 
 scalar_t__ hifn_ramtype (struct hifn_softc*) ; 
 int /*<<< orphan*/  hifn_reset_board (struct hifn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hifn_reset_puc (struct hifn_softc*) ; 
 int /*<<< orphan*/  hifn_sessions (struct hifn_softc*) ; 
 int /*<<< orphan*/  hifn_set_retry (struct hifn_softc*) ; 
 int /*<<< orphan*/  hifn_sramsize (struct hifn_softc*) ; 
 int /*<<< orphan*/  hifn_tick ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_revid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ *) ; 
 void* rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
hifn_attach(device_t dev)
{
	struct hifn_softc *sc = device_get_softc(dev);
	caddr_t kva;
	int rseg, rid;
	char rbase;
	u_int16_t ena, rev;

	sc->sc_dev = dev;

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), "hifn driver", MTX_DEF);

	/* XXX handle power management */

	/*
	 * The 7951 and 795x have a random number generator and
	 * public key support; note this.
	 */
	if (pci_get_vendor(dev) == PCI_VENDOR_HIFN &&
	    (pci_get_device(dev) == PCI_PRODUCT_HIFN_7951 ||
	     pci_get_device(dev) == PCI_PRODUCT_HIFN_7955 ||
	     pci_get_device(dev) == PCI_PRODUCT_HIFN_7956))
		sc->sc_flags = HIFN_HAS_RNG | HIFN_HAS_PUBLIC;
	/*
	 * The 7811 has a random number generator and
	 * we also note it's identity 'cuz of some quirks.
	 */
	if (pci_get_vendor(dev) == PCI_VENDOR_HIFN &&
	    pci_get_device(dev) == PCI_PRODUCT_HIFN_7811)
		sc->sc_flags |= HIFN_IS_7811 | HIFN_HAS_RNG;

	/*
	 * The 795x parts support AES.
	 */
	if (pci_get_vendor(dev) == PCI_VENDOR_HIFN &&
	    (pci_get_device(dev) == PCI_PRODUCT_HIFN_7955 ||
	     pci_get_device(dev) == PCI_PRODUCT_HIFN_7956)) {
		sc->sc_flags |= HIFN_IS_7956 | HIFN_HAS_AES;
		/*
		 * Select PLL configuration.  This depends on the
		 * bus and board design and must be manually configured
		 * if the default setting is unacceptable.
		 */
		hifn_getpllconfig(dev, &sc->sc_pllconfig);
	}

	/*
	 * Setup PCI resources. Note that we record the bus
	 * tag and handle for each register mapping, this is
	 * used by the READ_REG_0, WRITE_REG_0, READ_REG_1,
	 * and WRITE_REG_1 macros throughout the driver.
	 */
	pci_enable_busmaster(dev);

	rid = HIFN_BAR0;
	sc->sc_bar0res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
			 			RF_ACTIVE);
	if (sc->sc_bar0res == NULL) {
		device_printf(dev, "cannot map bar%d register space\n", 0);
		goto fail_pci;
	}
	sc->sc_st0 = rman_get_bustag(sc->sc_bar0res);
	sc->sc_sh0 = rman_get_bushandle(sc->sc_bar0res);
	sc->sc_bar0_lastreg = (bus_size_t) -1;

	rid = HIFN_BAR1;
	sc->sc_bar1res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
						RF_ACTIVE);
	if (sc->sc_bar1res == NULL) {
		device_printf(dev, "cannot map bar%d register space\n", 1);
		goto fail_io0;
	}
	sc->sc_st1 = rman_get_bustag(sc->sc_bar1res);
	sc->sc_sh1 = rman_get_bushandle(sc->sc_bar1res);
	sc->sc_bar1_lastreg = (bus_size_t) -1;

	hifn_set_retry(sc);

	/*
	 * Setup the area where the Hifn DMA's descriptors
	 * and associated data structures.
	 */
	if (bus_dma_tag_create(bus_get_dma_tag(dev),	/* PCI parent */
			       1, 0,			/* alignment,boundary */
			       BUS_SPACE_MAXADDR_32BIT,	/* lowaddr */
			       BUS_SPACE_MAXADDR,	/* highaddr */
			       NULL, NULL,		/* filter, filterarg */
			       HIFN_MAX_DMALEN,		/* maxsize */
			       MAX_SCATTER,		/* nsegments */
			       HIFN_MAX_SEGLEN,		/* maxsegsize */
			       BUS_DMA_ALLOCNOW,	/* flags */
			       NULL,			/* lockfunc */
			       NULL,			/* lockarg */
			       &sc->sc_dmat)) {
		device_printf(dev, "cannot allocate DMA tag\n");
		goto fail_io1;
	}
	if (bus_dmamap_create(sc->sc_dmat, BUS_DMA_NOWAIT, &sc->sc_dmamap)) {
		device_printf(dev, "cannot create dma map\n");
		bus_dma_tag_destroy(sc->sc_dmat);
		goto fail_io1;
	}
	if (bus_dmamem_alloc(sc->sc_dmat, (void**) &kva, BUS_DMA_NOWAIT, &sc->sc_dmamap)) {
		device_printf(dev, "cannot alloc dma buffer\n");
		bus_dmamap_destroy(sc->sc_dmat, sc->sc_dmamap);
		bus_dma_tag_destroy(sc->sc_dmat);
		goto fail_io1;
	}
	if (bus_dmamap_load(sc->sc_dmat, sc->sc_dmamap, kva,
			     sizeof (*sc->sc_dma),
			     hifn_dmamap_cb, &sc->sc_dma_physaddr,
			     BUS_DMA_NOWAIT)) {
		device_printf(dev, "cannot load dma map\n");
		bus_dmamem_free(sc->sc_dmat, kva, sc->sc_dmamap);
		bus_dma_tag_destroy(sc->sc_dmat);
		goto fail_io1;
	}
	sc->sc_dma = (struct hifn_dma *)kva;
	bzero(sc->sc_dma, sizeof(*sc->sc_dma));

	KASSERT(sc->sc_st0 != 0, ("hifn_attach: null bar0 tag!"));
	KASSERT(sc->sc_sh0 != 0, ("hifn_attach: null bar0 handle!"));
	KASSERT(sc->sc_st1 != 0, ("hifn_attach: null bar1 tag!"));
	KASSERT(sc->sc_sh1 != 0, ("hifn_attach: null bar1 handle!"));

	/*
	 * Reset the board and do the ``secret handshake''
	 * to enable the crypto support.  Then complete the
	 * initialization procedure by setting up the interrupt
	 * and hooking in to the system crypto support so we'll
	 * get used for system services like the crypto device,
	 * IPsec, RNG device, etc.
	 */
	hifn_reset_board(sc, 0);

	if (hifn_enable_crypto(sc) != 0) {
		device_printf(dev, "crypto enabling failed\n");
		goto fail_mem;
	}
	hifn_reset_puc(sc);

	hifn_init_dma(sc);
	hifn_init_pci_registers(sc);

	/* XXX can't dynamically determine ram type for 795x; force dram */
	if (sc->sc_flags & HIFN_IS_7956)
		sc->sc_drammodel = 1;
	else if (hifn_ramtype(sc))
		goto fail_mem;

	if (sc->sc_drammodel == 0)
		hifn_sramsize(sc);
	else
		hifn_dramsize(sc);

	/*
	 * Workaround for NetSec 7751 rev A: half ram size because two
	 * of the address lines were left floating
	 */
	if (pci_get_vendor(dev) == PCI_VENDOR_NETSEC &&
	    pci_get_device(dev) == PCI_PRODUCT_NETSEC_7751 &&
	    pci_get_revid(dev) == 0x61)	/*XXX???*/
		sc->sc_ramsize >>= 1;

	/*
	 * Arrange the interrupt line.
	 */
	rid = 0;
	sc->sc_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
					    RF_SHAREABLE|RF_ACTIVE);
	if (sc->sc_irq == NULL) {
		device_printf(dev, "could not map interrupt\n");
		goto fail_mem;
	}
	/*
	 * NB: Network code assumes we are blocked with splimp()
	 *     so make sure the IRQ is marked appropriately.
	 */
	if (bus_setup_intr(dev, sc->sc_irq, INTR_TYPE_NET | INTR_MPSAFE,
			   NULL, hifn_intr, sc, &sc->sc_intrhand)) {
		device_printf(dev, "could not setup interrupt\n");
		goto fail_intr2;
	}

	hifn_sessions(sc);

	/*
	 * NB: Keep only the low 16 bits; this masks the chip id
	 *     from the 7951.
	 */
	rev = READ_REG_1(sc, HIFN_1_REVID) & 0xffff;

	rseg = sc->sc_ramsize / 1024;
	rbase = 'K';
	if (sc->sc_ramsize >= (1024 * 1024)) {
		rbase = 'M';
		rseg /= 1024;
	}
	device_printf(sc->sc_dev, "%s, rev %u, %d%cB %cram",
		hifn_partname(sc), rev,
		rseg, rbase, sc->sc_drammodel ? 'd' : 's');
	if (sc->sc_flags & HIFN_IS_7956)
		printf(", pll=0x%x<%s clk, %ux mult>",
			sc->sc_pllconfig,
			sc->sc_pllconfig & HIFN_PLL_REF_SEL ? "ext" : "pci",
			2 + 2*((sc->sc_pllconfig & HIFN_PLL_ND) >> 11));
	printf("\n");

	sc->sc_cid = crypto_get_driverid(dev, sizeof(struct hifn_session),
	    CRYPTOCAP_F_HARDWARE);
	if (sc->sc_cid < 0) {
		device_printf(dev, "could not get crypto driver id\n");
		goto fail_intr;
	}

	WRITE_REG_0(sc, HIFN_0_PUCNFG,
	    READ_REG_0(sc, HIFN_0_PUCNFG) | HIFN_PUCNFG_CHIPID);
	ena = READ_REG_0(sc, HIFN_0_PUSTAT) & HIFN_PUSTAT_CHIPENA;

	switch (ena) {
	case HIFN_PUSTAT_ENA_2:
		crypto_register(sc->sc_cid, CRYPTO_3DES_CBC, 0, 0);
		crypto_register(sc->sc_cid, CRYPTO_ARC4, 0, 0);
		if (sc->sc_flags & HIFN_HAS_AES)
			crypto_register(sc->sc_cid, CRYPTO_AES_CBC, 0, 0);
		/*FALLTHROUGH*/
	case HIFN_PUSTAT_ENA_1:
		crypto_register(sc->sc_cid, CRYPTO_MD5, 0, 0);
		crypto_register(sc->sc_cid, CRYPTO_SHA1, 0, 0);
		crypto_register(sc->sc_cid, CRYPTO_MD5_HMAC, 0, 0);
		crypto_register(sc->sc_cid, CRYPTO_SHA1_HMAC, 0, 0);
		crypto_register(sc->sc_cid, CRYPTO_DES_CBC, 0, 0);
		break;
	}

	bus_dmamap_sync(sc->sc_dmat, sc->sc_dmamap,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	if (sc->sc_flags & (HIFN_HAS_PUBLIC | HIFN_HAS_RNG))
		hifn_init_pubrng(sc);

	callout_init(&sc->sc_tickto, 1);
	callout_reset(&sc->sc_tickto, hz, hifn_tick, sc);

	return (0);

fail_intr:
	bus_teardown_intr(dev, sc->sc_irq, sc->sc_intrhand);
fail_intr2:
	/* XXX don't store rid */
	bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_irq);
fail_mem:
	bus_dmamap_unload(sc->sc_dmat, sc->sc_dmamap);
	bus_dmamem_free(sc->sc_dmat, sc->sc_dma, sc->sc_dmamap);
	bus_dma_tag_destroy(sc->sc_dmat);

	/* Turn off DMA polling */
	WRITE_REG_1(sc, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MSTRESET |
	    HIFN_DMACNFG_DMARESET | HIFN_DMACNFG_MODE);
fail_io1:
	bus_release_resource(dev, SYS_RES_MEMORY, HIFN_BAR1, sc->sc_bar1res);
fail_io0:
	bus_release_resource(dev, SYS_RES_MEMORY, HIFN_BAR0, sc->sc_bar0res);
fail_pci:
	mtx_destroy(&sc->sc_mtx);
	return (ENXIO);
}