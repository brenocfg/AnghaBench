#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct mii_softc {int /*<<< orphan*/  mii_phy; } ;
struct mge_softc {int phy_attached; int switch_attached; int rx_ic_time; int tx_ic_time; int mge_intr_cnt; int /*<<< orphan*/ * ih_cookie; int /*<<< orphan*/ * res; int /*<<< orphan*/  mge_ifmedia; TYPE_1__* mii; int /*<<< orphan*/  miibus; struct ifnet* ifp; int /*<<< orphan*/  wd_callout; scalar_t__ mge_hw_csum; scalar_t__ tx_desc_used_count; scalar_t__ tx_desc_used_idx; scalar_t__ rx_desc_curr; scalar_t__ tx_desc_curr; int /*<<< orphan*/  receive_lock; int /*<<< orphan*/  transmit_lock; int /*<<< orphan*/  node; struct mge_softc* phy_sc; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; TYPE_3__ if_snd; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; int /*<<< orphan*/  if_hwassist; struct mge_softc* if_softc; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int /*<<< orphan*/  description; int /*<<< orphan*/ * handler; } ;
struct TYPE_5__ {int /*<<< orphan*/  mii_phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int ENOMEM ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFCAP_HWCSUM ; 
 int /*<<< orphan*/  IFCAP_POLLING ; 
 int /*<<< orphan*/  IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_1000_T ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_3__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 struct mii_softc* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MGE_CHECKSUM_FEATURES ; 
 int /*<<< orphan*/  MGE_REG_PHYDEV ; 
 int /*<<< orphan*/  MGE_SWITCH_PHYDEV ; 
 scalar_t__ MGE_TX_DESC_NUM ; 
 int /*<<< orphan*/  MGE_WRITE (struct mge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mge_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 scalar_t__ fdt_find_compatible (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ fdt_get_phyaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,void**) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mge_add_sysctls (struct mge_softc*) ; 
 int mge_allocate_dma (struct mge_softc*) ; 
 int /*<<< orphan*/  mge_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mge_get_mac_address (struct mge_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mge_ifmedia_sts ; 
 int /*<<< orphan*/  mge_ifmedia_upd ; 
 int /*<<< orphan*/  mge_init ; 
 TYPE_2__* mge_intrs ; 
 int /*<<< orphan*/  mge_ioctl ; 
 int /*<<< orphan*/  mge_start ; 
 int /*<<< orphan*/  mge_ver_params (struct mge_softc*) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_spec ; 
 int switch_attached ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sx_smi ; 

__attribute__((used)) static int
mge_attach(device_t dev)
{
	struct mge_softc *sc;
	struct mii_softc *miisc;
	struct ifnet *ifp;
	uint8_t hwaddr[ETHER_ADDR_LEN];
	int i, error, phy;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->node = ofw_bus_get_node(dev);
	phy = 0;

	if (fdt_get_phyaddr(sc->node, sc->dev, &phy, (void **)&sc->phy_sc) == 0) {
		device_printf(dev, "PHY%i attached, phy_sc points to %s\n", phy,
		    device_get_nameunit(sc->phy_sc->dev));
		sc->phy_attached = 1;
	} else {
		device_printf(dev, "PHY not attached.\n");
		sc->phy_attached = 0;
		sc->phy_sc = sc;
	}

	if (fdt_find_compatible(sc->node, "mrvl,sw", 1) != 0) {
		device_printf(dev, "Switch attached.\n");
		sc->switch_attached = 1;
		/* additional variable available across instances */
		switch_attached = 1;
	} else {
		sc->switch_attached = 0;
	}

	if (device_get_unit(dev) == 0) {
		sx_init(&sx_smi, "mge_tick() SMI access threads interlock");
	}

	/* Set chip version-dependent parameters */
	mge_ver_params(sc);

	/* Initialize mutexes */
	mtx_init(&sc->transmit_lock, device_get_nameunit(dev), "mge TX lock",
	    MTX_DEF);
	mtx_init(&sc->receive_lock, device_get_nameunit(dev), "mge RX lock",
	    MTX_DEF);

	/* Allocate IO and IRQ resources */
	error = bus_alloc_resources(dev, res_spec, sc->res);
	if (error) {
		device_printf(dev, "could not allocate resources\n");
		mge_detach(dev);
		return (ENXIO);
	}

	/* Allocate DMA, buffers, buffer descriptors */
	error = mge_allocate_dma(sc);
	if (error) {
		mge_detach(dev);
		return (ENXIO);
	}

	sc->tx_desc_curr = 0;
	sc->rx_desc_curr = 0;
	sc->tx_desc_used_idx = 0;
	sc->tx_desc_used_count = 0;

	/* Configure defaults for interrupts coalescing */
	sc->rx_ic_time = 768;
	sc->tx_ic_time = 768;
	mge_add_sysctls(sc);

	/* Allocate network interface */
	ifp = sc->ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "if_alloc() failed\n");
		mge_detach(dev);
		return (ENOMEM);
	}

	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_softc = sc;
	ifp->if_flags = IFF_SIMPLEX | IFF_MULTICAST | IFF_BROADCAST;
	ifp->if_capabilities = IFCAP_VLAN_MTU;
	if (sc->mge_hw_csum) {
		ifp->if_capabilities |= IFCAP_HWCSUM;
		ifp->if_hwassist = MGE_CHECKSUM_FEATURES;
	}
	ifp->if_capenable = ifp->if_capabilities;

#ifdef DEVICE_POLLING
	/* Advertise that polling is supported */
	ifp->if_capabilities |= IFCAP_POLLING;
#endif

	ifp->if_init = mge_init;
	ifp->if_start = mge_start;
	ifp->if_ioctl = mge_ioctl;

	ifp->if_snd.ifq_drv_maxlen = MGE_TX_DESC_NUM - 1;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifp->if_snd.ifq_drv_maxlen);
	IFQ_SET_READY(&ifp->if_snd);

