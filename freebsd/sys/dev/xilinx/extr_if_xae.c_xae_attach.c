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
typedef  int uint32_t ;
struct xae_softc {int is_attached; int /*<<< orphan*/  xchan_rx; int /*<<< orphan*/  macaddr; int /*<<< orphan*/  miibus; void* mii_softc; int /*<<< orphan*/  phy_addr; struct ifnet* ifp; int /*<<< orphan*/  intr_cookie; int /*<<< orphan*/ * res; int /*<<< orphan*/  mtx; int /*<<< orphan*/  xae_callout; int /*<<< orphan*/  dev; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/ * br; } ;
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_qflush; int /*<<< orphan*/  if_transmit; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; struct xae_softc* if_softc; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  BUFRING_SIZE ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int MDIO_CLK_DIV_DEFAULT ; 
 int MDIO_SETUP_CLK_DIV_S ; 
 int MDIO_SETUP_ENABLE ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NUM_RX_MBUF ; 
 scalar_t__ OF_getproplen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  READ4 (struct xae_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ TX_DESC_COUNT ; 
 int /*<<< orphan*/  WRITE4 (struct xae_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XAE_IDENT ; 
 int /*<<< orphan*/  XAE_MDIO_SETUP ; 
 int /*<<< orphan*/ * buf_ring_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct xae_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mdio_wait (struct xae_softc*) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 scalar_t__ setup_xdma (struct xae_softc*) ; 
 scalar_t__ xae_get_hwaddr (struct xae_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ xae_get_phyaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xae_init ; 
 int /*<<< orphan*/  xae_intr ; 
 int /*<<< orphan*/  xae_ioctl ; 
 int /*<<< orphan*/  xae_media_change ; 
 int /*<<< orphan*/  xae_media_status ; 
 int /*<<< orphan*/  xae_phy_fixup (struct xae_softc*) ; 
 int /*<<< orphan*/  xae_qflush ; 
 int /*<<< orphan*/  xae_rx_enqueue (struct xae_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xae_spec ; 
 int /*<<< orphan*/  xae_transmit ; 
 int /*<<< orphan*/  xdma_queue_submit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xae_attach(device_t dev)
{
	struct xae_softc *sc;
	struct ifnet *ifp;
	phandle_t node;
	uint32_t reg;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	if (setup_xdma(sc) != 0) {
		device_printf(dev, "Could not setup xDMA.\n");
		return (ENXIO);
	}

	mtx_init(&sc->mtx, device_get_nameunit(sc->dev),
	    MTX_NETWORK_LOCK, MTX_DEF);

	sc->br = buf_ring_alloc(BUFRING_SIZE, M_DEVBUF,
	    M_NOWAIT, &sc->mtx);
	if (sc->br == NULL)
		return (ENOMEM);

	if (bus_alloc_resources(dev, xae_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	device_printf(sc->dev, "Identification: %x\n",
	    READ4(sc, XAE_IDENT));

	/* Get MAC addr */
	if (xae_get_hwaddr(sc, sc->macaddr)) {
		device_printf(sc->dev, "can't get mac\n");
		return (ENXIO);
	}

	/* Enable MII clock */
	reg = (MDIO_CLK_DIV_DEFAULT << MDIO_SETUP_CLK_DIV_S);
	reg |= MDIO_SETUP_ENABLE;
	WRITE4(sc, XAE_MDIO_SETUP, reg);
	if (mdio_wait(sc))
		return (ENXIO);

	callout_init_mtx(&sc->xae_callout, &sc->mtx, 0);

	/* Setup interrupt handler. */
	error = bus_setup_intr(dev, sc->res[1], INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, xae_intr, sc, &sc->intr_cookie);
	if (error != 0) {
		device_printf(dev, "could not setup interrupt handler.\n");
		return (ENXIO);
	}

	/* Set up the ethernet interface. */
	sc->ifp = ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "could not allocate ifp.\n");
		return (ENXIO);
	}

	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_capabilities = IFCAP_VLAN_MTU;
	ifp->if_capenable = ifp->if_capabilities;
	ifp->if_transmit = xae_transmit;
	ifp->if_qflush = xae_qflush;
	ifp->if_ioctl = xae_ioctl;
	ifp->if_init = xae_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, TX_DESC_COUNT - 1);
	ifp->if_snd.ifq_drv_maxlen = TX_DESC_COUNT - 1;
	IFQ_SET_READY(&ifp->if_snd);

	if (xae_get_phyaddr(node, &sc->phy_addr) != 0)
		return (ENXIO);

	/* Attach the mii driver. */
	error = mii_attach(dev, &sc->miibus, ifp, xae_media_change,
	    xae_media_status, BMSR_DEFCAPMASK, sc->phy_addr,
	    MII_OFFSET_ANY, 0);

	if (error != 0) {
		device_printf(dev, "PHY attach failed\n");
		return (ENXIO);
	}
	sc->mii_softc = device_get_softc(sc->miibus);

	/* Apply vcu118 workaround. */
	if (OF_getproplen(node, "xlnx,vcu118") >= 0)
		xae_phy_fixup(sc);

	/* All ready to run, attach the ethernet interface. */
	ether_ifattach(ifp, sc->macaddr);
	sc->is_attached = true;

	xae_rx_enqueue(sc, NUM_RX_MBUF);
	xdma_queue_submit(sc->xchan_rx);

	return (0);
}