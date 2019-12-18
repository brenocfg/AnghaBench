#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mge_softc {int mge_ver; int volatile mge_tx_tok_cnt; int volatile mge_tx_tok_cfg; int volatile mge_tx_arb_cfg; int mge_media_status; int volatile tx_desc_start; int volatile rx_desc_start; int /*<<< orphan*/  wd_callout; scalar_t__ phy_attached; scalar_t__ wd_timer; TYPE_2__* ifp; int /*<<< orphan*/  mge_desc_dtag; struct mge_desc_wrapper* mge_rx_desc; scalar_t__ tx_desc_used_count; scalar_t__ tx_desc_used_idx; scalar_t__ rx_desc_curr; scalar_t__ tx_desc_curr; scalar_t__ switch_attached; int /*<<< orphan*/  mge_mtu; } ;
struct mge_desc_wrapper {int /*<<< orphan*/  desc_dmap; TYPE_1__* mge_desc; } ;
struct TYPE_4__ {int if_capenable; int /*<<< orphan*/  if_drv_flags; } ;
struct TYPE_3__ {int cmd_status; int /*<<< orphan*/  buff_size; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFM_1000_T ; 
 int IFM_TMASK ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int MGE_DMA_OWNED ; 
 int volatile MGE_ENABLE_RXQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGE_FIXED_PRIO_CONF ; 
 int volatile MGE_FIXED_PRIO_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGE_GLOBAL_LOCK_ASSERT (struct mge_softc*) ; 
 int /*<<< orphan*/  MGE_PORT_CONFIG ; 
 int /*<<< orphan*/  MGE_PORT_EXT_CONFIG ; 
 int /*<<< orphan*/  MGE_PORT_SERIAL_CTRL ; 
 int /*<<< orphan*/  MGE_PORT_SERIAL_CTRL1 ; 
 int /*<<< orphan*/  MGE_PORT_STATUS ; 
 int MGE_READ (struct mge_softc*,int /*<<< orphan*/ ) ; 
 int volatile MGE_RGMII_EN ; 
 int /*<<< orphan*/  MGE_RX_CUR_DESC_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGE_RX_DEFAULT_QUEUE ; 
 int MGE_RX_DESC_NUM ; 
 int MGE_RX_ENABLE_INT ; 
 int /*<<< orphan*/  MGE_RX_QUEUE_CMD ; 
 int /*<<< orphan*/  MGE_SDMA_BURST_16_WORD ; 
 int /*<<< orphan*/  MGE_SDMA_CONFIG ; 
 int volatile MGE_SDMA_RX_BURST_SIZE (int /*<<< orphan*/ ) ; 
 int volatile MGE_SDMA_RX_BYTE_SWAP ; 
 int volatile MGE_SDMA_TX_BURST_SIZE (int /*<<< orphan*/ ) ; 
 int volatile MGE_SDMA_TX_BYTE_SWAP ; 
 int volatile MGE_STATUS_LINKUP ; 
 int /*<<< orphan*/  MGE_TX_ARBITER_CONF (int) ; 
 int /*<<< orphan*/  MGE_TX_CUR_DESC_PTR ; 
 int /*<<< orphan*/  MGE_TX_FIFO_URGENT_TRSH ; 
 int /*<<< orphan*/  MGE_TX_TOKEN_CONF (int) ; 
 int /*<<< orphan*/  MGE_TX_TOKEN_COUNT (int) ; 
 int /*<<< orphan*/  MGE_WRITE (struct mge_softc*,int /*<<< orphan*/ ,int volatile) ; 
 int volatile PORT_CONFIG_ARO_RXQ (int /*<<< orphan*/ ) ; 
 int volatile PORT_CONFIG_DFLT_RXQ (int /*<<< orphan*/ ) ; 
 int volatile PORT_CONFIG_RXCS ; 
 int volatile PORT_SERIAL_ENABLE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mge_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_printf (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  mge_intrs_ctrl (struct mge_softc*,int) ; 
 int /*<<< orphan*/  mge_set_mac_address (struct mge_softc*) ; 
 int mge_set_port_serial_control (int) ; 
 int /*<<< orphan*/  mge_set_prom_mode (struct mge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mge_set_rxic (struct mge_softc*) ; 
 int /*<<< orphan*/  mge_set_txic (struct mge_softc*) ; 
 int /*<<< orphan*/  mge_setup_multicast (struct mge_softc*) ; 
 int /*<<< orphan*/  mge_stop (struct mge_softc*) ; 
 int /*<<< orphan*/  mge_tick ; 

__attribute__((used)) static void
mge_init_locked(void *arg)
{
	struct mge_softc *sc = arg;
	struct mge_desc_wrapper *dw;
	volatile uint32_t reg_val;
	int i, count;
	uint32_t media_status;


	MGE_GLOBAL_LOCK_ASSERT(sc);

	/* Stop interface */
	mge_stop(sc);

	/* Disable interrupts */
	mge_intrs_ctrl(sc, 0);

	/* Set MAC address */
	mge_set_mac_address(sc);

	/* Setup multicast filters */
	mge_setup_multicast(sc);

	if (sc->mge_ver == 2) {
		MGE_WRITE(sc, MGE_PORT_SERIAL_CTRL1, MGE_RGMII_EN);
		MGE_WRITE(sc, MGE_FIXED_PRIO_CONF, MGE_FIXED_PRIO_EN(0));
	}

	/* Initialize TX queue configuration registers */
	MGE_WRITE(sc, MGE_TX_TOKEN_COUNT(0), sc->mge_tx_tok_cnt);
	MGE_WRITE(sc, MGE_TX_TOKEN_CONF(0), sc->mge_tx_tok_cfg);
	MGE_WRITE(sc, MGE_TX_ARBITER_CONF(0), sc->mge_tx_arb_cfg);

	/* Clear TX queue configuration registers for unused queues */
	for (i = 1; i < 7; i++) {
		MGE_WRITE(sc, MGE_TX_TOKEN_COUNT(i), 0);
		MGE_WRITE(sc, MGE_TX_TOKEN_CONF(i), 0);
		MGE_WRITE(sc, MGE_TX_ARBITER_CONF(i), 0);
	}

	/* Set default MTU */
	MGE_WRITE(sc, sc->mge_mtu, 0);

	/* Port configuration */
	MGE_WRITE(sc, MGE_PORT_CONFIG,
	    PORT_CONFIG_RXCS | PORT_CONFIG_DFLT_RXQ(0) |
	    PORT_CONFIG_ARO_RXQ(0));
	MGE_WRITE(sc, MGE_PORT_EXT_CONFIG , 0x0);

	/* Configure promisc mode */
	mge_set_prom_mode(sc, MGE_RX_DEFAULT_QUEUE);

	media_status = sc->mge_media_status;
	if (sc->switch_attached) {
		media_status &= ~IFM_TMASK;
		media_status |= IFM_1000_T;
	}

	/* Setup port configuration */
	reg_val = mge_set_port_serial_control(media_status);
	MGE_WRITE(sc, MGE_PORT_SERIAL_CTRL, reg_val);

	/* Setup SDMA configuration */
	MGE_WRITE(sc, MGE_SDMA_CONFIG , MGE_SDMA_RX_BYTE_SWAP |
	    MGE_SDMA_TX_BYTE_SWAP |
	    MGE_SDMA_RX_BURST_SIZE(MGE_SDMA_BURST_16_WORD) |
	    MGE_SDMA_TX_BURST_SIZE(MGE_SDMA_BURST_16_WORD));

	MGE_WRITE(sc, MGE_TX_FIFO_URGENT_TRSH, 0x0);

	MGE_WRITE(sc, MGE_TX_CUR_DESC_PTR, sc->tx_desc_start);
	MGE_WRITE(sc, MGE_RX_CUR_DESC_PTR(MGE_RX_DEFAULT_QUEUE),
	    sc->rx_desc_start);

	/* Reset descriptor indexes */
	sc->tx_desc_curr = 0;
	sc->rx_desc_curr = 0;
	sc->tx_desc_used_idx = 0;
	sc->tx_desc_used_count = 0;

	/* Enable RX descriptors */
	for (i = 0; i < MGE_RX_DESC_NUM; i++) {
		dw = &sc->mge_rx_desc[i];
		dw->mge_desc->cmd_status = MGE_RX_ENABLE_INT | MGE_DMA_OWNED;
		dw->mge_desc->buff_size = MCLBYTES;
		bus_dmamap_sync(sc->mge_desc_dtag, dw->desc_dmap,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	}

	/* Enable RX queue */
	MGE_WRITE(sc, MGE_RX_QUEUE_CMD, MGE_ENABLE_RXQ(MGE_RX_DEFAULT_QUEUE));

	/* Enable port */
	reg_val = MGE_READ(sc, MGE_PORT_SERIAL_CTRL);
	reg_val |= PORT_SERIAL_ENABLE;
	MGE_WRITE(sc, MGE_PORT_SERIAL_CTRL, reg_val);
	count = 0x100000;
	for (;;) {
		reg_val = MGE_READ(sc, MGE_PORT_STATUS);
		if (reg_val & MGE_STATUS_LINKUP)
			break;
		DELAY(100);
		if (--count == 0) {
			if_printf(sc->ifp, "Timeout on link-up\n");
			break;
		}
	}

	/* Setup interrupts coalescing */
	mge_set_rxic(sc);
	mge_set_txic(sc);

	/* Enable interrupts */
#ifdef DEVICE_POLLING
        /*
	 * * ...only if polling is not turned on. Disable interrupts explicitly
	 * if polling is enabled.
	 */
	if (sc->ifp->if_capenable & IFCAP_POLLING)
		mge_intrs_ctrl(sc, 0);
	else
#endif /* DEVICE_POLLING */
	mge_intrs_ctrl(sc, 1);

	/* Activate network interface */
	sc->ifp->if_drv_flags |= IFF_DRV_RUNNING;
	sc->ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
	sc->wd_timer = 0;

	/* Schedule watchdog timeout */
	if (sc->phy_attached)
		callout_reset(&sc->wd_callout, hz, mge_tick, sc);
}