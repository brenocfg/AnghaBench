#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_hdrlen; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_qflush; int /*<<< orphan*/  if_transmit; int /*<<< orphan*/  if_ioctl; struct atse_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
struct atse_softc {int atse_phy_addr; int /*<<< orphan*/ * xchan_rx; int /*<<< orphan*/  atse_eth_addr; int /*<<< orphan*/  atse_miibus; struct ifnet* atse_ifp; int /*<<< orphan*/  atse_bmcr1; int /*<<< orphan*/  atse_bmcr0; int /*<<< orphan*/  atse_mtx; int /*<<< orphan*/  atse_tick; int /*<<< orphan*/ * br; int /*<<< orphan*/  br_mtx; int /*<<< orphan*/  dev; int /*<<< orphan*/  ih_rx; int /*<<< orphan*/ * xdma_rx; int /*<<< orphan*/ * xchan_tx; int /*<<< orphan*/  ih_tx; int /*<<< orphan*/ * xdma_tx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ATSE_TX_LIST_CNT ; 
 int /*<<< orphan*/  BASE_CFG_MDIO_ADDR0 ; 
 int /*<<< orphan*/  BASE_CFG_MDIO_ADDR1 ; 
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  BUFRING_SIZE ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct atse_softc*,int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENXIO ; 
 int /*<<< orphan*/  IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  MDIO_0_START ; 
 int /*<<< orphan*/  MDIO_1_START ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/ * MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NUM_RX_MBUF ; 
 int /*<<< orphan*/  RX_QUEUE_SIZE ; 
 int /*<<< orphan*/  TX_QUEUE_SIZE ; 
 int /*<<< orphan*/  XCHAN_CAP_NOSEG ; 
 int /*<<< orphan*/  atse_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atse_ethernet_option_bits_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atse_ifmedia_sts ; 
 int /*<<< orphan*/  atse_ifmedia_upd ; 
 int /*<<< orphan*/  atse_init ; 
 int /*<<< orphan*/  atse_ioctl ; 
 int /*<<< orphan*/  atse_qflush ; 
 int /*<<< orphan*/  atse_reset (struct atse_softc*) ; 
 int /*<<< orphan*/  atse_rx_enqueue (struct atse_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atse_sysctl_stats_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atse_transmit ; 
 int /*<<< orphan*/  atse_xdma_rx_intr ; 
 int /*<<< orphan*/  atse_xdma_tx_intr ; 
 int /*<<< orphan*/ * buf_ring_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct atse_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* xdma_channel_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* xdma_ofw_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xdma_prep_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdma_queue_submit (int /*<<< orphan*/ *) ; 
 int xdma_setup_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct atse_softc*,int /*<<< orphan*/ *) ; 

int
atse_attach(device_t dev)
{
	struct atse_softc *sc;
	struct ifnet *ifp;
	uint32_t caps;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;

	/* Get xDMA controller */
	sc->xdma_tx = xdma_ofw_get(sc->dev, "tx");
	if (sc->xdma_tx == NULL) {
		device_printf(dev, "Can't find DMA controller.\n");
		return (ENXIO);
	}

	/*
	 * Only final (EOP) write can be less than "symbols per beat" value
	 * so we have to defrag mbuf chain.
	 * Chapter 15. On-Chip FIFO Memory Core.
	 * Embedded Peripherals IP User Guide.
	 */
	caps = XCHAN_CAP_NOSEG;

	/* Alloc xDMA virtual channel. */
	sc->xchan_tx = xdma_channel_alloc(sc->xdma_tx, caps);
	if (sc->xchan_tx == NULL) {
		device_printf(dev, "Can't alloc virtual DMA channel.\n");
		return (ENXIO);
	}

	/* Setup interrupt handler. */
	error = xdma_setup_intr(sc->xchan_tx, atse_xdma_tx_intr, sc, &sc->ih_tx);
	if (error) {
		device_printf(sc->dev,
		    "Can't setup xDMA interrupt handler.\n");
		return (ENXIO);
	}

	xdma_prep_sg(sc->xchan_tx,
	    TX_QUEUE_SIZE,	/* xchan requests queue size */
	    MCLBYTES,	/* maxsegsize */
	    8,		/* maxnsegs */
	    16,		/* alignment */
	    0,		/* boundary */
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR);

	/* Get RX xDMA controller */
	sc->xdma_rx = xdma_ofw_get(sc->dev, "rx");
	if (sc->xdma_rx == NULL) {
		device_printf(dev, "Can't find DMA controller.\n");
		return (ENXIO);
	}

	/* Alloc xDMA virtual channel. */
	sc->xchan_rx = xdma_channel_alloc(sc->xdma_rx, caps);
	if (sc->xchan_rx == NULL) {
		device_printf(dev, "Can't alloc virtual DMA channel.\n");
		return (ENXIO);
	}

	/* Setup interrupt handler. */
	error = xdma_setup_intr(sc->xchan_rx, atse_xdma_rx_intr, sc, &sc->ih_rx);
	if (error) {
		device_printf(sc->dev,
		    "Can't setup xDMA interrupt handler.\n");
		return (ENXIO);
	}

	xdma_prep_sg(sc->xchan_rx,
	    RX_QUEUE_SIZE,	/* xchan requests queue size */
	    MCLBYTES,		/* maxsegsize */
	    1,			/* maxnsegs */
	    16,			/* alignment */
	    0,			/* boundary */
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR);

	mtx_init(&sc->br_mtx, "buf ring mtx", NULL, MTX_DEF);
	sc->br = buf_ring_alloc(BUFRING_SIZE, M_DEVBUF,
	    M_NOWAIT, &sc->br_mtx);
	if (sc->br == NULL) {
		return (ENOMEM);
	}

	atse_ethernet_option_bits_read(dev);

	mtx_init(&sc->atse_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);

	callout_init_mtx(&sc->atse_tick, &sc->atse_mtx, 0);

	/*
	 * We are only doing single-PHY with this driver currently.  The
	 * defaults would be right so that BASE_CFG_MDIO_ADDR0 points to the
	 * 1st PHY address (0) apart from the fact that BMCR0 is always
	 * the PCS mapping, so we always use BMCR1. See Table 5-1 0xA0-0xBF.
	 */
#if 0	/* Always PCS. */
	sc->atse_bmcr0 = MDIO_0_START;
	CSR_WRITE_4(sc, BASE_CFG_MDIO_ADDR0, 0x00);
#endif
	/* Always use matching PHY for atse[0..]. */
	sc->atse_phy_addr = device_get_unit(dev);
	sc->atse_bmcr1 = MDIO_1_START;
	CSR_WRITE_4(sc, BASE_CFG_MDIO_ADDR1, sc->atse_phy_addr);

	/* Reset the adapter. */
	atse_reset(sc);

	/* Setup interface. */
	ifp = sc->atse_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "if_alloc() failed\n");
		error = ENOSPC;
		goto err;
	}
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = atse_ioctl;
	ifp->if_transmit = atse_transmit;
	ifp->if_qflush = atse_qflush;
	ifp->if_init = atse_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, ATSE_TX_LIST_CNT - 1);
	ifp->if_snd.ifq_drv_maxlen = ATSE_TX_LIST_CNT - 1;
	IFQ_SET_READY(&ifp->if_snd);

	/* MII setup. */
	error = mii_attach(dev, &sc->atse_miibus, ifp, atse_ifmedia_upd,
	    atse_ifmedia_sts, BMSR_DEFCAPMASK, MII_PHY_ANY, MII_OFFSET_ANY, 0);
	if (error != 0) {
		device_printf(dev, "attaching PHY failed: %d\n", error);
		goto err;
	}

	/* Call media-indepedent attach routine. */
	ether_ifattach(ifp, sc->atse_eth_addr);

	/* Tell the upper layer(s) about vlan mtu support. */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);
	ifp->if_capabilities |= IFCAP_VLAN_MTU;
	ifp->if_capenable = ifp->if_capabilities;

err:
	if (error != 0) {
		atse_detach(dev);
	}

	if (error == 0) {
		atse_sysctl_stats_attach(dev);
	}

	atse_rx_enqueue(sc, NUM_RX_MBUF);
	xdma_queue_submit(sc->xchan_rx);

	return (error);
}