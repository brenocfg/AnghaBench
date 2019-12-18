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
typedef  int /*<<< orphan*/  u_char ;
struct cgem_softc {int rxhangwar; int /*<<< orphan*/  intrhand; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  tick_ch; int /*<<< orphan*/  miibus; int /*<<< orphan*/  rxbufs; int /*<<< orphan*/  if_old_flags; int /*<<< orphan*/ * ifp; int /*<<< orphan*/ * mem_res; scalar_t__ ref_clk_num; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/ * if_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cell ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  CGEM_LOCK (struct cgem_softc*) ; 
 int /*<<< orphan*/  CGEM_LOCK_INIT (struct cgem_softc*) ; 
 int /*<<< orphan*/  CGEM_NUM_TX_DESCS ; 
 int /*<<< orphan*/  CGEM_UNLOCK (struct cgem_softc*) ; 
 int /*<<< orphan*/  DEFAULT_NUM_RX_BUFS ; 
 int ENOMEM ; 
 int ETHER_ADDR_LEN ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_HWCSUM_IPV6 ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  IF_CGEM_NAME ; 
 int INTR_EXCL ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MII_PHY_ANY ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cgem_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgem_add_sysctls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgem_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgem_get_mac (struct cgem_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgem_ifmedia_sts ; 
 int /*<<< orphan*/  cgem_ifmedia_upd ; 
 int /*<<< orphan*/  cgem_init ; 
 int /*<<< orphan*/  cgem_intr ; 
 int /*<<< orphan*/  cgem_ioctl ; 
 int /*<<< orphan*/  cgem_reset (struct cgem_softc*) ; 
 int cgem_setup_descs (struct cgem_softc*) ; 
 int /*<<< orphan*/  cgem_start ; 
 struct cgem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifattach (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ *) ; 
 scalar_t__ fdt32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * if_alloc (int /*<<< orphan*/ ) ; 
 int if_getcapabilities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_getflags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_initname (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapabilitiesbit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapenable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_setflags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_sethwassist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setinitfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setioctlfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setsendqlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setsendqready (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_setsoftc (int /*<<< orphan*/ *,struct cgem_softc*) ; 
 int /*<<< orphan*/  if_setstartfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cgem_attach(device_t dev)
{
	struct cgem_softc *sc = device_get_softc(dev);
	if_t ifp = NULL;
	phandle_t node;
	pcell_t cell;
	int rid, err;
	u_char eaddr[ETHER_ADDR_LEN];

	sc->dev = dev;
	CGEM_LOCK_INIT(sc);

	/* Get reference clock number and base divider from fdt. */
	node = ofw_bus_get_node(dev);
	sc->ref_clk_num = 0;
	if (OF_getprop(node, "ref-clock-num", &cell, sizeof(cell)) > 0)
		sc->ref_clk_num = fdt32_to_cpu(cell);

	/* Get memory resource. */
	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
					     RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "could not allocate memory resources.\n");
		return (ENOMEM);
	}

	/* Get IRQ resource. */
	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
					     RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "could not allocate interrupt resource.\n");
		cgem_detach(dev);
		return (ENOMEM);
	}

	/* Set up ifnet structure. */
	ifp = sc->ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "could not allocate ifnet structure\n");
		cgem_detach(dev);
		return (ENOMEM);
	}
	if_setsoftc(ifp, sc);
	if_initname(ifp, IF_CGEM_NAME, device_get_unit(dev));
	if_setflags(ifp, IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST);
	if_setinitfn(ifp, cgem_init);
	if_setioctlfn(ifp, cgem_ioctl);
	if_setstartfn(ifp, cgem_start);
	if_setcapabilitiesbit(ifp, IFCAP_HWCSUM | IFCAP_HWCSUM_IPV6 |
			      IFCAP_VLAN_MTU | IFCAP_VLAN_HWCSUM, 0);
	if_setsendqlen(ifp, CGEM_NUM_TX_DESCS);
	if_setsendqready(ifp);

	/* Disable hardware checksumming by default. */
	if_sethwassist(ifp, 0);
	if_setcapenable(ifp, if_getcapabilities(ifp) &
		~(IFCAP_HWCSUM | IFCAP_HWCSUM_IPV6 | IFCAP_VLAN_HWCSUM));

	sc->if_old_flags = if_getflags(ifp);
	sc->rxbufs = DEFAULT_NUM_RX_BUFS;
	sc->rxhangwar = 1;

	/* Reset hardware. */
	CGEM_LOCK(sc);
	cgem_reset(sc);
	CGEM_UNLOCK(sc);

	/* Attach phy to mii bus. */
	err = mii_attach(dev, &sc->miibus, ifp,
			 cgem_ifmedia_upd, cgem_ifmedia_sts,
			 BMSR_DEFCAPMASK, MII_PHY_ANY, MII_OFFSET_ANY, 0);
	if (err) {
		device_printf(dev, "attaching PHYs failed\n");
		cgem_detach(dev);
		return (err);
	}

	/* Set up TX and RX descriptor area. */
	err = cgem_setup_descs(sc);
	if (err) {
		device_printf(dev, "could not set up dma mem for descs.\n");
		cgem_detach(dev);
		return (ENOMEM);
	}

	/* Get a MAC address. */
	cgem_get_mac(sc, eaddr);

	/* Start ticks. */
	callout_init_mtx(&sc->tick_ch, &sc->sc_mtx, 0);

	ether_ifattach(ifp, eaddr);

	err = bus_setup_intr(dev, sc->irq_res, INTR_TYPE_NET | INTR_MPSAFE |
			     INTR_EXCL, NULL, cgem_intr, sc, &sc->intrhand);
	if (err) {
		device_printf(dev, "could not set interrupt handler.\n");
		ether_ifdetach(ifp);
		cgem_detach(dev);
		return (err);
	}

	cgem_add_sysctls(dev);

	return (0);
}