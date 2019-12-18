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
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_capabilities; int if_capenable; int if_hdrlen; TYPE_1__ if_snd; int /*<<< orphan*/  if_get_counter; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_init; struct et_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
struct et_softc {int sc_mem_rid; int sc_expcap; int sc_flags; int sc_irq_rid; int /*<<< orphan*/  sc_irq_handle; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_miibus; int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/  sc_timer; int /*<<< orphan*/  sc_tx_intr_nsegs; int /*<<< orphan*/  sc_rx_intr_delay; int /*<<< orphan*/  sc_rx_intr_npkts; struct ifnet* ifp; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_tick; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int) ; 
 int EM_PM_GIGEPHY_ENB ; 
 int ENOSPC ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int ET_FLAG_FASTETHER ; 
 int ET_FLAG_MSI ; 
 int ET_FLAG_PCIE ; 
 int /*<<< orphan*/  ET_PM ; 
 int ET_PM_RXCLK_GATE ; 
 int ET_PM_SYSCLK_GATE ; 
 int ET_PM_TXCLK_GATE ; 
 scalar_t__ ET_TX_NDESC ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_VLAN_MTU ; 
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
 int /*<<< orphan*/  MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 scalar_t__ PCI_PRODUCT_LUCENT_ET1310_FAST ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct et_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct et_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  et_add_sysctls (struct et_softc*) ; 
 int et_bus_config (struct et_softc*) ; 
 int /*<<< orphan*/  et_chip_attach (struct et_softc*) ; 
 int /*<<< orphan*/  et_detach (int /*<<< orphan*/ ) ; 
 int et_dma_alloc (struct et_softc*) ; 
 int /*<<< orphan*/  et_get_counter ; 
 int /*<<< orphan*/  et_get_eaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  et_ifmedia_sts ; 
 int /*<<< orphan*/  et_ifmedia_upd ; 
 int /*<<< orphan*/  et_init ; 
 int /*<<< orphan*/  et_intr ; 
 int /*<<< orphan*/  et_ioctl ; 
 int /*<<< orphan*/  et_reset (struct et_softc*) ; 
 int /*<<< orphan*/  et_rx_intr_delay ; 
 int /*<<< orphan*/  et_rx_intr_npkts ; 
 int /*<<< orphan*/  et_start ; 
 int /*<<< orphan*/  et_timer ; 
 int /*<<< orphan*/  et_tx_intr_nsegs ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ msi_disable ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_msi_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
et_attach(device_t dev)
{
	struct et_softc *sc;
	struct ifnet *ifp;
	uint8_t eaddr[ETHER_ADDR_LEN];
	uint32_t pmcfg;
	int cap, error, msic;

	sc = device_get_softc(dev);
	sc->dev = dev;
	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init_mtx(&sc->sc_tick, &sc->sc_mtx, 0);

	ifp = sc->ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "can not if_alloc()\n");
		error = ENOSPC;
		goto fail;
	}

	/*
	 * Initialize tunables
	 */
	sc->sc_rx_intr_npkts = et_rx_intr_npkts;
	sc->sc_rx_intr_delay = et_rx_intr_delay;
	sc->sc_tx_intr_nsegs = et_tx_intr_nsegs;
	sc->sc_timer = et_timer;

	/* Enable bus mastering */
	pci_enable_busmaster(dev);

	/*
	 * Allocate IO memory
	 */
	sc->sc_mem_rid = PCIR_BAR(0);
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->sc_mem_rid, RF_ACTIVE);
	if (sc->sc_mem_res == NULL) {
		device_printf(dev, "can't allocate IO memory\n");
		return (ENXIO);
	}

	msic = 0;
	if (pci_find_cap(dev, PCIY_EXPRESS, &cap) == 0) {
		sc->sc_expcap = cap;
		sc->sc_flags |= ET_FLAG_PCIE;
		msic = pci_msi_count(dev);
		if (bootverbose)
			device_printf(dev, "MSI count: %d\n", msic);
	}
	if (msic > 0 && msi_disable == 0) {
		msic = 1;
		if (pci_alloc_msi(dev, &msic) == 0) {
			if (msic == 1) {
				device_printf(dev, "Using %d MSI message\n",
				    msic);
				sc->sc_flags |= ET_FLAG_MSI;
			} else
				pci_release_msi(dev);
		}
	}

	/*
	 * Allocate IRQ
	 */
	if ((sc->sc_flags & ET_FLAG_MSI) == 0) {
		sc->sc_irq_rid = 0;
		sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
		    &sc->sc_irq_rid, RF_SHAREABLE | RF_ACTIVE);
	} else {
		sc->sc_irq_rid = 1;
		sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
		    &sc->sc_irq_rid, RF_ACTIVE);
	}
	if (sc->sc_irq_res == NULL) {
		device_printf(dev, "can't allocate irq\n");
		error = ENXIO;
		goto fail;
	}

	if (pci_get_device(dev) == PCI_PRODUCT_LUCENT_ET1310_FAST)
		sc->sc_flags |= ET_FLAG_FASTETHER;

	error = et_bus_config(sc);
	if (error)
		goto fail;

	et_get_eaddr(dev, eaddr);

	/* Take PHY out of COMA and enable clocks. */
	pmcfg = ET_PM_SYSCLK_GATE | ET_PM_TXCLK_GATE | ET_PM_RXCLK_GATE;
	if ((sc->sc_flags & ET_FLAG_FASTETHER) == 0)
		pmcfg |= EM_PM_GIGEPHY_ENB;
	CSR_WRITE_4(sc, ET_PM, pmcfg);

	et_reset(sc);

	error = et_dma_alloc(sc);
	if (error)
		goto fail;

	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_init = et_init;
	ifp->if_ioctl = et_ioctl;
	ifp->if_start = et_start;
	ifp->if_get_counter = et_get_counter;
	ifp->if_capabilities = IFCAP_TXCSUM | IFCAP_VLAN_MTU;
	ifp->if_capenable = ifp->if_capabilities;
	ifp->if_snd.ifq_drv_maxlen = ET_TX_NDESC - 1;
	IFQ_SET_MAXLEN(&ifp->if_snd, ET_TX_NDESC - 1);
	IFQ_SET_READY(&ifp->if_snd);

	et_chip_attach(sc);

	error = mii_attach(dev, &sc->sc_miibus, ifp, et_ifmedia_upd,
	    et_ifmedia_sts, BMSR_DEFCAPMASK, MII_PHY_ANY, MII_OFFSET_ANY,
	    MIIF_DOPAUSE);
	if (error) {
		device_printf(dev, "attaching PHYs failed\n");
		goto fail;
	}

	ether_ifattach(ifp, eaddr);

	/* Tell the upper layer(s) we support long frames. */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);

	error = bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, et_intr, sc, &sc->sc_irq_handle);
	if (error) {
		ether_ifdetach(ifp);
		device_printf(dev, "can't setup intr\n");
		goto fail;
	}

	et_add_sysctls(sc);

	return (0);
fail:
	et_detach(dev);
	return (error);
}