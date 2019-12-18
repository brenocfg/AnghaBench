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
typedef  int /*<<< orphan*/  u_char ;
struct vge_softc {int vge_flags; int vge_expcap; int vge_pmcap; int vge_phyaddr; int /*<<< orphan*/  vge_intrhand; int /*<<< orphan*/ * vge_irq; int /*<<< orphan*/  vge_miibus; struct ifnet* vge_ifp; int /*<<< orphan*/ * vge_res; int /*<<< orphan*/  vge_mtx; int /*<<< orphan*/  vge_watchdog; int /*<<< orphan*/  vge_dev; } ;
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_capabilities; int if_capenable; int if_hdrlen; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_hwassist; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct vge_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  CSR_CLRBIT_1 (struct vge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CSR_READ_1 (struct vge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENOSPC ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_POLLING ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_MTU ; 
 int IFCAP_WOL ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MIIF_DOPAUSE ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  VGE_CHIPCFG0 ; 
 int /*<<< orphan*/  VGE_CHIPCFG0_PACPI ; 
 int /*<<< orphan*/  VGE_CSUM_FEATURES ; 
 int /*<<< orphan*/  VGE_EECSR ; 
 int VGE_EECSR_RELOAD ; 
 int /*<<< orphan*/  VGE_EE_EADDR ; 
 int VGE_FLAG_JUMBO ; 
 int VGE_FLAG_MSI ; 
 int VGE_FLAG_PCIE ; 
 int VGE_FLAG_PMCAP ; 
 int /*<<< orphan*/  VGE_MIICFG ; 
 int VGE_MIICFG_PHYADDR ; 
 int VGE_TIMEOUT ; 
 scalar_t__ VGE_TX_DESC_CNT ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vge_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct vge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ msi_disable ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_msi_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vge_clrwol (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_detach (int /*<<< orphan*/ ) ; 
 int vge_dma_alloc (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_ifmedia_sts ; 
 int /*<<< orphan*/  vge_ifmedia_upd ; 
 int /*<<< orphan*/  vge_init ; 
 int /*<<< orphan*/  vge_intr ; 
 int /*<<< orphan*/  vge_ioctl ; 
 int /*<<< orphan*/  vge_miipoll_start (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_read_eeprom (struct vge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vge_reset (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_start ; 
 int /*<<< orphan*/  vge_sysctl_node (struct vge_softc*) ; 

__attribute__((used)) static int
vge_attach(device_t dev)
{
	u_char eaddr[ETHER_ADDR_LEN];
	struct vge_softc *sc;
	struct ifnet *ifp;
	int error = 0, cap, i, msic, rid;

	sc = device_get_softc(dev);
	sc->vge_dev = dev;

	mtx_init(&sc->vge_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init_mtx(&sc->vge_watchdog, &sc->vge_mtx, 0);

	/*
	 * Map control/status registers.
	 */
	pci_enable_busmaster(dev);

	rid = PCIR_BAR(1);
	sc->vge_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);

	if (sc->vge_res == NULL) {
		device_printf(dev, "couldn't map ports/memory\n");
		error = ENXIO;
		goto fail;
	}

	if (pci_find_cap(dev, PCIY_EXPRESS, &cap) == 0) {
		sc->vge_flags |= VGE_FLAG_PCIE;
		sc->vge_expcap = cap;
	} else
		sc->vge_flags |= VGE_FLAG_JUMBO;
	if (pci_find_cap(dev, PCIY_PMG, &cap) == 0) {
		sc->vge_flags |= VGE_FLAG_PMCAP;
		sc->vge_pmcap = cap;
	}
	rid = 0;
	msic = pci_msi_count(dev);
	if (msi_disable == 0 && msic > 0) {
		msic = 1;
		if (pci_alloc_msi(dev, &msic) == 0) {
			if (msic == 1) {
				sc->vge_flags |= VGE_FLAG_MSI;
				device_printf(dev, "Using %d MSI message\n",
				    msic);
				rid = 1;
			} else
				pci_release_msi(dev);
		}
	}

	/* Allocate interrupt */
	sc->vge_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    ((sc->vge_flags & VGE_FLAG_MSI) ? 0 : RF_SHAREABLE) | RF_ACTIVE);
	if (sc->vge_irq == NULL) {
		device_printf(dev, "couldn't map interrupt\n");
		error = ENXIO;
		goto fail;
	}

	/* Reset the adapter. */
	vge_reset(sc);
	/* Reload EEPROM. */
	CSR_WRITE_1(sc, VGE_EECSR, VGE_EECSR_RELOAD);
	for (i = 0; i < VGE_TIMEOUT; i++) {
		DELAY(5);
		if ((CSR_READ_1(sc, VGE_EECSR) & VGE_EECSR_RELOAD) == 0)
			break;
	}
	if (i == VGE_TIMEOUT)
		device_printf(dev, "EEPROM reload timed out\n");
	/*
	 * Clear PACPI as EEPROM reload will set the bit. Otherwise
	 * MAC will receive magic packet which in turn confuses
	 * controller.
	 */
	CSR_CLRBIT_1(sc, VGE_CHIPCFG0, VGE_CHIPCFG0_PACPI);

	/*
	 * Get station address from the EEPROM.
	 */
	vge_read_eeprom(sc, (caddr_t)eaddr, VGE_EE_EADDR, 3, 0);
	/*
	 * Save configured PHY address.
	 * It seems the PHY address of PCIe controllers just
	 * reflects media jump strapping status so we assume the
	 * internal PHY address of PCIe controller is at 1.
	 */
	if ((sc->vge_flags & VGE_FLAG_PCIE) != 0)
		sc->vge_phyaddr = 1;
	else
		sc->vge_phyaddr = CSR_READ_1(sc, VGE_MIICFG) &
		    VGE_MIICFG_PHYADDR;
	/* Clear WOL and take hardware from powerdown. */
	vge_clrwol(sc);
	vge_sysctl_node(sc);
	error = vge_dma_alloc(sc);
	if (error)
		goto fail;

	ifp = sc->vge_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "can not if_alloc()\n");
		error = ENOSPC;
		goto fail;
	}

	vge_miipoll_start(sc);
	/* Do MII setup */
	error = mii_attach(dev, &sc->vge_miibus, ifp, vge_ifmedia_upd,
	    vge_ifmedia_sts, BMSR_DEFCAPMASK, sc->vge_phyaddr, MII_OFFSET_ANY,
	    MIIF_DOPAUSE);
	if (error != 0) {
		device_printf(dev, "attaching PHYs failed\n");
		goto fail;
	}

	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = vge_ioctl;
	ifp->if_capabilities = IFCAP_VLAN_MTU;
	ifp->if_start = vge_start;
	ifp->if_hwassist = VGE_CSUM_FEATURES;
	ifp->if_capabilities |= IFCAP_HWCSUM | IFCAP_VLAN_HWCSUM |
	    IFCAP_VLAN_HWTAGGING;
	if ((sc->vge_flags & VGE_FLAG_PMCAP) != 0)
		ifp->if_capabilities |= IFCAP_WOL;
	ifp->if_capenable = ifp->if_capabilities;
#ifdef DEVICE_POLLING
	ifp->if_capabilities |= IFCAP_POLLING;
#endif
	ifp->if_init = vge_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, VGE_TX_DESC_CNT - 1);
	ifp->if_snd.ifq_drv_maxlen = VGE_TX_DESC_CNT - 1;
	IFQ_SET_READY(&ifp->if_snd);

	/*
	 * Call MI attach routine.
	 */
	ether_ifattach(ifp, eaddr);

	/* Tell the upper layer(s) we support long frames. */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);

	/* Hook interrupt last to avoid having to lock softc */
	error = bus_setup_intr(dev, sc->vge_irq, INTR_TYPE_NET|INTR_MPSAFE,
	    NULL, vge_intr, sc, &sc->vge_intrhand);

	if (error) {
		device_printf(dev, "couldn't set up irq\n");
		ether_ifdetach(ifp);
		goto fail;
	}

fail:
	if (error)
		vge_detach(dev);

	return (error);
}