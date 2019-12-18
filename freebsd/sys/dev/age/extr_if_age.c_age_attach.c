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
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_capabilities; int if_hwassist; int if_capenable; int if_hdrlen; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct age_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
struct age_softc {int age_chip_rev; int age_flags; int age_dma_rd_burst; int age_dma_wr_burst; int /*<<< orphan*/ * age_tq; int /*<<< orphan*/ * age_intrhand; int /*<<< orphan*/ * age_irq; int /*<<< orphan*/  age_dev; int /*<<< orphan*/  age_eaddr; int /*<<< orphan*/  age_phyaddr; int /*<<< orphan*/  age_miibus; struct ifnet* age_ifp; int /*<<< orphan*/  age_irq_spec; int /*<<< orphan*/  age_rev; int /*<<< orphan*/ * age_res; int /*<<< orphan*/  age_res_spec; int /*<<< orphan*/  age_link_task; int /*<<< orphan*/  age_int_task; int /*<<< orphan*/  age_mtx; int /*<<< orphan*/  age_tick_ch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AGE_CSUM_FEATURES ; 
 int AGE_FLAG_MSI ; 
 int AGE_FLAG_MSIX ; 
 int AGE_FLAG_PCIE ; 
 int AGE_FLAG_PMCAP ; 
 int /*<<< orphan*/  AGE_MASTER_CFG ; 
 int AGE_MSIX_MESSAGES ; 
 int AGE_MSI_MESSAGES ; 
 int /*<<< orphan*/  AGE_PHY_ADDR ; 
 int /*<<< orphan*/  AGE_SRAM_RX_FIFO_LEN ; 
 int /*<<< orphan*/  AGE_SRAM_TX_FIFO_LEN ; 
 scalar_t__ AGE_TX_RING_CNT ; 
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int CSR_READ_4 (struct age_softc*,int /*<<< orphan*/ ) ; 
 int CSUM_TSO ; 
 int DMA_CFG_RD_BURST_128 ; 
 int DMA_CFG_RD_BURST_SHIFT ; 
 int DMA_CFG_WR_BURST_128 ; 
 int DMA_CFG_WR_BURST_SHIFT ; 
 int ENXIO ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_TSO4 ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFCAP_VLAN_MTU ; 
 int IFCAP_WOL_MAGIC ; 
 int IFCAP_WOL_MCAST ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int MASTER_CHIP_REV_SHIFT ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct age_softc*) ; 
 int /*<<< orphan*/  age_detach (int /*<<< orphan*/ ) ; 
 int age_dma_alloc (struct age_softc*) ; 
 int /*<<< orphan*/  age_get_macaddr (struct age_softc*) ; 
 int /*<<< orphan*/  age_init ; 
 int /*<<< orphan*/  age_int_task ; 
 int /*<<< orphan*/  age_intr ; 
 int /*<<< orphan*/  age_ioctl ; 
 int /*<<< orphan*/  age_irq_spec_legacy ; 
 int /*<<< orphan*/  age_irq_spec_msi ; 
 int /*<<< orphan*/  age_irq_spec_msix ; 
 int /*<<< orphan*/  age_link_task ; 
 int /*<<< orphan*/  age_mediachange ; 
 int /*<<< orphan*/  age_mediastatus ; 
 int /*<<< orphan*/  age_phy_reset (struct age_softc*) ; 
 int /*<<< orphan*/  age_res_spec_mem ; 
 int /*<<< orphan*/  age_reset (struct age_softc*) ; 
 int /*<<< orphan*/  age_start ; 
 int /*<<< orphan*/  age_sysctl_node (struct age_softc*) ; 
 scalar_t__ bootverbose ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct age_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct age_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ msi_disable ; 
 scalar_t__ msix_disable ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_get_revid (int /*<<< orphan*/ ) ; 
 int pci_msi_count (int /*<<< orphan*/ ) ; 
 int pci_msix_count (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
age_attach(device_t dev)
{
	struct age_softc *sc;
	struct ifnet *ifp;
	uint16_t burst;
	int error, i, msic, msixc, pmc;

	error = 0;
	sc = device_get_softc(dev);
	sc->age_dev = dev;

	mtx_init(&sc->age_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init_mtx(&sc->age_tick_ch, &sc->age_mtx, 0);
	TASK_INIT(&sc->age_int_task, 0, age_int_task, sc);
	TASK_INIT(&sc->age_link_task, 0, age_link_task, sc);

	/* Map the device. */
	pci_enable_busmaster(dev);
	sc->age_res_spec = age_res_spec_mem;
	sc->age_irq_spec = age_irq_spec_legacy;
	error = bus_alloc_resources(dev, sc->age_res_spec, sc->age_res);
	if (error != 0) {
		device_printf(dev, "cannot allocate memory resources.\n");
		goto fail;
	}

	/* Set PHY address. */
	sc->age_phyaddr = AGE_PHY_ADDR;

	/* Reset PHY. */
	age_phy_reset(sc);

	/* Reset the ethernet controller. */
	age_reset(sc);

	/* Get PCI and chip id/revision. */
	sc->age_rev = pci_get_revid(dev);
	sc->age_chip_rev = CSR_READ_4(sc, AGE_MASTER_CFG) >>
	    MASTER_CHIP_REV_SHIFT;
	if (bootverbose) {
		device_printf(dev, "PCI device revision : 0x%04x\n",
		    sc->age_rev);
		device_printf(dev, "Chip id/revision : 0x%04x\n",
		    sc->age_chip_rev);
	}

	/*
	 * XXX
	 * Unintialized hardware returns an invalid chip id/revision
	 * as well as 0xFFFFFFFF for Tx/Rx fifo length. It seems that
	 * unplugged cable results in putting hardware into automatic
	 * power down mode which in turn returns invalld chip revision.
	 */
	if (sc->age_chip_rev == 0xFFFF) {
		device_printf(dev,"invalid chip revision : 0x%04x -- "
		    "not initialized?\n", sc->age_chip_rev);
		error = ENXIO;
		goto fail;
	}

	device_printf(dev, "%d Tx FIFO, %d Rx FIFO\n",
	    CSR_READ_4(sc, AGE_SRAM_TX_FIFO_LEN),
	    CSR_READ_4(sc, AGE_SRAM_RX_FIFO_LEN));

	/* Allocate IRQ resources. */
	msixc = pci_msix_count(dev);
	msic = pci_msi_count(dev);
	if (bootverbose) {
		device_printf(dev, "MSIX count : %d\n", msixc);
		device_printf(dev, "MSI count : %d\n", msic);
	}

	/* Prefer MSIX over MSI. */
	if (msix_disable == 0 || msi_disable == 0) {
		if (msix_disable == 0 && msixc == AGE_MSIX_MESSAGES &&
		    pci_alloc_msix(dev, &msixc) == 0) {
			if (msic == AGE_MSIX_MESSAGES) {
				device_printf(dev, "Using %d MSIX messages.\n",
				    msixc);
				sc->age_flags |= AGE_FLAG_MSIX;
				sc->age_irq_spec = age_irq_spec_msix;
			} else
				pci_release_msi(dev);
		}
		if (msi_disable == 0 && (sc->age_flags & AGE_FLAG_MSIX) == 0 &&
		    msic == AGE_MSI_MESSAGES &&
		    pci_alloc_msi(dev, &msic) == 0) {
			if (msic == AGE_MSI_MESSAGES) {
				device_printf(dev, "Using %d MSI messages.\n",
				    msic);
				sc->age_flags |= AGE_FLAG_MSI;
				sc->age_irq_spec = age_irq_spec_msi;
			} else
				pci_release_msi(dev);
		}
	}

	error = bus_alloc_resources(dev, sc->age_irq_spec, sc->age_irq);
	if (error != 0) {
		device_printf(dev, "cannot allocate IRQ resources.\n");
		goto fail;
	}


	/* Get DMA parameters from PCIe device control register. */
	if (pci_find_cap(dev, PCIY_EXPRESS, &i) == 0) {
		sc->age_flags |= AGE_FLAG_PCIE;
		burst = pci_read_config(dev, i + 0x08, 2);
		/* Max read request size. */
		sc->age_dma_rd_burst = ((burst >> 12) & 0x07) <<
		    DMA_CFG_RD_BURST_SHIFT;
		/* Max payload size. */
		sc->age_dma_wr_burst = ((burst >> 5) & 0x07) <<
		    DMA_CFG_WR_BURST_SHIFT;
		if (bootverbose) {
			device_printf(dev, "Read request size : %d bytes.\n",
			    128 << ((burst >> 12) & 0x07));
			device_printf(dev, "TLP payload size : %d bytes.\n",
			    128 << ((burst >> 5) & 0x07));
		}
	} else {
		sc->age_dma_rd_burst = DMA_CFG_RD_BURST_128;
		sc->age_dma_wr_burst = DMA_CFG_WR_BURST_128;
	}

	/* Create device sysctl node. */
	age_sysctl_node(sc);

	if ((error = age_dma_alloc(sc)) != 0)
		goto fail;

	/* Load station address. */
	age_get_macaddr(sc);

	ifp = sc->age_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "cannot allocate ifnet structure.\n");
		error = ENXIO;
		goto fail;
	}

	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = age_ioctl;
	ifp->if_start = age_start;
	ifp->if_init = age_init;
	ifp->if_snd.ifq_drv_maxlen = AGE_TX_RING_CNT - 1;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifp->if_snd.ifq_drv_maxlen);
	IFQ_SET_READY(&ifp->if_snd);
	ifp->if_capabilities = IFCAP_HWCSUM | IFCAP_TSO4;
	ifp->if_hwassist = AGE_CSUM_FEATURES | CSUM_TSO;
	if (pci_find_cap(dev, PCIY_PMG, &pmc) == 0) {
		sc->age_flags |= AGE_FLAG_PMCAP;
		ifp->if_capabilities |= IFCAP_WOL_MAGIC | IFCAP_WOL_MCAST;
	}
	ifp->if_capenable = ifp->if_capabilities;

	/* Set up MII bus. */
	error = mii_attach(dev, &sc->age_miibus, ifp, age_mediachange,
	    age_mediastatus, BMSR_DEFCAPMASK, sc->age_phyaddr, MII_OFFSET_ANY,
	    0);
	if (error != 0) {
		device_printf(dev, "attaching PHYs failed\n");
		goto fail;
	}

	ether_ifattach(ifp, sc->age_eaddr);

	/* VLAN capability setup. */
	ifp->if_capabilities |= IFCAP_VLAN_MTU | IFCAP_VLAN_HWTAGGING |
	    IFCAP_VLAN_HWCSUM | IFCAP_VLAN_HWTSO;
	ifp->if_capenable = ifp->if_capabilities;

	/* Tell the upper layer(s) we support long frames. */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);

	/* Create local taskq. */
	sc->age_tq = taskqueue_create_fast("age_taskq", M_WAITOK,
	    taskqueue_thread_enqueue, &sc->age_tq);
	if (sc->age_tq == NULL) {
		device_printf(dev, "could not create taskqueue.\n");
		ether_ifdetach(ifp);
		error = ENXIO;
		goto fail;
	}
	taskqueue_start_threads(&sc->age_tq, 1, PI_NET, "%s taskq",
	    device_get_nameunit(sc->age_dev));

	if ((sc->age_flags & AGE_FLAG_MSIX) != 0)
		msic = AGE_MSIX_MESSAGES;
	else if ((sc->age_flags & AGE_FLAG_MSI) != 0)
		msic = AGE_MSI_MESSAGES;
	else
		msic = 1;
	for (i = 0; i < msic; i++) {
		error = bus_setup_intr(dev, sc->age_irq[i],
		    INTR_TYPE_NET | INTR_MPSAFE, age_intr, NULL, sc,
		    &sc->age_intrhand[i]);
		if (error != 0)
			break;
	}
	if (error != 0) {
		device_printf(dev, "could not set up interrupt handler.\n");
		taskqueue_free(sc->age_tq);
		sc->age_tq = NULL;
		ether_ifdetach(ifp);
		goto fail;
	}

fail:
	if (error != 0)
		age_detach(dev);

	return (error);
}