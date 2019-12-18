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
typedef  int uint16_t ;
struct vte_softc {int vte_res_id; scalar_t__ vte_res_type; int /*<<< orphan*/  vte_intrhand; int /*<<< orphan*/ * vte_irq; int /*<<< orphan*/  vte_eaddr; int /*<<< orphan*/  vte_miibus; struct ifnet* vte_ifp; int /*<<< orphan*/  vte_mtx; int /*<<< orphan*/ * vte_res; int /*<<< orphan*/  vte_ident; int /*<<< orphan*/  vte_tick_ch; int /*<<< orphan*/  vte_dev; } ;
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_hdrlen; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; TYPE_1__ if_snd; int /*<<< orphan*/  if_get_counter; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct vte_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int CSR_READ_2 (struct vte_softc*,int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 void* PCIR_BAR (int) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 scalar_t__ SYS_RES_IOPORT ; 
 scalar_t__ SYS_RES_IRQ ; 
 scalar_t__ SYS_RES_MEMORY ; 
 int /*<<< orphan*/  VTE_MACID ; 
 int VTE_MACID_MASK ; 
 int /*<<< orphan*/  VTE_MACID_REV ; 
 int VTE_MACID_REV_MASK ; 
 int VTE_MACID_REV_SHIFT ; 
 int VTE_MACID_SHIFT ; 
 scalar_t__ VTE_TX_RING_CNT ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,scalar_t__,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vte_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct vte_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vte_detach (int /*<<< orphan*/ ) ; 
 int vte_dma_alloc (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_find_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vte_get_counter ; 
 int /*<<< orphan*/  vte_get_macaddr (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_init ; 
 int /*<<< orphan*/  vte_intr ; 
 int /*<<< orphan*/  vte_ioctl ; 
 int /*<<< orphan*/  vte_mediachange ; 
 int /*<<< orphan*/  vte_mediastatus ; 
 int /*<<< orphan*/  vte_reset (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_start ; 
 int /*<<< orphan*/  vte_sysctl_node (struct vte_softc*) ; 

__attribute__((used)) static int
vte_attach(device_t dev)
{
	struct vte_softc *sc;
	struct ifnet *ifp;
	uint16_t macid;
	int error, rid;

	error = 0;
	sc = device_get_softc(dev);
	sc->vte_dev = dev;

	mtx_init(&sc->vte_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init_mtx(&sc->vte_tick_ch, &sc->vte_mtx, 0);
	sc->vte_ident = vte_find_ident(dev);

	/* Map the device. */
	pci_enable_busmaster(dev);
	sc->vte_res_id = PCIR_BAR(1);
	sc->vte_res_type = SYS_RES_MEMORY;
	sc->vte_res = bus_alloc_resource_any(dev, sc->vte_res_type,
	    &sc->vte_res_id, RF_ACTIVE);
	if (sc->vte_res == NULL) {
		sc->vte_res_id = PCIR_BAR(0);
		sc->vte_res_type = SYS_RES_IOPORT;
		sc->vte_res = bus_alloc_resource_any(dev, sc->vte_res_type,
		    &sc->vte_res_id, RF_ACTIVE);
		if (sc->vte_res == NULL) {
			device_printf(dev, "cannot map memory/ports.\n");
			mtx_destroy(&sc->vte_mtx);
			return (ENXIO);
		}
	}
	if (bootverbose) {
		device_printf(dev, "using %s space register mapping\n",
		    sc->vte_res_type == SYS_RES_MEMORY ? "memory" : "I/O");
		device_printf(dev, "MAC Identifier : 0x%04x\n",
		    CSR_READ_2(sc, VTE_MACID));
		macid = CSR_READ_2(sc, VTE_MACID_REV);
		device_printf(dev, "MAC Id. 0x%02x, Rev. 0x%02x\n",
		    (macid & VTE_MACID_MASK) >> VTE_MACID_SHIFT,
		    (macid & VTE_MACID_REV_MASK) >> VTE_MACID_REV_SHIFT);
	}

	rid = 0;
	sc->vte_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE);
	if (sc->vte_irq == NULL) {
		device_printf(dev, "cannot allocate IRQ resources.\n");
		error = ENXIO;
		goto fail;
	}

	/* Reset the ethernet controller. */
	vte_reset(sc);

	if ((error = vte_dma_alloc(sc)) != 0)
		goto fail;

	/* Create device sysctl node. */
	vte_sysctl_node(sc);

	/* Load station address. */
	vte_get_macaddr(sc);

	ifp = sc->vte_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "cannot allocate ifnet structure.\n");
		error = ENXIO;
		goto fail;
	}

	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = vte_ioctl;
	ifp->if_start = vte_start;
	ifp->if_init = vte_init;
	ifp->if_get_counter = vte_get_counter;
	ifp->if_snd.ifq_drv_maxlen = VTE_TX_RING_CNT - 1;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifp->if_snd.ifq_drv_maxlen);
	IFQ_SET_READY(&ifp->if_snd);

	/*
	 * Set up MII bus.
	 * BIOS would have initialized VTE_MPSCCR to catch PHY
	 * status changes so driver may be able to extract
	 * configured PHY address.  Since it's common to see BIOS
	 * fails to initialize the register(including the sample
	 * board I have), let mii(4) probe it.  This is more
	 * reliable than relying on BIOS's initialization.
	 *
	 * Advertising flow control capability to mii(4) was
	 * intentionally disabled due to severe problems in TX
	 * pause frame generation.  See vte_rxeof() for more
	 * details.
	 */
	error = mii_attach(dev, &sc->vte_miibus, ifp, vte_mediachange,
	    vte_mediastatus, BMSR_DEFCAPMASK, MII_PHY_ANY, MII_OFFSET_ANY, 0);
	if (error != 0) {
		device_printf(dev, "attaching PHYs failed\n");
		goto fail;
	}

	ether_ifattach(ifp, sc->vte_eaddr);

	/* VLAN capability setup. */
	ifp->if_capabilities |= IFCAP_VLAN_MTU;
	ifp->if_capenable = ifp->if_capabilities;
	/* Tell the upper layer we support VLAN over-sized frames. */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);

	error = bus_setup_intr(dev, sc->vte_irq, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, vte_intr, sc, &sc->vte_intrhand);
	if (error != 0) {
		device_printf(dev, "could not set up interrupt handler.\n");
		ether_ifdetach(ifp);
		goto fail;
	}

fail:
	if (error != 0)
		vte_detach(dev);

	return (error);
}