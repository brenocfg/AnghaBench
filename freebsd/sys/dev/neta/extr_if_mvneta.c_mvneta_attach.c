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
struct mvneta_softc {int version; scalar_t__ phy_addr; scalar_t__ use_inband_status; int phy_attached; int phy_speed; struct ifnet* ifp; int /*<<< orphan*/ * ih_cookie; int /*<<< orphan*/ * res; int /*<<< orphan*/  tick_ch; int /*<<< orphan*/ * dev; int /*<<< orphan*/  mvneta_ifmedia; scalar_t__ phy_fdx; int /*<<< orphan*/  phy_mode; int /*<<< orphan*/ * miibus; void* mii; int /*<<< orphan*/  enaddr; int /*<<< orphan*/  mtx; } ;
struct TYPE_5__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_capabilities; int if_flags; int if_capenable; int if_hwassist; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_init; TYPE_2__ if_snd; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_qflush; int /*<<< orphan*/  if_transmit; struct mvneta_softc* if_softc; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_4__ {int description; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int CSUM_IP ; 
 int CSUM_TCP ; 
 int CSUM_UDP ; 
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ FALSE ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_HWCSUM_IPV6 ; 
 int IFCAP_JUMBO_MTU ; 
 int IFCAP_LRO ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_1000_T ; 
 int IFM_100_TX ; 
 int IFM_10_T ; 
 int IFM_2500_T ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int IFM_HDX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_2__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int IO_WIN_COH_ATTR_MASK ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 scalar_t__ MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ MVNETA_IS_LINKUP (struct mvneta_softc*) ; 
 int /*<<< orphan*/  MVNETA_PACC ; 
 int MVNETA_PACC_ACCELERATIONMODE_EDM ; 
 int /*<<< orphan*/  MVNETA_PHY_QSGMII ; 
 int /*<<< orphan*/  MVNETA_PHY_SGMII ; 
 int /*<<< orphan*/  MVNETA_PRXINIT ; 
 int /*<<< orphan*/  MVNETA_PSNPCFG ; 
 int MVNETA_PSNPCFG_BUFSNP_MASK ; 
 int MVNETA_PSNPCFG_DESCSNP_MASK ; 
 int /*<<< orphan*/  MVNETA_PTXINIT ; 
 int /*<<< orphan*/  MVNETA_PV ; 
 int MVNETA_READ (struct mvneta_softc*,int /*<<< orphan*/ ) ; 
 int MVNETA_RX_QNUM_MAX ; 
 int MVNETA_TX_QNUM_MAX ; 
 scalar_t__ MVNETA_TX_RING_CNT ; 
 int /*<<< orphan*/  MVNETA_WRITE (struct mvneta_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MV_WIN_NETA_BASE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 scalar_t__ bootverbose ; 
 int bus_alloc_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mvneta_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mvneta_softc*) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ *) ; 
 void* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int) ; 
 int mii_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ **,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_init ; 
 int /*<<< orphan*/  mii_mutex ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvneta_disable_intr (struct mvneta_softc*) ; 
 int mvneta_dma_create (struct mvneta_softc*) ; 
 int /*<<< orphan*/  mvneta_filter_setup (struct mvneta_softc*) ; 
 scalar_t__ mvneta_get_mac_address (struct mvneta_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ mvneta_has_switch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvneta_init ; 
 int /*<<< orphan*/  mvneta_initreg (struct ifnet*) ; 
 TYPE_1__* mvneta_intrs ; 
 int /*<<< orphan*/  mvneta_ioctl ; 
 int /*<<< orphan*/  mvneta_linkdown (struct mvneta_softc*) ; 
 int /*<<< orphan*/  mvneta_linkup (struct mvneta_softc*) ; 
 int /*<<< orphan*/  mvneta_mediachange ; 
 int /*<<< orphan*/  mvneta_mediastatus ; 
 int /*<<< orphan*/  mvneta_qflush ; 
 int mvneta_ring_init_rx_queue (struct mvneta_softc*,int) ; 
 int mvneta_ring_init_tx_queue (struct mvneta_softc*,int) ; 
 int /*<<< orphan*/  mvneta_sc_lock (struct mvneta_softc*) ; 
 int /*<<< orphan*/  mvneta_sc_unlock (struct mvneta_softc*) ; 
 int /*<<< orphan*/  mvneta_set_mac_address (struct mvneta_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_start ; 
 int /*<<< orphan*/  mvneta_tick ; 
 int /*<<< orphan*/  mvneta_transmit ; 
 int /*<<< orphan*/  mvneta_update_autoneg (struct mvneta_softc*,scalar_t__) ; 
 int /*<<< orphan*/  mvneta_update_media (struct mvneta_softc*,int) ; 
 int /*<<< orphan*/  res_spec ; 
 int /*<<< orphan*/  sysctl_mvneta_init (struct mvneta_softc*) ; 

int
mvneta_attach(device_t self)
{
	struct mvneta_softc *sc;
	struct ifnet *ifp;
	device_t child;
	int ifm_target;
	int q, error;
#if !defined(__aarch64__)
	uint32_t reg;
#endif

	sc = device_get_softc(self);
	sc->dev = self;

	mtx_init(&sc->mtx, "mvneta_sc", NULL, MTX_DEF);

	error = bus_alloc_resources(self, res_spec, sc->res);
	if (error) {
		device_printf(self, "could not allocate resources\n");
		return (ENXIO);
	}

	sc->version = MVNETA_READ(sc, MVNETA_PV);
	device_printf(self, "version is %x\n", sc->version);
	callout_init(&sc->tick_ch, 0);

	/*
	 * make sure DMA engines are in reset state
	 */
	MVNETA_WRITE(sc, MVNETA_PRXINIT, 0x00000001);
	MVNETA_WRITE(sc, MVNETA_PTXINIT, 0x00000001);

#if !defined(__aarch64__)
	/*
	 * Disable port snoop for buffers and descriptors
	 * to avoid L2 caching of both without DRAM copy.
	 * Obtain coherency settings from the first MBUS
	 * window attribute.
	 */
	if ((MVNETA_READ(sc, MV_WIN_NETA_BASE(0)) & IO_WIN_COH_ATTR_MASK) == 0) {
		reg = MVNETA_READ(sc, MVNETA_PSNPCFG);
		reg &= ~MVNETA_PSNPCFG_DESCSNP_MASK;
		reg &= ~MVNETA_PSNPCFG_BUFSNP_MASK;
		MVNETA_WRITE(sc, MVNETA_PSNPCFG, reg);
	}
#endif

	/*
	 * MAC address
	 */
	if (mvneta_get_mac_address(sc, sc->enaddr)) {
		device_printf(self, "no mac address.\n");
		return (ENXIO);
	}
	mvneta_set_mac_address(sc, sc->enaddr);

	mvneta_disable_intr(sc);

	/* Allocate network interface */
	ifp = sc->ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(self, "if_alloc() failed\n");
		mvneta_detach(self);
		return (ENOMEM);
	}
	if_initname(ifp, device_get_name(self), device_get_unit(self));

	/*
	 * We can support 802.1Q VLAN-sized frames and jumbo
	 * Ethernet frames.
	 */
	ifp->if_capabilities |= IFCAP_VLAN_MTU | IFCAP_JUMBO_MTU;

	ifp->if_softc = sc;
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
#ifdef MVNETA_MULTIQUEUE
	ifp->if_transmit = mvneta_transmit;
	ifp->if_qflush = mvneta_qflush;
#else /* !MVNETA_MULTIQUEUE */
	ifp->if_start = mvneta_start;
	ifp->if_snd.ifq_drv_maxlen = MVNETA_TX_RING_CNT - 1;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifp->if_snd.ifq_drv_maxlen);
	IFQ_SET_READY(&ifp->if_snd);
#endif
	ifp->if_init = mvneta_init;
	ifp->if_ioctl = mvneta_ioctl;

	/*
	 * We can do IPv4/TCPv4/UDPv4/TCPv6/UDPv6 checksums in hardware.
	 */
	ifp->if_capabilities |= IFCAP_HWCSUM;

	/*
	 * As VLAN hardware tagging is not supported
	 * but is necessary to perform VLAN hardware checksums,
	 * it is done in the driver
	 */
	ifp->if_capabilities |= IFCAP_VLAN_HWTAGGING | IFCAP_VLAN_HWCSUM;

	/*
	 * Currently IPv6 HW checksum is broken, so make sure it is disabled.
	 */
	ifp->if_capabilities &= ~IFCAP_HWCSUM_IPV6;
	ifp->if_capenable = ifp->if_capabilities;

	/*
	 * Disabled option(s):
	 * - Support for Large Receive Offload
	 */
	ifp->if_capabilities |= IFCAP_LRO;

	ifp->if_hwassist = CSUM_IP | CSUM_TCP | CSUM_UDP;

	/*
	 * Device DMA Buffer allocation.
	 * Handles resource deallocation in case of failure.
	 */
	error = mvneta_dma_create(sc);
	if (error != 0) {
		mvneta_detach(self);
		return (error);
	}

	/* Initialize queues */
	for (q = 0; q < MVNETA_TX_QNUM_MAX; q++) {
		error = mvneta_ring_init_tx_queue(sc, q);
		if (error != 0) {
			mvneta_detach(self);
			return (error);
		}
	}

	for (q = 0; q < MVNETA_RX_QNUM_MAX; q++) {
		error = mvneta_ring_init_rx_queue(sc, q);
		if (error != 0) {
			mvneta_detach(self);
			return (error);
		}
	}

	ether_ifattach(ifp, sc->enaddr);

	/*
	 * Enable DMA engines and Initialize Device Registers.
	 */
	MVNETA_WRITE(sc, MVNETA_PRXINIT, 0x00000000);
	MVNETA_WRITE(sc, MVNETA_PTXINIT, 0x00000000);
	MVNETA_WRITE(sc, MVNETA_PACC, MVNETA_PACC_ACCELERATIONMODE_EDM);
	mvneta_sc_lock(sc);
	mvneta_filter_setup(sc);
	mvneta_sc_unlock(sc);
	mvneta_initreg(ifp);

	/*
	 * Now MAC is working, setup MII.
	 */
	if (mii_init == 0) {
		/*
		 * MII bus is shared by all MACs and all PHYs in SoC.
		 * serializing the bus access should be safe.
		 */
		mtx_init(&mii_mutex, "mvneta_mii", NULL, MTX_DEF);
		mii_init = 1;
	}

	/* Attach PHY(s) */
	if ((sc->phy_addr != MII_PHY_ANY) && (!sc->use_inband_status)) {
		error = mii_attach(self, &sc->miibus, ifp, mvneta_mediachange,
		    mvneta_mediastatus, BMSR_DEFCAPMASK, sc->phy_addr,
		    MII_OFFSET_ANY, 0);
		if (error != 0) {
			if (bootverbose) {
				device_printf(self,
				    "MII attach failed, error: %d\n", error);
			}
			ether_ifdetach(sc->ifp);
			mvneta_detach(self);
			return (error);
		}
		sc->mii = device_get_softc(sc->miibus);
		sc->phy_attached = 1;

		/* Disable auto-negotiation in MAC - rely on PHY layer */
		mvneta_update_autoneg(sc, FALSE);
	} else if (sc->use_inband_status == TRUE) {
		/* In-band link status */
		ifmedia_init(&sc->mvneta_ifmedia, 0, mvneta_mediachange,
		    mvneta_mediastatus);

		/* Configure media */
		ifmedia_add(&sc->mvneta_ifmedia, IFM_ETHER | IFM_1000_T | IFM_FDX,
		    0, NULL);
		ifmedia_add(&sc->mvneta_ifmedia, IFM_ETHER | IFM_100_TX, 0, NULL);
		ifmedia_add(&sc->mvneta_ifmedia, IFM_ETHER | IFM_100_TX | IFM_FDX,
		    0, NULL);
		ifmedia_add(&sc->mvneta_ifmedia, IFM_ETHER | IFM_10_T, 0, NULL);
		ifmedia_add(&sc->mvneta_ifmedia, IFM_ETHER | IFM_10_T | IFM_FDX,
		    0, NULL);
		ifmedia_add(&sc->mvneta_ifmedia, IFM_ETHER | IFM_AUTO, 0, NULL);
		ifmedia_set(&sc->mvneta_ifmedia, IFM_ETHER | IFM_AUTO);

		/* Enable auto-negotiation */
		mvneta_update_autoneg(sc, TRUE);

		mvneta_sc_lock(sc);
		if (MVNETA_IS_LINKUP(sc))
			mvneta_linkup(sc);
		else
			mvneta_linkdown(sc);
		mvneta_sc_unlock(sc);

	} else {
		/* Fixed-link, use predefined values */
		mvneta_update_autoneg(sc, FALSE);
		ifmedia_init(&sc->mvneta_ifmedia, 0, mvneta_mediachange,
		    mvneta_mediastatus);

		ifm_target = IFM_ETHER;
		switch (sc->phy_speed) {
		case 2500:
			if (sc->phy_mode != MVNETA_PHY_SGMII &&
			    sc->phy_mode != MVNETA_PHY_QSGMII) {
				device_printf(self,
				    "2.5G speed can work only in (Q)SGMII mode\n");
				ether_ifdetach(sc->ifp);
				mvneta_detach(self);
				return (ENXIO);
			}
			ifm_target |= IFM_2500_T;
			break;
		case 1000:
			ifm_target |= IFM_1000_T;
			break;
		case 100:
			ifm_target |= IFM_100_TX;
			break;
		case 10:
			ifm_target |= IFM_10_T;
			break;
		default:
			ether_ifdetach(sc->ifp);
			mvneta_detach(self);
			return (ENXIO);
		}

		if (sc->phy_fdx)
			ifm_target |= IFM_FDX;
		else
			ifm_target |= IFM_HDX;

		ifmedia_add(&sc->mvneta_ifmedia, ifm_target, 0, NULL);
		ifmedia_set(&sc->mvneta_ifmedia, ifm_target);
		if_link_state_change(sc->ifp, LINK_STATE_UP);

		if (mvneta_has_switch(self)) {
			if (bootverbose)
				device_printf(self, "This device is attached to a switch\n");
			child = device_add_child(sc->dev, "mdio", -1);
			if (child == NULL) {
				ether_ifdetach(sc->ifp);
				mvneta_detach(self);
				return (ENXIO);
			}
			bus_generic_attach(sc->dev);
			bus_generic_attach(child);
		}

		/* Configure MAC media */
		mvneta_update_media(sc, ifm_target);
	}

	sysctl_mvneta_init(sc);

	callout_reset(&sc->tick_ch, 0, mvneta_tick, sc);

	error = bus_setup_intr(self, sc->res[1],
	    INTR_TYPE_NET | INTR_MPSAFE, NULL, mvneta_intrs[0].handler, sc,
	    &sc->ih_cookie[0]);
	if (error) {
		device_printf(self, "could not setup %s\n",
		    mvneta_intrs[0].description);
		ether_ifdetach(sc->ifp);
		mvneta_detach(self);
		return (error);
	}

	return (0);
}