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
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; int /*<<< orphan*/  ifq_maxlen; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; TYPE_1__ if_snd; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_mtu; struct dtsec_softc* if_softc; } ;
struct dtsec_softc {scalar_t__ sc_mode; int (* sc_port_tx_init ) (struct dtsec_softc*,int /*<<< orphan*/ ) ;int (* sc_port_rx_init ) (struct dtsec_softc*,int /*<<< orphan*/ ) ;scalar_t__ sc_phy_addr; int /*<<< orphan*/  sc_mac_addr; int /*<<< orphan*/  sc_mii_dev; void* sc_mii; int /*<<< orphan*/  sc_dev; struct ifnet* sc_ifnet; int /*<<< orphan*/  sc_fm_base; int /*<<< orphan*/  sc_muramh; int /*<<< orphan*/  sc_fmh; int /*<<< orphan*/  sc_tick_callout; int /*<<< orphan*/  sc_mii_lock; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_mac_mdio_irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  CALLOUT_MPSAFE ; 
 scalar_t__ DTSEC_MODE_REGULAR ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETHERMTU ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  IFCAP_JUMBO_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_MAXLEN ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  NO_IRQ ; 
 scalar_t__ TSEC_TX_NUM_DESC ; 
 scalar_t__ XX_MallocSmartInit () ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dtsec_configure_mode (struct dtsec_softc*) ; 
 int /*<<< orphan*/  dtsec_detach (int /*<<< orphan*/ ) ; 
 int dtsec_fm_mac_init (struct dtsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtsec_if_init ; 
 int /*<<< orphan*/  dtsec_if_ioctl ; 
 int /*<<< orphan*/  dtsec_if_start ; 
 int /*<<< orphan*/  dtsec_ifmedia_sts ; 
 int /*<<< orphan*/  dtsec_ifmedia_upd ; 
 int dtsec_rm_fi_pool_init (struct dtsec_softc*) ; 
 int dtsec_rm_fqr_rx_init (struct dtsec_softc*) ; 
 int dtsec_rm_fqr_tx_init (struct dtsec_softc*) ; 
 int dtsec_rm_pool_rx_init (struct dtsec_softc*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 int fman_get_bushandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fman_get_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fman_get_muram_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,char*,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dtsec_softc*,int /*<<< orphan*/ ) ; 
 int stub2 (struct dtsec_softc*,int /*<<< orphan*/ ) ; 

int
dtsec_attach(device_t dev)
{
	struct dtsec_softc *sc;
	device_t parent;
	int error;
	struct ifnet *ifp;

	sc = device_get_softc(dev);

	parent = device_get_parent(dev);
	sc->sc_dev = dev;
	sc->sc_mac_mdio_irq = NO_IRQ;

	/* Check if MallocSmart allocator is ready */
	if (XX_MallocSmartInit() != E_OK)
		return (ENXIO);

	/* Init locks */
	mtx_init(&sc->sc_lock, device_get_nameunit(dev),
	    "DTSEC Global Lock", MTX_DEF);

	mtx_init(&sc->sc_mii_lock, device_get_nameunit(dev),
	    "DTSEC MII Lock", MTX_DEF);

	/* Init callouts */
	callout_init(&sc->sc_tick_callout, CALLOUT_MPSAFE);

	/* Read configuraton */
	if ((error = fman_get_handle(parent, &sc->sc_fmh)) != 0)
		return (error);

	if ((error = fman_get_muram_handle(parent, &sc->sc_muramh)) != 0)
		return (error);

	if ((error = fman_get_bushandle(parent, &sc->sc_fm_base)) != 0)
		return (error);

	/* Configure working mode */
	dtsec_configure_mode(sc);

	/* If we are working in regular mode configure BMAN and QMAN */
	if (sc->sc_mode == DTSEC_MODE_REGULAR) {
		/* Create RX buffer pool */
		error = dtsec_rm_pool_rx_init(sc);
		if (error != 0)
			return (EIO);

		/* Create RX frame queue range */
		error = dtsec_rm_fqr_rx_init(sc);
		if (error != 0)
			return (EIO);

		/* Create frame info pool */
		error = dtsec_rm_fi_pool_init(sc);
		if (error != 0)
			return (EIO);

		/* Create TX frame queue range */
		error = dtsec_rm_fqr_tx_init(sc);
		if (error != 0)
			return (EIO);
	}

	/* Init FMan MAC module. */
	error = dtsec_fm_mac_init(sc, sc->sc_mac_addr);
	if (error != 0) {
		dtsec_detach(dev);
		return (ENXIO);
	}

	/* Init FMan TX port */
	error = sc->sc_port_tx_init(sc, device_get_unit(sc->sc_dev));
	if (error != 0) {
		dtsec_detach(dev);
		return (ENXIO);
	}

	/* Init FMan RX port */
	error = sc->sc_port_rx_init(sc, device_get_unit(sc->sc_dev));
	if (error != 0) {
		dtsec_detach(dev);
		return (ENXIO);
	}

	/* Create network interface for upper layers */
	ifp = sc->sc_ifnet = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(sc->sc_dev, "if_alloc() failed.\n");
		dtsec_detach(dev);
		return (ENOMEM);
	}

	ifp->if_softc = sc;
	ifp->if_mtu = ETHERMTU;	/* TODO: Configure */
	ifp->if_flags = IFF_SIMPLEX | IFF_BROADCAST;
	ifp->if_init = dtsec_if_init;
	ifp->if_start = dtsec_if_start;
	ifp->if_ioctl = dtsec_if_ioctl;
	ifp->if_snd.ifq_maxlen = IFQ_MAXLEN;

	if (sc->sc_phy_addr >= 0)
		if_initname(ifp, device_get_name(sc->sc_dev),
		    device_get_unit(sc->sc_dev));
	else
		if_initname(ifp, "dtsec_phy", device_get_unit(sc->sc_dev));

	/* TODO */
#if 0
	IFQ_SET_MAXLEN(&ifp->if_snd, TSEC_TX_NUM_DESC - 1);
	ifp->if_snd.ifq_drv_maxlen = TSEC_TX_NUM_DESC - 1;
	IFQ_SET_READY(&ifp->if_snd);
#endif
	ifp->if_capabilities = IFCAP_JUMBO_MTU; /* TODO: HWCSUM */
	ifp->if_capenable = ifp->if_capabilities;

	/* Attach PHY(s) */
	error = mii_attach(sc->sc_dev, &sc->sc_mii_dev, ifp, dtsec_ifmedia_upd,
	    dtsec_ifmedia_sts, BMSR_DEFCAPMASK, sc->sc_phy_addr,
	    MII_OFFSET_ANY, 0);
	if (error) {
		device_printf(sc->sc_dev, "attaching PHYs failed: %d\n", error);
		dtsec_detach(sc->sc_dev);
		return (error);
	}
	sc->sc_mii = device_get_softc(sc->sc_mii_dev);

	/* Attach to stack */
	ether_ifattach(ifp, sc->sc_mac_addr);

	return (0);
}