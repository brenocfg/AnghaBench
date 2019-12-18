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
typedef  int /*<<< orphan*/  uint16_t ;
struct ste_softc {int ste_flags; int ste_res_id; int /*<<< orphan*/  ste_intrhand; int /*<<< orphan*/ * ste_irq; int /*<<< orphan*/  ste_tx_thresh; int /*<<< orphan*/  ste_miibus; struct ifnet* ste_ifp; int /*<<< orphan*/  ste_mtx; int /*<<< orphan*/  ste_callout; int /*<<< orphan*/ * ste_res; int /*<<< orphan*/  ste_res_type; int /*<<< orphan*/  ste_dev; } ;
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_hdrlen; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct ste_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 scalar_t__ DL_DEVICEID_DL10050 ; 
 scalar_t__ DL_VENDORID ; 
 int ENOSPC ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFCAP_POLLING ; 
 int /*<<< orphan*/  IFCAP_VLAN_MTU ; 
 int /*<<< orphan*/  IFCAP_WOL_MAGIC ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 void* PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  STE_EEADDR_NODE0 ; 
 int STE_FLAG_ONE_PHY ; 
 int /*<<< orphan*/  STE_TXSTART_THRESH ; 
 scalar_t__ STE_TX_LIST_CNT ; 
 scalar_t__ ST_DEVICEID_ST201_1 ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ste_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ste_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_revid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  ste_detach (int /*<<< orphan*/ ) ; 
 int ste_dma_alloc (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_ifmedia_sts ; 
 int /*<<< orphan*/  ste_ifmedia_upd ; 
 int /*<<< orphan*/  ste_init ; 
 int /*<<< orphan*/  ste_intr ; 
 int /*<<< orphan*/  ste_ioctl ; 
 scalar_t__ ste_read_eeprom (struct ste_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ste_reset (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_start ; 
 int /*<<< orphan*/  ste_sysctl_node (struct ste_softc*) ; 

__attribute__((used)) static int
ste_attach(device_t dev)
{
	struct ste_softc *sc;
	struct ifnet *ifp;
	uint16_t eaddr[ETHER_ADDR_LEN / 2];
	int error = 0, phy, pmc, prefer_iomap, rid;

	sc = device_get_softc(dev);
	sc->ste_dev = dev;

	/*
	 * Only use one PHY since this chip reports multiple
	 * Note on the DFE-550 the PHY is at 1 on the DFE-580
	 * it is at 0 & 1.  It is rev 0x12.
	 */
	if (pci_get_vendor(dev) == DL_VENDORID &&
	    pci_get_device(dev) == DL_DEVICEID_DL10050 &&
	    pci_get_revid(dev) == 0x12 )
		sc->ste_flags |= STE_FLAG_ONE_PHY;

	mtx_init(&sc->ste_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	/*
	 * Map control/status registers.
	 */
	pci_enable_busmaster(dev);

	/*
	 * Prefer memory space register mapping over IO space but use
	 * IO space for a device that is known to have issues on memory
	 * mapping.
	 */
	prefer_iomap = 0;
	if (pci_get_device(dev) == ST_DEVICEID_ST201_1)
		prefer_iomap = 1;
	else
		resource_int_value(device_get_name(sc->ste_dev),
		    device_get_unit(sc->ste_dev), "prefer_iomap",
		    &prefer_iomap);
	if (prefer_iomap == 0) {
		sc->ste_res_id = PCIR_BAR(1);
		sc->ste_res_type = SYS_RES_MEMORY;
		sc->ste_res = bus_alloc_resource_any(dev, sc->ste_res_type,
		    &sc->ste_res_id, RF_ACTIVE);
	}
	if (prefer_iomap || sc->ste_res == NULL) {
		sc->ste_res_id = PCIR_BAR(0);
		sc->ste_res_type = SYS_RES_IOPORT;
		sc->ste_res = bus_alloc_resource_any(dev, sc->ste_res_type,
		    &sc->ste_res_id, RF_ACTIVE);
	}
	if (sc->ste_res == NULL) {
		device_printf(dev, "couldn't map ports/memory\n");
		error = ENXIO;
		goto fail;
	}

	/* Allocate interrupt */
	rid = 0;
	sc->ste_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE);

	if (sc->ste_irq == NULL) {
		device_printf(dev, "couldn't map interrupt\n");
		error = ENXIO;
		goto fail;
	}

	callout_init_mtx(&sc->ste_callout, &sc->ste_mtx, 0);

	/* Reset the adapter. */
	ste_reset(sc);

	/*
	 * Get station address from the EEPROM.
	 */
	if (ste_read_eeprom(sc, eaddr, STE_EEADDR_NODE0, ETHER_ADDR_LEN / 2)) {
		device_printf(dev, "failed to read station address\n");
		error = ENXIO;
		goto fail;
	}
	ste_sysctl_node(sc);

	if ((error = ste_dma_alloc(sc)) != 0)
		goto fail;

	ifp = sc->ste_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "can not if_alloc()\n");
		error = ENOSPC;
		goto fail;
	}

	/* Do MII setup. */
	phy = MII_PHY_ANY;
	if ((sc->ste_flags & STE_FLAG_ONE_PHY) != 0)
		phy = 0;
	error = mii_attach(dev, &sc->ste_miibus, ifp, ste_ifmedia_upd,
		ste_ifmedia_sts, BMSR_DEFCAPMASK, phy, MII_OFFSET_ANY, 0);
	if (error != 0) {
		device_printf(dev, "attaching PHYs failed\n");
		goto fail;
	}

	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = ste_ioctl;
	ifp->if_start = ste_start;
	ifp->if_init = ste_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, STE_TX_LIST_CNT - 1);
	ifp->if_snd.ifq_drv_maxlen = STE_TX_LIST_CNT - 1;
	IFQ_SET_READY(&ifp->if_snd);

	sc->ste_tx_thresh = STE_TXSTART_THRESH;

	/*
	 * Call MI attach routine.
	 */
	ether_ifattach(ifp, (uint8_t *)eaddr);

	/*
	 * Tell the upper layer(s) we support long frames.
	 */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);
	ifp->if_capabilities |= IFCAP_VLAN_MTU;
	if (pci_find_cap(dev, PCIY_PMG, &pmc) == 0)
		ifp->if_capabilities |= IFCAP_WOL_MAGIC;
	ifp->if_capenable = ifp->if_capabilities;
#ifdef DEVICE_POLLING
	ifp->if_capabilities |= IFCAP_POLLING;
#endif

	/* Hook interrupt last to avoid having to lock softc */
	error = bus_setup_intr(dev, sc->ste_irq, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, ste_intr, sc, &sc->ste_intrhand);

	if (error) {
		device_printf(dev, "couldn't set up irq\n");
		ether_ifdetach(ifp);
		goto fail;
	}

fail:
	if (error)
		ste_detach(dev);

	return (error);
}