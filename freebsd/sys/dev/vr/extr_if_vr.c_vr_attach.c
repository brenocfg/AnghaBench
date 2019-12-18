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
typedef  int uint8_t ;
struct vr_type {int vr_quirks; } ;
struct vr_softc {int vr_quirks; scalar_t__ vr_revid; int vr_res_id; int /*<<< orphan*/  vr_intrhand; int /*<<< orphan*/ * vr_irq; int /*<<< orphan*/  vr_miibus; void* vr_txthresh; int /*<<< orphan*/  vr_inttask; struct ifnet* vr_ifp; int /*<<< orphan*/ * vr_res; int /*<<< orphan*/  vr_res_type; int /*<<< orphan*/  vr_mtx; int /*<<< orphan*/  vr_stat_callout; int /*<<< orphan*/  vr_dev; } ;
struct TYPE_3__ {scalar_t__ ifq_maxlen; } ;
struct ifnet {int if_flags; int if_capabilities; int if_capenable; int if_hdrlen; int /*<<< orphan*/  if_hwassist; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct vr_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int CSR_READ_1 (struct vr_softc*,scalar_t__) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct vr_softc*,int /*<<< orphan*/ ,int) ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENOSPC ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_POLLING ; 
 int IFCAP_VLAN_MTU ; 
 int IFCAP_WOL_MAGIC ; 
 int IFCAP_WOL_UCAST ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MIIF_DOPAUSE ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 scalar_t__ REV_ID_VT6102_A ; 
 scalar_t__ REV_ID_VT6105M_A0 ; 
 scalar_t__ REV_ID_VT6105_A0 ; 
 scalar_t__ REV_ID_VT6105_LOM ; 
 scalar_t__ REV_ID_VT6107_A1 ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct vr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vr_softc*) ; 
 int /*<<< orphan*/  VR_CLRBIT (struct vr_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VR_CSUM_FEATURES ; 
 scalar_t__ VR_EECSR ; 
 int VR_EECSR_LOAD ; 
 int /*<<< orphan*/  VR_IMR ; 
 int /*<<< orphan*/  VR_ISR ; 
 int /*<<< orphan*/  VR_MIICMD ; 
 int VR_MIICMD_AUTOPOLL ; 
 int /*<<< orphan*/  VR_MII_IMR ; 
 int VR_MODE2_MODE10T ; 
 int VR_MODE2_MRDPL ; 
 int VR_MODE2_PCEROPT ; 
 int VR_MODE3_MIION ; 
 scalar_t__ VR_PAR0 ; 
 int /*<<< orphan*/  VR_PCI_MODE2 ; 
 int /*<<< orphan*/  VR_PCI_MODE3 ; 
 scalar_t__ VR_PHYADDR ; 
 int VR_PHYADDR_MASK ; 
 int VR_Q_CSUM ; 
 int /*<<< orphan*/  VR_SETBIT (struct vr_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  VR_STICKHW ; 
 int VR_STICKHW_DS0 ; 
 int VR_STICKHW_DS1 ; 
 int VR_TIMEOUT ; 
 void* VR_TXTHRESH_MAX ; 
 void* VR_TXTHRESH_MIN ; 
 scalar_t__ VR_TX_RING_CNT ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vr_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct vr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int*) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_get_revid (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vr_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ vr_dma_alloc (struct vr_softc*) ; 
 int /*<<< orphan*/  vr_ifmedia_sts ; 
 int /*<<< orphan*/  vr_ifmedia_upd ; 
 int /*<<< orphan*/  vr_init ; 
 int /*<<< orphan*/  vr_int_task ; 
 int /*<<< orphan*/  vr_intr ; 
 int /*<<< orphan*/  vr_ioctl ; 
 struct vr_type* vr_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vr_reset (struct vr_softc*) ; 
 int /*<<< orphan*/  vr_start ; 
 int /*<<< orphan*/  vr_sysctl_stats ; 

__attribute__((used)) static int
vr_attach(device_t dev)
{
	struct vr_softc		*sc;
	struct ifnet		*ifp;
	const struct vr_type	*t;
	uint8_t			eaddr[ETHER_ADDR_LEN];
	int			error, rid;
	int			i, phy, pmc;

	sc = device_get_softc(dev);
	sc->vr_dev = dev;
	t = vr_match(dev);
	KASSERT(t != NULL, ("Lost if_vr device match"));
	sc->vr_quirks = t->vr_quirks;
	device_printf(dev, "Quirks: 0x%x\n", sc->vr_quirks);

	mtx_init(&sc->vr_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init_mtx(&sc->vr_stat_callout, &sc->vr_mtx, 0);
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
	    OID_AUTO, "stats", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
	    vr_sysctl_stats, "I", "Statistics");

	error = 0;

	/*
	 * Map control/status registers.
	 */
	pci_enable_busmaster(dev);
	sc->vr_revid = pci_get_revid(dev);
	device_printf(dev, "Revision: 0x%x\n", sc->vr_revid);

	sc->vr_res_id = PCIR_BAR(0);
	sc->vr_res_type = SYS_RES_IOPORT;
	sc->vr_res = bus_alloc_resource_any(dev, sc->vr_res_type,
	    &sc->vr_res_id, RF_ACTIVE);
	if (sc->vr_res == NULL) {
		device_printf(dev, "couldn't map ports\n");
		error = ENXIO;
		goto fail;
	}

	/* Allocate interrupt. */
	rid = 0;
	sc->vr_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE);

	if (sc->vr_irq == NULL) {
		device_printf(dev, "couldn't map interrupt\n");
		error = ENXIO;
		goto fail;
	}

	/* Allocate ifnet structure. */
	ifp = sc->vr_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "couldn't allocate ifnet structure\n");
		error = ENOSPC;
		goto fail;
	}
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = vr_ioctl;
	ifp->if_start = vr_start;
	ifp->if_init = vr_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, VR_TX_RING_CNT - 1);
	ifp->if_snd.ifq_maxlen = VR_TX_RING_CNT - 1;
	IFQ_SET_READY(&ifp->if_snd);

	TASK_INIT(&sc->vr_inttask, 0, vr_int_task, sc);

	/* Configure Tx FIFO threshold. */
	sc->vr_txthresh = VR_TXTHRESH_MIN;
	if (sc->vr_revid < REV_ID_VT6105_A0) {
		/*
		 * Use store and forward mode for Rhine I/II.
		 * Otherwise they produce a lot of Tx underruns and
		 * it would take a while to get working FIFO threshold
		 * value.
		 */
		sc->vr_txthresh = VR_TXTHRESH_MAX;
	}
	if ((sc->vr_quirks & VR_Q_CSUM) != 0) {
		ifp->if_hwassist = VR_CSUM_FEATURES;
		ifp->if_capabilities |= IFCAP_HWCSUM;
		/*
		 * To update checksum field the hardware may need to
		 * store entire frames into FIFO before transmitting.
		 */
		sc->vr_txthresh = VR_TXTHRESH_MAX;
	}

	if (sc->vr_revid >= REV_ID_VT6102_A &&
	    pci_find_cap(dev, PCIY_PMG, &pmc) == 0)
		ifp->if_capabilities |= IFCAP_WOL_UCAST | IFCAP_WOL_MAGIC;

	/* Rhine supports oversized VLAN frame. */
	ifp->if_capabilities |= IFCAP_VLAN_MTU;
	ifp->if_capenable = ifp->if_capabilities;