	mge_get_mac_address(sc, hwaddr);
	ether_ifattach(ifp, hwaddr);
	callout_init(&sc->wd_callout, 0);

	/* Attach PHY(s) */
	if (sc->phy_attached) {
		error = mii_attach(dev, &sc->miibus, ifp, mge_ifmedia_upd,
		    mge_ifmedia_sts, BMSR_DEFCAPMASK, phy, MII_OFFSET_ANY, 0);
		if (error) {
			device_printf(dev, "MII failed to find PHY\n");
			if_free(ifp);
			sc->ifp = NULL;
			mge_detach(dev);
			return (error);
		}
		sc->mii = device_get_softc(sc->miibus);

		/* Tell the MAC where to find the PHY so autoneg works */
		miisc = LIST_FIRST(&sc->mii->mii_phys);
		MGE_WRITE(sc, MGE_REG_PHYDEV, miisc->mii_phy);
	} else {
		/* no PHY, so use hard-coded values */
		ifmedia_init(&sc->mge_ifmedia, 0,
		    mge_ifmedia_upd,
		    mge_ifmedia_sts);
		ifmedia_add(&sc->mge_ifmedia,
		    IFM_ETHER | IFM_1000_T | IFM_FDX,
		    0, NULL);
		ifmedia_set(&sc->mge_ifmedia,
		    IFM_ETHER | IFM_1000_T | IFM_FDX);
	}

	/* Attach interrupt handlers */
	/* TODO: review flags, in part. mark RX as INTR_ENTROPY ? */
	for (i = 1; i <= sc->mge_intr_cnt; ++i) {
		error = bus_setup_intr(dev, sc->res[i],
		    INTR_TYPE_NET | INTR_MPSAFE,
		    NULL, *mge_intrs[(sc->mge_intr_cnt == 1 ? 0 : i)].handler,
		    sc, &sc->ih_cookie[i - 1]);
		if (error) {
			device_printf(dev, "could not setup %s\n",
			    mge_intrs[(sc->mge_intr_cnt == 1 ? 0 : i)].description);
			mge_detach(dev);
			return (error);
		}
	}

	if (sc->switch_attached) {
		device_t child;
		MGE_WRITE(sc, MGE_REG_PHYDEV, MGE_SWITCH_PHYDEV);
		child = device_add_child(dev, "mdio", -1);
		bus_generic_attach(dev);
	}

	return (0);
}