#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct ifnet {int if_flags; scalar_t__ if_hwassist; scalar_t__ if_capenable; scalar_t__ if_capabilities; int /*<<< orphan*/  if_get_counter; int /*<<< orphan*/  if_qflush; int /*<<< orphan*/  if_transmit; int /*<<< orphan*/  if_ioctl; struct axgbe_softc* if_softc; int /*<<< orphan*/  if_init; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* phy_init ) (TYPE_3__*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  rx_q_cnt; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* exit ) (TYPE_3__*) ;} ;
struct TYPE_10__ {int advertising; } ;
struct TYPE_12__ {int pause_autoneg; int tx_pause; int rx_pause; int tx_ring_count; int tx_q_count; int rx_ring_count; int /*<<< orphan*/  dev_state; TYPE_5__ phy_if; TYPE_2__ hw_feat; int /*<<< orphan*/  rx_q_count; scalar_t__ power_down; int /*<<< orphan*/  phy_speed; void* rx_pbl; int /*<<< orphan*/  rx_threshold; int /*<<< orphan*/  rx_sf_mode; int /*<<< orphan*/  rx_desc_count; int /*<<< orphan*/  tx_osp_mode; void* tx_pbl; int /*<<< orphan*/  tx_threshold; int /*<<< orphan*/  tx_sf_mode; int /*<<< orphan*/  tx_desc_count; int /*<<< orphan*/  pblx8; TYPE_6__ hw_if; int /*<<< orphan*/  desc_if; int /*<<< orphan*/  dev_workqueue; int /*<<< orphan*/  xpcs_lock; int /*<<< orphan*/  awcache; int /*<<< orphan*/  arcache; int /*<<< orphan*/  axdomain; void* coherent; int /*<<< orphan*/ * serdes_dfe_tap_ena; int /*<<< orphan*/ * serdes_dfe_tap_cfg; int /*<<< orphan*/ * serdes_tx_amp; int /*<<< orphan*/ * serdes_pq_skew; int /*<<< orphan*/ * serdes_cdr_rate; int /*<<< orphan*/ * serdes_blwc; int /*<<< orphan*/  speed_set; TYPE_1__ phy; int /*<<< orphan*/  dmat; int /*<<< orphan*/  dev; struct ifnet* netdev; struct resource** chan_irq_res; void* per_channel_irq; struct resource* dev_irq_res; struct resource* xpcs_res; struct resource* xgmac_res; struct resource* an_irq_res; struct resource* sir1_res; struct resource* sir0_res; struct resource* rxtx_res; } ;
struct axgbe_softc {TYPE_3__ prv; int /*<<< orphan*/  media; int /*<<< orphan*/  mac_addr; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  phy_handle ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ADVERTISED_10000baseKR_Full ; 
 int ADVERTISED_1000baseKX_Full ; 
 int /*<<< orphan*/  DMA_OSP_ENABLE ; 
 void* DMA_PBL_16 ; 
 int /*<<< orphan*/  DMA_PBL_X8_ENABLE ; 
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ ETHER_ADDR_LEN ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_1000_KX ; 
 int IFM_10G_KR ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  IFM_IMASK ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  MTL_RSF_DISABLE ; 
 int /*<<< orphan*/  MTL_RX_THRESHOLD_64 ; 
 int /*<<< orphan*/  MTL_TSF_ENABLE ; 
 int /*<<< orphan*/  MTL_TX_THRESHOLD_64 ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  OF_device_from_xref (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OF_getprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ OF_getproplen (int /*<<< orphan*/ ,char*) ; 
 void* OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  XGBE_BLWC_PROPERTY ; 
 int /*<<< orphan*/  XGBE_CDR_RATE_PROPERTY ; 
 int /*<<< orphan*/  XGBE_DFE_CFG_PROPERTY ; 
 int /*<<< orphan*/  XGBE_DFE_ENA_PROPERTY ; 
 char* XGBE_DMA_IRQS_PROPERTY ; 
 int /*<<< orphan*/  XGBE_DMA_OS_ARCACHE ; 
 int /*<<< orphan*/  XGBE_DMA_OS_AWCACHE ; 
 int /*<<< orphan*/  XGBE_DMA_OS_AXDOMAIN ; 
 int /*<<< orphan*/  XGBE_DMA_SYS_ARCACHE ; 
 int /*<<< orphan*/  XGBE_DMA_SYS_AWCACHE ; 
 int /*<<< orphan*/  XGBE_DMA_SYS_AXDOMAIN ; 
 int /*<<< orphan*/  XGBE_DOWN ; 
 int /*<<< orphan*/  XGBE_PQ_SKEW_PROPERTY ; 
 int /*<<< orphan*/  XGBE_RX_DESC_CNT ; 
 char* XGBE_SPEEDSET_PROPERTY ; 
 int /*<<< orphan*/  XGBE_SPEED_10000_BLWC ; 
 int /*<<< orphan*/  XGBE_SPEED_10000_CDR ; 
 int /*<<< orphan*/  XGBE_SPEED_10000_DFE_TAP_CONFIG ; 
 int /*<<< orphan*/  XGBE_SPEED_10000_DFE_TAP_ENABLE ; 
 int /*<<< orphan*/  XGBE_SPEED_10000_PQ ; 
 int /*<<< orphan*/  XGBE_SPEED_10000_TXAMP ; 
 int /*<<< orphan*/  XGBE_SPEED_1000_BLWC ; 
 int /*<<< orphan*/  XGBE_SPEED_1000_CDR ; 
 int /*<<< orphan*/  XGBE_SPEED_1000_DFE_TAP_CONFIG ; 
 int /*<<< orphan*/  XGBE_SPEED_1000_DFE_TAP_ENABLE ; 
 int /*<<< orphan*/  XGBE_SPEED_1000_PQ ; 
 int /*<<< orphan*/  XGBE_SPEED_1000_TXAMP ; 
 int /*<<< orphan*/  XGBE_SPEED_2500_BLWC ; 
 int /*<<< orphan*/  XGBE_SPEED_2500_CDR ; 
 int /*<<< orphan*/  XGBE_SPEED_2500_DFE_TAP_CONFIG ; 
 int /*<<< orphan*/  XGBE_SPEED_2500_DFE_TAP_ENABLE ; 
 int /*<<< orphan*/  XGBE_SPEED_2500_PQ ; 
 int /*<<< orphan*/  XGBE_SPEED_2500_TXAMP ; 
 int /*<<< orphan*/  XGBE_TX_AMP_PROPERTY ; 
 int /*<<< orphan*/  XGBE_TX_DESC_CNT ; 
 int /*<<< orphan*/  axgbe_get_counter ; 
 int axgbe_get_optional_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  axgbe_init ; 
 int /*<<< orphan*/  axgbe_ioctl ; 
 int /*<<< orphan*/  axgbe_media_change ; 
 int /*<<< orphan*/  axgbe_media_status ; 
 int /*<<< orphan*/  axgbe_qflush ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource**) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct axgbe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mac_spec ; 
 int nitems (struct resource**) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_mac_spec ; 
 int /*<<< orphan*/  old_phy_spec ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  taskqueue_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int /*<<< orphan*/  xgbe_get_all_hw_features (TYPE_3__*) ; 
 int /*<<< orphan*/  xgbe_init_function_ptrs_desc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_init_function_ptrs_dev (TYPE_6__*) ; 
 int /*<<< orphan*/  xgbe_init_function_ptrs_phy (TYPE_5__*) ; 
 int /*<<< orphan*/  xgbe_init_rx_coalesce (TYPE_3__*) ; 
 int /*<<< orphan*/  xgbe_init_tx_coalesce (TYPE_3__*) ; 
 scalar_t__ xgbe_open (struct ifnet*) ; 
 int /*<<< orphan*/  xgbe_xmit ; 

__attribute__((used)) static int
axgbe_attach(device_t dev)
{
	struct axgbe_softc *sc;
	struct ifnet *ifp;
	pcell_t phy_handle;
	device_t phydev;
	phandle_t node, phy_node;
	struct resource *mac_res[11];
	struct resource *phy_res[4];
	ssize_t len;
	int error, i, j;

	sc = device_get_softc(dev);

	node = ofw_bus_get_node(dev);
	if (OF_getencprop(node, "phy-handle", &phy_handle,
	    sizeof(phy_handle)) <= 0) {
		phy_node = node;

		if (bus_alloc_resources(dev, mac_spec, mac_res)) {
			device_printf(dev,
			    "could not allocate phy resources\n");
			return (ENXIO);
		}

		sc->prv.xgmac_res = mac_res[0];
		sc->prv.xpcs_res = mac_res[1];
		sc->prv.rxtx_res = mac_res[2];
		sc->prv.sir0_res = mac_res[3];
		sc->prv.sir1_res = mac_res[4];

		sc->prv.dev_irq_res = mac_res[5];
		sc->prv.per_channel_irq = OF_hasprop(node,
		    XGBE_DMA_IRQS_PROPERTY);
		for (i = 0, j = 6; j < nitems(mac_res) - 1 &&
		    mac_res[j + 1] != NULL; i++, j++) {
			if (sc->prv.per_channel_irq) {
				sc->prv.chan_irq_res[i] = mac_res[j];
			}
		}

		/* The last entry is the auto-negotiation interrupt */
		sc->prv.an_irq_res = mac_res[j];
	} else {
		phydev = OF_device_from_xref(phy_handle);
		phy_node = ofw_bus_get_node(phydev);

		if (bus_alloc_resources(phydev, old_phy_spec, phy_res)) {
			device_printf(dev,
			    "could not allocate phy resources\n");
			return (ENXIO);
		}

		if (bus_alloc_resources(dev, old_mac_spec, mac_res)) {
			device_printf(dev,
			    "could not allocate mac resources\n");
			return (ENXIO);
		}

		sc->prv.rxtx_res = phy_res[0];
		sc->prv.sir0_res = phy_res[1];
		sc->prv.sir1_res = phy_res[2];
		sc->prv.an_irq_res = phy_res[3];

		sc->prv.xgmac_res = mac_res[0];
		sc->prv.xpcs_res = mac_res[1];
		sc->prv.dev_irq_res = mac_res[2];
		sc->prv.per_channel_irq = OF_hasprop(node,
		    XGBE_DMA_IRQS_PROPERTY);
		if (sc->prv.per_channel_irq) {
			for (i = 0, j = 3; i < nitems(sc->prv.chan_irq_res) &&
			    mac_res[j] != NULL; i++, j++) {
				sc->prv.chan_irq_res[i] = mac_res[j];
			}
		}
	}

	if ((len = OF_getproplen(node, "mac-address")) < 0) {
		device_printf(dev, "No mac-address property\n");
		return (EINVAL);
	}

	if (len != ETHER_ADDR_LEN)
		return (EINVAL);

	OF_getprop(node, "mac-address", sc->mac_addr, ETHER_ADDR_LEN);

	sc->prv.netdev = ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "Cannot alloc ifnet\n");
		return (ENXIO);
	}

	sc->prv.dev = dev;
	sc->prv.dmat = bus_get_dma_tag(dev);
	sc->prv.phy.advertising = ADVERTISED_10000baseKR_Full |
	    ADVERTISED_1000baseKX_Full;


	/*
	 * Read the needed properties from the phy node.
	 */

	/* This is documented as optional, but Linux requires it */
	if (OF_getencprop(phy_node, XGBE_SPEEDSET_PROPERTY, &sc->prv.speed_set,
	    sizeof(sc->prv.speed_set)) <= 0) {
		device_printf(dev, "%s property is missing\n",
		    XGBE_SPEEDSET_PROPERTY);
		return (EINVAL);
	}

	error = axgbe_get_optional_prop(dev, phy_node, XGBE_BLWC_PROPERTY,
	    sc->prv.serdes_blwc, sizeof(sc->prv.serdes_blwc));
	if (error > 0) {
		return (error);
	} else if (error < 0) {
		sc->prv.serdes_blwc[0] = XGBE_SPEED_1000_BLWC;
		sc->prv.serdes_blwc[1] = XGBE_SPEED_2500_BLWC;
		sc->prv.serdes_blwc[2] = XGBE_SPEED_10000_BLWC;
	}

	error = axgbe_get_optional_prop(dev, phy_node, XGBE_CDR_RATE_PROPERTY,
	    sc->prv.serdes_cdr_rate, sizeof(sc->prv.serdes_cdr_rate));
	if (error > 0) {
		return (error);
	} else if (error < 0) {
		sc->prv.serdes_cdr_rate[0] = XGBE_SPEED_1000_CDR;
		sc->prv.serdes_cdr_rate[1] = XGBE_SPEED_2500_CDR;
		sc->prv.serdes_cdr_rate[2] = XGBE_SPEED_10000_CDR;
	}

	error = axgbe_get_optional_prop(dev, phy_node, XGBE_PQ_SKEW_PROPERTY,
	    sc->prv.serdes_pq_skew, sizeof(sc->prv.serdes_pq_skew));
	if (error > 0) {
		return (error);
	} else if (error < 0) {
		sc->prv.serdes_pq_skew[0] = XGBE_SPEED_1000_PQ;
		sc->prv.serdes_pq_skew[1] = XGBE_SPEED_2500_PQ;
		sc->prv.serdes_pq_skew[2] = XGBE_SPEED_10000_PQ;
	}

	error = axgbe_get_optional_prop(dev, phy_node, XGBE_TX_AMP_PROPERTY,
	    sc->prv.serdes_tx_amp, sizeof(sc->prv.serdes_tx_amp));
	if (error > 0) {
		return (error);
	} else if (error < 0) {
		sc->prv.serdes_tx_amp[0] = XGBE_SPEED_1000_TXAMP;
		sc->prv.serdes_tx_amp[1] = XGBE_SPEED_2500_TXAMP;
		sc->prv.serdes_tx_amp[2] = XGBE_SPEED_10000_TXAMP;
	}

	error = axgbe_get_optional_prop(dev, phy_node, XGBE_DFE_CFG_PROPERTY,
	    sc->prv.serdes_dfe_tap_cfg, sizeof(sc->prv.serdes_dfe_tap_cfg));
	if (error > 0) {
		return (error);
	} else if (error < 0) {
		sc->prv.serdes_dfe_tap_cfg[0] = XGBE_SPEED_1000_DFE_TAP_CONFIG;
		sc->prv.serdes_dfe_tap_cfg[1] = XGBE_SPEED_2500_DFE_TAP_CONFIG;
		sc->prv.serdes_dfe_tap_cfg[2] = XGBE_SPEED_10000_DFE_TAP_CONFIG;
	}

	error = axgbe_get_optional_prop(dev, phy_node, XGBE_DFE_ENA_PROPERTY,
	    sc->prv.serdes_dfe_tap_ena, sizeof(sc->prv.serdes_dfe_tap_ena));
	if (error > 0) {
		return (error);
	} else if (error < 0) {
		sc->prv.serdes_dfe_tap_ena[0] = XGBE_SPEED_1000_DFE_TAP_ENABLE;
		sc->prv.serdes_dfe_tap_ena[1] = XGBE_SPEED_2500_DFE_TAP_ENABLE;
		sc->prv.serdes_dfe_tap_ena[2] = XGBE_SPEED_10000_DFE_TAP_ENABLE;
	}

	/* Check if the NIC is DMA coherent */
	sc->prv.coherent = OF_hasprop(node, "dma-coherent");
	if (sc->prv.coherent) {
		sc->prv.axdomain = XGBE_DMA_OS_AXDOMAIN;
		sc->prv.arcache = XGBE_DMA_OS_ARCACHE;
		sc->prv.awcache = XGBE_DMA_OS_AWCACHE;
	} else {
		sc->prv.axdomain = XGBE_DMA_SYS_AXDOMAIN;
		sc->prv.arcache = XGBE_DMA_SYS_ARCACHE;
		sc->prv.awcache = XGBE_DMA_SYS_AWCACHE;
	}

	/* Create the lock & workqueues */
	spin_lock_init(&sc->prv.xpcs_lock);
	sc->prv.dev_workqueue = taskqueue_create("axgbe", M_WAITOK,
	    taskqueue_thread_enqueue, &sc->prv.dev_workqueue);
	taskqueue_start_threads(&sc->prv.dev_workqueue, 1, PI_NET,
	    "axgbe taskq");

	/* Set the needed pointers */
	xgbe_init_function_ptrs_phy(&sc->prv.phy_if);
	xgbe_init_function_ptrs_dev(&sc->prv.hw_if);
	xgbe_init_function_ptrs_desc(&sc->prv.desc_if);

	/* Reset the hardware */
	sc->prv.hw_if.exit(&sc->prv);

	/* Read the hardware features */
	xgbe_get_all_hw_features(&sc->prv);

	/* Set default values */
	sc->prv.pblx8 = DMA_PBL_X8_ENABLE;
	sc->prv.tx_desc_count = XGBE_TX_DESC_CNT;
	sc->prv.tx_sf_mode = MTL_TSF_ENABLE;
	sc->prv.tx_threshold = MTL_TX_THRESHOLD_64;
	sc->prv.tx_pbl = DMA_PBL_16;
	sc->prv.tx_osp_mode = DMA_OSP_ENABLE;
	sc->prv.rx_desc_count = XGBE_RX_DESC_CNT;
	sc->prv.rx_sf_mode = MTL_RSF_DISABLE;
	sc->prv.rx_threshold = MTL_RX_THRESHOLD_64;
	sc->prv.rx_pbl = DMA_PBL_16;
	sc->prv.pause_autoneg = 1;
	sc->prv.tx_pause = 1;
	sc->prv.rx_pause = 1;
	sc->prv.phy_speed = SPEED_UNKNOWN;
	sc->prv.power_down = 0;

	/* TODO: Limit to min(ncpus, hw rings) */
	sc->prv.tx_ring_count = 1;
	sc->prv.tx_q_count = 1;
	sc->prv.rx_ring_count = 1;
	sc->prv.rx_q_count = sc->prv.hw_feat.rx_q_cnt;

	/* Init the PHY */
	sc->prv.phy_if.phy_init(&sc->prv);

	/* Set the coalescing */
	xgbe_init_rx_coalesce(&sc->prv);
	xgbe_init_tx_coalesce(&sc->prv);

	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_init = axgbe_init;
        ifp->if_softc = sc;
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = axgbe_ioctl;
	ifp->if_transmit = xgbe_xmit;
	ifp->if_qflush = axgbe_qflush;
	ifp->if_get_counter = axgbe_get_counter;

	/* TODO: Support HW offload */
	ifp->if_capabilities = 0;
	ifp->if_capenable = 0;
	ifp->if_hwassist = 0;

	ether_ifattach(ifp, sc->mac_addr);

	ifmedia_init(&sc->media, IFM_IMASK, axgbe_media_change,
	    axgbe_media_status);
#ifdef notyet
	ifmedia_add(&sc->media, IFM_ETHER | IFM_10G_KR, 0, NULL);
#endif
	ifmedia_add(&sc->media, IFM_ETHER | IFM_1000_KX, 0, NULL);
	ifmedia_add(&sc->media, IFM_ETHER | IFM_AUTO, 0, NULL);
	ifmedia_set(&sc->media, IFM_ETHER | IFM_AUTO);

	set_bit(XGBE_DOWN, &sc->prv.dev_state);

	if (xgbe_open(ifp) < 0) {
		device_printf(dev, "ndo_open failed\n");
		return (ENXIO);
	}

	return (0);
}