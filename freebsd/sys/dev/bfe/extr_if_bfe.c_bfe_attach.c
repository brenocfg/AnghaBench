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
struct TYPE_3__ {int /*<<< orphan*/  ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_hdrlen; int /*<<< orphan*/  if_capenable; int /*<<< orphan*/  if_capabilities; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct bfe_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
struct bfe_softc {int /*<<< orphan*/  bfe_intrhand; int /*<<< orphan*/ * bfe_irq; int /*<<< orphan*/  bfe_enaddr; int /*<<< orphan*/  bfe_phyaddr; int /*<<< orphan*/  bfe_miibus; struct ifnet* bfe_ifp; int /*<<< orphan*/ * bfe_res; int /*<<< orphan*/  bfe_dev; int /*<<< orphan*/  bfe_mtx; int /*<<< orphan*/  bfe_stat_co; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFE_LOCK (struct bfe_softc*) ; 
 int /*<<< orphan*/  BFE_TX_QLEN ; 
 int /*<<< orphan*/  BFE_UNLOCK (struct bfe_softc*) ; 
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int ENOSPC ; 
 int ENXIO ; 
 int /*<<< orphan*/  IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct bfe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bfe_chip_reset (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ bfe_dma_alloc (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_get_config (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_ifmedia_sts ; 
 int /*<<< orphan*/  bfe_ifmedia_upd ; 
 int /*<<< orphan*/  bfe_init ; 
 int /*<<< orphan*/  bfe_intr ; 
 int /*<<< orphan*/  bfe_ioctl ; 
 int /*<<< orphan*/  bfe_start ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfe_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct bfe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_bfe_stats ; 

__attribute__((used)) static int
bfe_attach(device_t dev)
{
	struct ifnet *ifp = NULL;
	struct bfe_softc *sc;
	int error = 0, rid;

	sc = device_get_softc(dev);
	mtx_init(&sc->bfe_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
			MTX_DEF);
	callout_init_mtx(&sc->bfe_stat_co, &sc->bfe_mtx, 0);

	sc->bfe_dev = dev;

	/*
	 * Map control/status registers.
	 */
	pci_enable_busmaster(dev);

	rid = PCIR_BAR(0);
	sc->bfe_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
			RF_ACTIVE);
	if (sc->bfe_res == NULL) {
		device_printf(dev, "couldn't map memory\n");
		error = ENXIO;
		goto fail;
	}

	/* Allocate interrupt */
	rid = 0;

	sc->bfe_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
			RF_SHAREABLE | RF_ACTIVE);
	if (sc->bfe_irq == NULL) {
		device_printf(dev, "couldn't map interrupt\n");
		error = ENXIO;
		goto fail;
	}

	if (bfe_dma_alloc(sc) != 0) {
		device_printf(dev, "failed to allocate DMA resources\n");
		error = ENXIO;
		goto fail;
	}

	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO,
	    "stats", CTLTYPE_INT | CTLFLAG_RW, sc, 0, sysctl_bfe_stats,
	    "I", "Statistics");

	/* Set up ifnet structure */
	ifp = sc->bfe_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "failed to if_alloc()\n");
		error = ENOSPC;
		goto fail;
	}
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = bfe_ioctl;
	ifp->if_start = bfe_start;
	ifp->if_init = bfe_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, BFE_TX_QLEN);
	ifp->if_snd.ifq_drv_maxlen = BFE_TX_QLEN;
	IFQ_SET_READY(&ifp->if_snd);

	bfe_get_config(sc);

	/* Reset the chip and turn on the PHY */
	BFE_LOCK(sc);
	bfe_chip_reset(sc);
	BFE_UNLOCK(sc);

	error = mii_attach(dev, &sc->bfe_miibus, ifp, bfe_ifmedia_upd,
	    bfe_ifmedia_sts, BMSR_DEFCAPMASK, sc->bfe_phyaddr, MII_OFFSET_ANY,
	    0);
	if (error != 0) {
		device_printf(dev, "attaching PHYs failed\n");
		goto fail;
	}

	ether_ifattach(ifp, sc->bfe_enaddr);

	/*
	 * Tell the upper layer(s) we support long frames.
	 */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);
	ifp->if_capabilities |= IFCAP_VLAN_MTU;
	ifp->if_capenable |= IFCAP_VLAN_MTU;

	/*
	 * Hook interrupt last to avoid having to lock softc
	 */
	error = bus_setup_intr(dev, sc->bfe_irq, INTR_TYPE_NET | INTR_MPSAFE,
			NULL, bfe_intr, sc, &sc->bfe_intrhand);

	if (error) {
		device_printf(dev, "couldn't set up irq\n");
		goto fail;
	}
fail:
	if (error != 0)
		bfe_detach(dev);
	return (error);
}