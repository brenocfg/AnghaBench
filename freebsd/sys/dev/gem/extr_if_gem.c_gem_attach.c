#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_hdrlen; int if_capabilities; int if_capenable; int /*<<< orphan*/  if_hwassist; TYPE_2__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; struct gem_softc* if_softc; } ;
struct gem_txsoft {int /*<<< orphan*/ * txs_dmamap; scalar_t__ txs_ndescs; int /*<<< orphan*/ * txs_mbuf; } ;
struct gem_softc {int sc_flags; scalar_t__ sc_cddma; int sc_variant; int sc_rxfifosize; int /*<<< orphan*/  sc_pdmatag; int /*<<< orphan*/  sc_rdmatag; int /*<<< orphan*/  sc_tdmatag; int /*<<< orphan*/  sc_cdmatag; int /*<<< orphan*/  sc_cddmamap; int /*<<< orphan*/  sc_control_data; struct gem_txsoft* sc_txsoft; TYPE_1__* sc_rxsoft; int /*<<< orphan*/  sc_csum_features; int /*<<< orphan*/  sc_enaddr; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_miibus; int /*<<< orphan*/  sc_mii; int /*<<< orphan*/  sc_txfreeq; int /*<<< orphan*/  sc_txdirtyq; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_rx_ch; int /*<<< orphan*/  sc_tick_ch; struct ifnet* sc_ifp; } ;
struct gem_control_data {int dummy; } ;
struct ether_vlan_header {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * rxs_dmamap; int /*<<< orphan*/ * rxs_mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int BUS_SPACE_MAXSIZE_32BIT ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENXIO ; 
#define  GEM_APPLE_GMAC 130 
#define  GEM_APPLE_K2_GMAC 129 
 int /*<<< orphan*/  GEM_BANK1_BARRIER (struct gem_softc*,int /*<<< orphan*/ ,int,int) ; 
 int GEM_BANK1_READ_4 (struct gem_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BANK1_WRITE_4 (struct gem_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GEM_CSUM_FEATURES ; 
 scalar_t__ GEM_IS_APPLE (struct gem_softc*) ; 
 int /*<<< orphan*/  GEM_MIF_CONFIG ; 
 int GEM_MIF_CONFIG_MDI0 ; 
 int GEM_MIF_CONFIG_MDI1 ; 
 int GEM_MIF_CONFIG_PHY_SEL ; 
 int /*<<< orphan*/  GEM_MII_CONFIG ; 
 int GEM_MII_CONFIG_ENABLE ; 
 int GEM_MII_DATAPATH_MII ; 
 int /*<<< orphan*/  GEM_MII_DATAPATH_MODE ; 
 int GEM_MII_DATAPATH_SERDES ; 
 int /*<<< orphan*/  GEM_MII_SLINK_CONTROL ; 
 int GEM_MII_SLINK_EN_SYNC_D ; 
 int GEM_MII_SLINK_LOOPBACK ; 
 int GEM_NRXDESC ; 
 int GEM_NTXSEGS ; 
 int GEM_PHYAD_EXTERNAL ; 
 int GEM_PHYAD_INTERNAL ; 
 int /*<<< orphan*/  GEM_RX_FIFO_SIZE ; 
 int GEM_SERDES ; 
#define  GEM_SUN_ERI 128 
 int GEM_SUN_GEM ; 
 int GEM_TXQUEUELEN ; 
 int /*<<< orphan*/  GEM_TX_FIFO_SIZE ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_2__*,int) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_2__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  MIIF_DOPAUSE ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int MII_PHY_ANY ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct gem_txsoft*,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct gem_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gem_cddma_callback ; 
 int /*<<< orphan*/  gem_init ; 
 int /*<<< orphan*/  gem_ioctl ; 
 int /*<<< orphan*/  gem_mediachange ; 
 int /*<<< orphan*/  gem_mediastatus ; 
 int /*<<< orphan*/  gem_mifinit (struct gem_softc*) ; 
 int /*<<< orphan*/  gem_reset (struct gem_softc*) ; 
 int /*<<< orphan*/  gem_start ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txs_q ; 

int
gem_attach(struct gem_softc *sc)
{
	struct gem_txsoft *txs;
	struct ifnet *ifp;
	int error, i, phy;
	uint32_t v;

	if (bootverbose)
		device_printf(sc->sc_dev, "flags=0x%x\n", sc->sc_flags);

	/* Set up ifnet structure. */
	ifp = sc->sc_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL)
		return (ENOSPC);
	sc->sc_csum_features = GEM_CSUM_FEATURES;
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(sc->sc_dev),
	    device_get_unit(sc->sc_dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_start = gem_start;
	ifp->if_ioctl = gem_ioctl;
	ifp->if_init = gem_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, GEM_TXQUEUELEN);
	ifp->if_snd.ifq_drv_maxlen = GEM_TXQUEUELEN;
	IFQ_SET_READY(&ifp->if_snd);

	callout_init_mtx(&sc->sc_tick_ch, &sc->sc_mtx, 0);
#ifdef GEM_RINT_TIMEOUT
	callout_init_mtx(&sc->sc_rx_ch, &sc->sc_mtx, 0);
#endif

	/* Make sure the chip is stopped. */
	gem_reset(sc);

	error = bus_dma_tag_create(bus_get_dma_tag(sc->sc_dev), 1, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    BUS_SPACE_MAXSIZE_32BIT, 0, BUS_SPACE_MAXSIZE_32BIT, 0, NULL,
	    NULL, &sc->sc_pdmatag);
	if (error != 0)
		goto fail_ifnet;

	error = bus_dma_tag_create(sc->sc_pdmatag, 1, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL, MCLBYTES,
	    1, MCLBYTES, BUS_DMA_ALLOCNOW, NULL, NULL, &sc->sc_rdmatag);
	if (error != 0)
		goto fail_ptag;

	error = bus_dma_tag_create(sc->sc_pdmatag, 1, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    MCLBYTES * GEM_NTXSEGS, GEM_NTXSEGS, MCLBYTES,
	    BUS_DMA_ALLOCNOW, NULL, NULL, &sc->sc_tdmatag);
	if (error != 0)
		goto fail_rtag;

	error = bus_dma_tag_create(sc->sc_pdmatag, PAGE_SIZE, 0,
	    BUS_SPACE_MAXADDR, BUS_SPACE_MAXADDR, NULL, NULL,
	    sizeof(struct gem_control_data), 1,
	    sizeof(struct gem_control_data), 0,
	    NULL, NULL, &sc->sc_cdmatag);
	if (error != 0)
		goto fail_ttag;

	/*
	 * Allocate the control data structures, create and load the
	 * DMA map for it.
	 */
	if ((error = bus_dmamem_alloc(sc->sc_cdmatag,
	    (void **)&sc->sc_control_data,
	    BUS_DMA_WAITOK | BUS_DMA_COHERENT | BUS_DMA_ZERO,
	    &sc->sc_cddmamap)) != 0) {
		device_printf(sc->sc_dev,
		    "unable to allocate control data, error = %d\n", error);
		goto fail_ctag;
	}

	sc->sc_cddma = 0;
	if ((error = bus_dmamap_load(sc->sc_cdmatag, sc->sc_cddmamap,
	    sc->sc_control_data, sizeof(struct gem_control_data),
	    gem_cddma_callback, sc, 0)) != 0 || sc->sc_cddma == 0) {
		device_printf(sc->sc_dev,
		    "unable to load control data DMA map, error = %d\n",
		    error);
		goto fail_cmem;
	}

	/*
	 * Initialize the transmit job descriptors.
	 */
	STAILQ_INIT(&sc->sc_txfreeq);
	STAILQ_INIT(&sc->sc_txdirtyq);

	/*
	 * Create the transmit buffer DMA maps.
	 */
	error = ENOMEM;
	for (i = 0; i < GEM_TXQUEUELEN; i++) {
		txs = &sc->sc_txsoft[i];
		txs->txs_mbuf = NULL;
		txs->txs_ndescs = 0;
		if ((error = bus_dmamap_create(sc->sc_tdmatag, 0,
		    &txs->txs_dmamap)) != 0) {
			device_printf(sc->sc_dev,
			    "unable to create TX DMA map %d, error = %d\n",
			    i, error);
			goto fail_txd;
		}
		STAILQ_INSERT_TAIL(&sc->sc_txfreeq, txs, txs_q);
	}

	/*
	 * Create the receive buffer DMA maps.
	 */
	for (i = 0; i < GEM_NRXDESC; i++) {
		if ((error = bus_dmamap_create(sc->sc_rdmatag, 0,
		    &sc->sc_rxsoft[i].rxs_dmamap)) != 0) {
			device_printf(sc->sc_dev,
			    "unable to create RX DMA map %d, error = %d\n",
			    i, error);
			goto fail_rxd;
		}
		sc->sc_rxsoft[i].rxs_mbuf = NULL;
	}

	/* Bypass probing PHYs if we already know for sure to use a SERDES. */
	if ((sc->sc_flags & GEM_SERDES) != 0)
		goto serdes;

	/* Bad things will happen when touching this register on ERI. */
	if (sc->sc_variant != GEM_SUN_ERI) {
		GEM_BANK1_WRITE_4(sc, GEM_MII_DATAPATH_MODE,
		    GEM_MII_DATAPATH_MII);
		GEM_BANK1_BARRIER(sc, GEM_MII_DATAPATH_MODE, 4,
		    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	}

	gem_mifinit(sc);

	/*
	 * Look for an external PHY.
	 */
	error = ENXIO;
	v = GEM_BANK1_READ_4(sc, GEM_MIF_CONFIG);
	if ((v & GEM_MIF_CONFIG_MDI1) != 0) {
		v |= GEM_MIF_CONFIG_PHY_SEL;
		GEM_BANK1_WRITE_4(sc, GEM_MIF_CONFIG, v);
		GEM_BANK1_BARRIER(sc, GEM_MIF_CONFIG, 4,
		    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
		switch (sc->sc_variant) {
		case GEM_SUN_ERI:
			phy = GEM_PHYAD_EXTERNAL;
			break;
		default:
			phy = MII_PHY_ANY;
			break;
		}
		error = mii_attach(sc->sc_dev, &sc->sc_miibus, ifp,
		    gem_mediachange, gem_mediastatus, BMSR_DEFCAPMASK, phy,
		    MII_OFFSET_ANY, MIIF_DOPAUSE);
	}

	/*
	 * Fall back on an internal PHY if no external PHY was found.
	 * Note that with Apple (K2) GMACs GEM_MIF_CONFIG_MDI0 can't be
	 * trusted when the firmware has powered down the chip.
	 */
	if (error != 0 &&
	    ((v & GEM_MIF_CONFIG_MDI0) != 0 || GEM_IS_APPLE(sc))) {
		v &= ~GEM_MIF_CONFIG_PHY_SEL;
		GEM_BANK1_WRITE_4(sc, GEM_MIF_CONFIG, v);
		GEM_BANK1_BARRIER(sc, GEM_MIF_CONFIG, 4,
		    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
		switch (sc->sc_variant) {
		case GEM_SUN_ERI:
		case GEM_APPLE_K2_GMAC:
			phy = GEM_PHYAD_INTERNAL;
			break;
		case GEM_APPLE_GMAC:
			phy = GEM_PHYAD_EXTERNAL;
			break;
		default:
			phy = MII_PHY_ANY;
			break;
		}
		error = mii_attach(sc->sc_dev, &sc->sc_miibus, ifp,
		    gem_mediachange, gem_mediastatus, BMSR_DEFCAPMASK, phy,
		    MII_OFFSET_ANY, MIIF_DOPAUSE);
	}

	/*
	 * Try the external PCS SERDES if we didn't find any PHYs.
	 */
	if (error != 0 && sc->sc_variant == GEM_SUN_GEM) {
 serdes:
		GEM_BANK1_WRITE_4(sc, GEM_MII_DATAPATH_MODE,
		    GEM_MII_DATAPATH_SERDES);
		GEM_BANK1_BARRIER(sc, GEM_MII_DATAPATH_MODE, 4,
		    BUS_SPACE_BARRIER_WRITE);
		GEM_BANK1_WRITE_4(sc, GEM_MII_SLINK_CONTROL,
		    GEM_MII_SLINK_LOOPBACK | GEM_MII_SLINK_EN_SYNC_D);
		GEM_BANK1_BARRIER(sc, GEM_MII_SLINK_CONTROL, 4,
		    BUS_SPACE_BARRIER_WRITE);
		GEM_BANK1_WRITE_4(sc, GEM_MII_CONFIG, GEM_MII_CONFIG_ENABLE);
		GEM_BANK1_BARRIER(sc, GEM_MII_CONFIG, 4,
		    BUS_SPACE_BARRIER_WRITE);
		sc->sc_flags |= GEM_SERDES;
		error = mii_attach(sc->sc_dev, &sc->sc_miibus, ifp,
		    gem_mediachange, gem_mediastatus, BMSR_DEFCAPMASK,
		    GEM_PHYAD_EXTERNAL, MII_OFFSET_ANY, MIIF_DOPAUSE);
	}
	if (error != 0) {
		device_printf(sc->sc_dev, "attaching PHYs failed\n");
		goto fail_rxd;
	}
	sc->sc_mii = device_get_softc(sc->sc_miibus);

	/*
	 * From this point forward, the attachment cannot fail.  A failure
	 * before this point releases all resources that may have been
	 * allocated.
	 */

	/* Get RX FIFO size. */
	sc->sc_rxfifosize = 64 *
	    GEM_BANK1_READ_4(sc, GEM_RX_FIFO_SIZE);

	/* Get TX FIFO size. */
	v = GEM_BANK1_READ_4(sc, GEM_TX_FIFO_SIZE);
	device_printf(sc->sc_dev, "%ukB RX FIFO, %ukB TX FIFO\n",
	    sc->sc_rxfifosize / 1024, v / 16);

	/* Attach the interface. */
	ether_ifattach(ifp, sc->sc_enaddr);

	/*
	 * Tell the upper layer(s) we support long frames/checksum offloads.
	 */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);
	ifp->if_capabilities |= IFCAP_VLAN_MTU | IFCAP_HWCSUM;
	ifp->if_hwassist |= sc->sc_csum_features;
	ifp->if_capenable |= IFCAP_VLAN_MTU | IFCAP_HWCSUM;

	return (0);

	/*
	 * Free any resources we've allocated during the failed attach
	 * attempt.  Do this in reverse order and fall through.
	 */
 fail_rxd:
	for (i = 0; i < GEM_NRXDESC; i++)
		if (sc->sc_rxsoft[i].rxs_dmamap != NULL)
			bus_dmamap_destroy(sc->sc_rdmatag,
			    sc->sc_rxsoft[i].rxs_dmamap);
 fail_txd:
	for (i = 0; i < GEM_TXQUEUELEN; i++)
		if (sc->sc_txsoft[i].txs_dmamap != NULL)
			bus_dmamap_destroy(sc->sc_tdmatag,
			    sc->sc_txsoft[i].txs_dmamap);
	bus_dmamap_unload(sc->sc_cdmatag, sc->sc_cddmamap);
 fail_cmem:
	bus_dmamem_free(sc->sc_cdmatag, sc->sc_control_data,
	    sc->sc_cddmamap);
 fail_ctag:
	bus_dma_tag_destroy(sc->sc_cdmatag);
 fail_ttag:
	bus_dma_tag_destroy(sc->sc_tdmatag);
 fail_rtag:
	bus_dma_tag_destroy(sc->sc_rdmatag);
 fail_ptag:
	bus_dma_tag_destroy(sc->sc_pdmatag);
 fail_ifnet:
	if_free(ifp);
	return (error);
}