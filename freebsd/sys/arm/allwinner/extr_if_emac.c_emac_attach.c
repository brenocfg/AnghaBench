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
typedef  int /*<<< orphan*/  uint8_t ;
struct ifnet {int if_flags; int if_hdrlen; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; struct emac_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
struct emac_softc {scalar_t__ emac_rx_process_limit; int /*<<< orphan*/  emac_intrhand; int /*<<< orphan*/ * emac_irq; int /*<<< orphan*/  emac_miibus; struct ifnet* emac_ifp; int /*<<< orphan*/ * emac_res; int /*<<< orphan*/  emac_handle; int /*<<< orphan*/  emac_tag; int /*<<< orphan*/  emac_mtx; int /*<<< orphan*/  emac_tick_ch; int /*<<< orphan*/  emac_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 void* EMAC_PROC_DEFAULT ; 
 scalar_t__ EMAC_PROC_MAX ; 
 scalar_t__ EMAC_PROC_MIN ; 
 int ENOSPC ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_MAXLEN ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct emac_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct emac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  emac_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_get_hwaddr (struct emac_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emac_ifmedia_sts ; 
 int /*<<< orphan*/  emac_ifmedia_upd ; 
 int /*<<< orphan*/  emac_init ; 
 int /*<<< orphan*/  emac_intr ; 
 int /*<<< orphan*/  emac_ioctl ; 
 int /*<<< orphan*/  emac_reset (struct emac_softc*) ; 
 int /*<<< orphan*/  emac_start ; 
 int emac_sys_setup (struct emac_softc*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_hw_emac_proc_limit ; 

__attribute__((used)) static int
emac_attach(device_t dev)
{
	struct emac_softc *sc;
	struct ifnet *ifp;
	int error, rid;
	uint8_t eaddr[ETHER_ADDR_LEN];

	sc = device_get_softc(dev);
	sc->emac_dev = dev;

	error = 0;
	mtx_init(&sc->emac_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init_mtx(&sc->emac_tick_ch, &sc->emac_mtx, 0);

	rid = 0;
	sc->emac_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->emac_res == NULL) {
		device_printf(dev, "unable to map memory\n");
		error = ENXIO;
		goto fail;
	}

	sc->emac_tag = rman_get_bustag(sc->emac_res);
	sc->emac_handle = rman_get_bushandle(sc->emac_res);

	rid = 0;
	sc->emac_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE);
	if (sc->emac_irq == NULL) {
		device_printf(dev, "cannot allocate IRQ resources.\n");
		error = ENXIO;
		goto fail;
	}
	/* Create device sysctl node. */
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
	    OID_AUTO, "process_limit", CTLTYPE_INT | CTLFLAG_RW,
	    &sc->emac_rx_process_limit, 0, sysctl_hw_emac_proc_limit, "I",
	    "max number of Rx events to process");

	sc->emac_rx_process_limit = EMAC_PROC_DEFAULT;
	error = resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "process_limit", &sc->emac_rx_process_limit);
	if (error == 0) {
		if (sc->emac_rx_process_limit < EMAC_PROC_MIN ||
		    sc->emac_rx_process_limit > EMAC_PROC_MAX) {
			device_printf(dev, "process_limit value out of range; "
			    "using default: %d\n", EMAC_PROC_DEFAULT);
			sc->emac_rx_process_limit = EMAC_PROC_DEFAULT;
		}
	}
	/* Setup EMAC */
	error = emac_sys_setup(sc);
	if (error != 0)
		goto fail;

	emac_reset(sc);

	ifp = sc->emac_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "unable to allocate ifp\n");
		error = ENOSPC;
		goto fail;
	}
	ifp->if_softc = sc;

	/* Setup MII */
	error = mii_attach(dev, &sc->emac_miibus, ifp, emac_ifmedia_upd,
	    emac_ifmedia_sts, BMSR_DEFCAPMASK, MII_PHY_ANY, MII_OFFSET_ANY, 0);
	if (error != 0) {
		device_printf(dev, "PHY probe failed\n");
		goto fail;
	}

	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_start = emac_start;
	ifp->if_ioctl = emac_ioctl;
	ifp->if_init = emac_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, IFQ_MAXLEN);

	/* Get MAC address */
	emac_get_hwaddr(sc, eaddr);
	ether_ifattach(ifp, eaddr);

	/* VLAN capability setup. */
	ifp->if_capabilities |= IFCAP_VLAN_MTU;
	ifp->if_capenable = ifp->if_capabilities;
	/* Tell the upper layer we support VLAN over-sized frames. */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);

	error = bus_setup_intr(dev, sc->emac_irq, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, emac_intr, sc, &sc->emac_intrhand);
	if (error != 0) {
		device_printf(dev, "could not set up interrupt handler.\n");
		ether_ifdetach(ifp);
		goto fail;
	}

fail:
	if (error != 0)
		emac_detach(dev);
	return (error);
}