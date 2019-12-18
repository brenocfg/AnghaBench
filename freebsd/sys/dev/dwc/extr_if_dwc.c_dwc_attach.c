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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {void* ifq_drv_maxlen; } ;
struct ifnet {int if_flags; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; struct dwc_softc* if_softc; } ;
struct dwc_softc {scalar_t__ mactype; int rxdesc_ring_paddr; int txdesc_ring_paddr; int is_attached; int /*<<< orphan*/  miibus; void* mii_softc; struct ifnet* ifp; int /*<<< orphan*/  intr_cookie; int /*<<< orphan*/ * res; int /*<<< orphan*/  mtx; int /*<<< orphan*/  dwc_callout; int /*<<< orphan*/  dev; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  mii_clk; void* txcount; scalar_t__ rx_idx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  BUS_MODE ; 
 int BUS_MODE_EIGHTXPBL ; 
 int BUS_MODE_FIXEDBURST ; 
 int BUS_MODE_PBL_BEATS_8 ; 
 int BUS_MODE_PBL_SHIFT ; 
 int BUS_MODE_PRIORXTX_41 ; 
 int BUS_MODE_PRIORXTX_SHIFT ; 
 int BUS_MODE_SWR ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ DWC_GMAC_ALT_DESC ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 scalar_t__ IF_DWC_INIT (int /*<<< orphan*/ ) ; 
 scalar_t__ IF_DWC_MAC_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_DWC_MII_CLK (int /*<<< orphan*/ ) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int MAC_RESET_TIMEOUT ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MII_PHY_ANY ; 
 int MODE_SR ; 
 int MODE_ST ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  OPERATION_MODE ; 
 int READ4 (struct dwc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_DESCR_LIST_ADDR ; 
 int /*<<< orphan*/  TX_DESCR_LIST_ADDR ; 
 void* TX_DESC_COUNT ; 
 int /*<<< orphan*/  WRITE4 (struct dwc_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dwc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dwc_clock_init (int /*<<< orphan*/ ) ; 
 scalar_t__ dwc_get_hwaddr (struct dwc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_init ; 
 int /*<<< orphan*/  dwc_intr ; 
 int /*<<< orphan*/  dwc_ioctl ; 
 int /*<<< orphan*/  dwc_media_change ; 
 int /*<<< orphan*/  dwc_media_status ; 
 scalar_t__ dwc_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_spec ; 
 int /*<<< orphan*/  dwc_txstart ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 scalar_t__ setup_dma (struct dwc_softc*) ; 

__attribute__((used)) static int
dwc_attach(device_t dev)
{
	uint8_t macaddr[ETHER_ADDR_LEN];
	struct dwc_softc *sc;
	struct ifnet *ifp;
	int error, i;
	uint32_t reg;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->rx_idx = 0;
	sc->txcount = TX_DESC_COUNT;
	sc->mii_clk = IF_DWC_MII_CLK(dev);
	sc->mactype = IF_DWC_MAC_TYPE(dev);

	if (IF_DWC_INIT(dev) != 0)
		return (ENXIO);

#ifdef EXT_RESOURCES
	if (dwc_clock_init(dev) != 0)
		return (ENXIO);
#endif

	if (bus_alloc_resources(dev, dwc_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	/* Read MAC before reset */
	if (dwc_get_hwaddr(sc, macaddr)) {
		device_printf(sc->dev, "can't get mac\n");
		return (ENXIO);
	}

	/* Reset the PHY if needed */
	if (dwc_reset(dev) != 0) {
		device_printf(dev, "Can't reset the PHY\n");
		return (ENXIO);
	}

	/* Reset */
	reg = READ4(sc, BUS_MODE);
	reg |= (BUS_MODE_SWR);
	WRITE4(sc, BUS_MODE, reg);

	for (i = 0; i < MAC_RESET_TIMEOUT; i++) {
		if ((READ4(sc, BUS_MODE) & BUS_MODE_SWR) == 0)
			break;
		DELAY(10);
	}
	if (i >= MAC_RESET_TIMEOUT) {
		device_printf(sc->dev, "Can't reset DWC.\n");
		return (ENXIO);
	}

	if (sc->mactype == DWC_GMAC_ALT_DESC) {
		reg = BUS_MODE_FIXEDBURST;
		reg |= (BUS_MODE_PRIORXTX_41 << BUS_MODE_PRIORXTX_SHIFT);
	} else
		reg = (BUS_MODE_EIGHTXPBL);
	reg |= (BUS_MODE_PBL_BEATS_8 << BUS_MODE_PBL_SHIFT);
	WRITE4(sc, BUS_MODE, reg);

	/*
	 * DMA must be stop while changing descriptor list addresses.
	 */
	reg = READ4(sc, OPERATION_MODE);
	reg &= ~(MODE_ST | MODE_SR);
	WRITE4(sc, OPERATION_MODE, reg);

	if (setup_dma(sc))
	        return (ENXIO);

	/* Setup addresses */
	WRITE4(sc, RX_DESCR_LIST_ADDR, sc->rxdesc_ring_paddr);
	WRITE4(sc, TX_DESCR_LIST_ADDR, sc->txdesc_ring_paddr);

	mtx_init(&sc->mtx, device_get_nameunit(sc->dev),
	    MTX_NETWORK_LOCK, MTX_DEF);

	callout_init_mtx(&sc->dwc_callout, &sc->mtx, 0);

	/* Setup interrupt handler. */
	error = bus_setup_intr(dev, sc->res[1], INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, dwc_intr, sc, &sc->intr_cookie);
	if (error != 0) {
		device_printf(dev, "could not setup interrupt handler.\n");
		return (ENXIO);
	}

	/* Set up the ethernet interface. */
	sc->ifp = ifp = if_alloc(IFT_ETHER);

	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_capabilities = IFCAP_VLAN_MTU;
	ifp->if_capenable = ifp->if_capabilities;
	ifp->if_start = dwc_txstart;
	ifp->if_ioctl = dwc_ioctl;
	ifp->if_init = dwc_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, TX_DESC_COUNT - 1);
	ifp->if_snd.ifq_drv_maxlen = TX_DESC_COUNT - 1;
	IFQ_SET_READY(&ifp->if_snd);

	/* Attach the mii driver. */
	error = mii_attach(dev, &sc->miibus, ifp, dwc_media_change,
	    dwc_media_status, BMSR_DEFCAPMASK, MII_PHY_ANY,
	    MII_OFFSET_ANY, 0);

	if (error != 0) {
		device_printf(dev, "PHY attach failed\n");
		return (ENXIO);
	}
	sc->mii_softc = device_get_softc(sc->miibus);

	/* All ready to run, attach the ethernet interface. */
	ether_ifattach(ifp, macaddr);
	sc->is_attached = true;

	return (0);
}