#ifdef DEVICE_POLLING
	ifp->if_capabilities |= IFCAP_POLLING;
#endif

	/*
	 * Windows may put the chip in suspend mode when it
	 * shuts down. Be sure to kick it in the head to wake it
	 * up again.
	 */
	if (pci_find_cap(dev, PCIY_PMG, &pmc) == 0)
		VR_CLRBIT(sc, VR_STICKHW, (VR_STICKHW_DS0|VR_STICKHW_DS1));

	/*
	 * Get station address. The way the Rhine chips work,
	 * you're not allowed to directly access the EEPROM once
	 * they've been programmed a special way. Consequently,
	 * we need to read the node address from the PAR0 and PAR1
	 * registers.
	 * Reloading EEPROM also overwrites VR_CFGA, VR_CFGB,
	 * VR_CFGC and VR_CFGD such that memory mapped IO configured
	 * by driver is reset to default state.
	 */
	VR_SETBIT(sc, VR_EECSR, VR_EECSR_LOAD);
	for (i = VR_TIMEOUT; i > 0; i--) {
		DELAY(1);
		if ((CSR_READ_1(sc, VR_EECSR) & VR_EECSR_LOAD) == 0)
			break;
	}
	if (i == 0)
		device_printf(dev, "Reloading EEPROM timeout!\n");
	for (i = 0; i < ETHER_ADDR_LEN; i++)
		eaddr[i] = CSR_READ_1(sc, VR_PAR0 + i);

	/* Reset the adapter. */
	vr_reset(sc);
	/* Ack intr & disable further interrupts. */
	CSR_WRITE_2(sc, VR_ISR, 0xFFFF);
	CSR_WRITE_2(sc, VR_IMR, 0);
	if (sc->vr_revid >= REV_ID_VT6102_A)
		CSR_WRITE_2(sc, VR_MII_IMR, 0);

	if (sc->vr_revid < REV_ID_VT6102_A) {
		pci_write_config(dev, VR_PCI_MODE2,
		    pci_read_config(dev, VR_PCI_MODE2, 1) |
		    VR_MODE2_MODE10T, 1);
	} else {
		/* Report error instead of retrying forever. */
		pci_write_config(dev, VR_PCI_MODE2,
		    pci_read_config(dev, VR_PCI_MODE2, 1) |
		    VR_MODE2_PCEROPT, 1);
        	/* Detect MII coding error. */
		pci_write_config(dev, VR_PCI_MODE3,
		    pci_read_config(dev, VR_PCI_MODE3, 1) |
		    VR_MODE3_MIION, 1);
		if (sc->vr_revid >= REV_ID_VT6105_LOM &&
		    sc->vr_revid < REV_ID_VT6105M_A0)
			pci_write_config(dev, VR_PCI_MODE2,
			    pci_read_config(dev, VR_PCI_MODE2, 1) |
			    VR_MODE2_MODE10T, 1);
		/* Enable Memory-Read-Multiple. */
		if (sc->vr_revid >= REV_ID_VT6107_A1 &&
		    sc->vr_revid < REV_ID_VT6105M_A0)
			pci_write_config(dev, VR_PCI_MODE2,
			    pci_read_config(dev, VR_PCI_MODE2, 1) |
			    VR_MODE2_MRDPL, 1);
	}
	/* Disable MII AUTOPOLL. */
	VR_CLRBIT(sc, VR_MIICMD, VR_MIICMD_AUTOPOLL);

	if (vr_dma_alloc(sc) != 0) {
		error = ENXIO;
		goto fail;
	}

	/* Do MII setup. */
	if (sc->vr_revid >= REV_ID_VT6105_A0)
		phy = 1;
	else
		phy = CSR_READ_1(sc, VR_PHYADDR) & VR_PHYADDR_MASK;
	error = mii_attach(dev, &sc->vr_miibus, ifp, vr_ifmedia_upd,
	    vr_ifmedia_sts, BMSR_DEFCAPMASK, phy, MII_OFFSET_ANY,
	    sc->vr_revid >= REV_ID_VT6102_A ? MIIF_DOPAUSE : 0);
	if (error != 0) {
		device_printf(dev, "attaching PHYs failed\n");
		goto fail;
	}

	/* Call MI attach routine. */
	ether_ifattach(ifp, eaddr);
	/*
	 * Tell the upper layer(s) we support long frames.
	 * Must appear after the call to ether_ifattach() because
	 * ether_ifattach() sets ifi_hdrlen to the default value.
	 */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);

	/* Hook interrupt last to avoid having to lock softc. */
	error = bus_setup_intr(dev, sc->vr_irq, INTR_TYPE_NET | INTR_MPSAFE,
	    vr_intr, NULL, sc, &sc->vr_intrhand);

	if (error) {
		device_printf(dev, "couldn't set up irq\n");
		ether_ifdetach(ifp);
		goto fail;
	}

fail:
	if (error)
		vr_detach(dev);

	return (error);
}