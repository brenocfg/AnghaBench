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
struct rt_softc {scalar_t__ gdma1_base; scalar_t__ pdma_glo_cfg; scalar_t__ pdma_rst_idx; scalar_t__* tx_base_ptr; scalar_t__* tx_max_cnt; scalar_t__* tx_ctx_idx; int rx_ring_count; scalar_t__* rx_base_ptr; scalar_t__* rx_max_cnt; scalar_t__* rx_calc_idx; scalar_t__ rt_chipid; scalar_t__ delay_int_cfg; scalar_t__ fe_int_status; int intr_enable_mask; scalar_t__ fe_int_enable; int /*<<< orphan*/  periodic_ch; scalar_t__ periodic_round; TYPE_2__* rx_ring; TYPE_1__* tx_ring; int /*<<< orphan*/  dev; int /*<<< orphan*/  rt_miibus; struct ifnet* ifp; } ;
struct mii_data {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct TYPE_4__ {int desc_phys_addr; } ;
struct TYPE_3__ {int desc_phys_addr; } ;

/* Variables and functions */
 int CNT_GDM_AF ; 
 int CNT_PPE_AF ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int FE_DMA_BT_SIZE16 ; 
 int FE_RST_DRX_IDX0 ; 
 int FE_RST_DTX_IDX0 ; 
 int FE_RST_DTX_IDX1 ; 
 int FE_RST_DTX_IDX2 ; 
 int FE_RST_DTX_IDX3 ; 
 int FE_RX_DMA_BUSY ; 
 int FE_RX_DMA_EN ; 
 int FE_TX_DMA_BUSY ; 
 int FE_TX_DMA_EN ; 
 int FE_TX_WB_DDONE ; 
 scalar_t__ GDMA_FWD_CFG ; 
 int GDM_BFRC_P_SHIFT ; 
 int GDM_CRC_DROP ; 
 int GDM_DST_PORT_CPU ; 
 int GDM_ICS_EN ; 
 int GDM_MFRC_P_SHIFT ; 
 int GDM_OFRC_P_SHIFT ; 
 int GDM_OTHER_DROP ; 
 int GDM_STRPCRC ; 
 int GDM_TCS_EN ; 
 int GDM_UCS_EN ; 
 int GDM_UFRC_P_SHIFT ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int INT_RX_COHERENT ; 
 int INT_RX_DONE ; 
 int INT_TXQ0_DONE ; 
 int INT_TXQ1_DONE ; 
 int INT_TXQ2_DONE ; 
 int INT_TXQ3_DONE ; 
 int INT_TX_COHERENT ; 
 int PSE_BUF_DROP ; 
 int PSE_FQ_EMPTY ; 
 int PSE_P0_FC ; 
 int PSE_P1_FC ; 
 int PSE_P2_FC ; 
 int RT5350_INT_RXQ0_DONE ; 
 int RT5350_INT_RXQ1_DONE ; 
 int RT5350_INT_RX_COHERENT ; 
 int RT5350_INT_TXQ0_DONE ; 
 int RT5350_INT_TXQ1_DONE ; 
 int RT5350_INT_TXQ2_DONE ; 
 int RT5350_INT_TXQ3_DONE ; 
 int RT5350_INT_TX_COHERENT ; 
 scalar_t__ RT_CHIPID_MT7620 ; 
 scalar_t__ RT_CHIPID_MT7621 ; 
 scalar_t__ RT_CHIPID_RT5350 ; 
 int /*<<< orphan*/  RT_DEBUG_ANY ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*) ; 
 int RT_READ (struct rt_softc*,scalar_t__) ; 
 int /*<<< orphan*/  RT_SOFTC_ASSERT_LOCKED (struct rt_softc*) ; 
 int RT_SOFTC_RX_RING_DATA_COUNT ; 
 int RT_SOFTC_TX_RING_COUNT ; 
 int RT_SOFTC_TX_RING_DESC_COUNT ; 
 int /*<<< orphan*/  RT_WRITE (struct rt_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct rt_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 
 int /*<<< orphan*/  rt_periodic ; 
 int /*<<< orphan*/  rt_reset_rx_ring (struct rt_softc*,TYPE_2__*) ; 
 int /*<<< orphan*/  rt_reset_tx_ring (struct rt_softc*,TYPE_1__*) ; 
 int /*<<< orphan*/  rt_stop_locked (struct rt_softc*) ; 
 scalar_t__ rt_txrx_enable (struct rt_softc*) ; 

__attribute__((used)) static void
rt_init_locked(void *priv)
{
	struct rt_softc *sc;
	struct ifnet *ifp;
#ifdef IF_RT_PHY_SUPPORT
	struct mii_data *mii;
#endif
	int i, ntries;
	uint32_t tmp;

	sc = priv;
	ifp = sc->ifp;
#ifdef IF_RT_PHY_SUPPORT
	mii = device_get_softc(sc->rt_miibus);
#endif

	RT_DPRINTF(sc, RT_DEBUG_ANY, "initializing\n");

	RT_SOFTC_ASSERT_LOCKED(sc);

	/* hardware reset */
	//RT_WRITE(sc, GE_PORT_BASE + FE_RST_GLO, PSE_RESET);
	//rt305x_sysctl_set(SYSCTL_RSTCTRL, SYSCTL_RSTCTRL_FRENG);

	/* Fwd to CPU (uni|broad|multi)cast and Unknown */
	if (sc->gdma1_base != 0)
		RT_WRITE(sc, sc->gdma1_base + GDMA_FWD_CFG,
		(
		GDM_ICS_EN | /* Enable IP Csum */
		GDM_TCS_EN | /* Enable TCP Csum */
		GDM_UCS_EN | /* Enable UDP Csum */
		GDM_STRPCRC | /* Strip CRC from packet */
		GDM_DST_PORT_CPU << GDM_UFRC_P_SHIFT | /* fwd UCast to CPU */
		GDM_DST_PORT_CPU << GDM_BFRC_P_SHIFT | /* fwd BCast to CPU */
		GDM_DST_PORT_CPU << GDM_MFRC_P_SHIFT | /* fwd MCast to CPU */
		GDM_DST_PORT_CPU << GDM_OFRC_P_SHIFT   /* fwd Other to CPU */
		));

	/* disable DMA engine */
	RT_WRITE(sc, sc->pdma_glo_cfg, 0);
	RT_WRITE(sc, sc->pdma_rst_idx, 0xffffffff);

	/* wait while DMA engine is busy */
	for (ntries = 0; ntries < 100; ntries++) {
		tmp = RT_READ(sc, sc->pdma_glo_cfg);
		if (!(tmp & (FE_TX_DMA_BUSY | FE_RX_DMA_BUSY)))
			break;
		DELAY(1000);
	}

	if (ntries == 100) {
		device_printf(sc->dev, "timeout waiting for DMA engine\n");
		goto fail;
	}

	/* reset Rx and Tx rings */
	tmp = FE_RST_DRX_IDX0 |
		FE_RST_DTX_IDX3 |
		FE_RST_DTX_IDX2 |
		FE_RST_DTX_IDX1 |
		FE_RST_DTX_IDX0;

	RT_WRITE(sc, sc->pdma_rst_idx, tmp);

	/* XXX switch set mac address */
	for (i = 0; i < RT_SOFTC_TX_RING_COUNT; i++)
		rt_reset_tx_ring(sc, &sc->tx_ring[i]);

	for (i = 0; i < RT_SOFTC_TX_RING_COUNT; i++) {
		/* update TX_BASE_PTRx */
		RT_WRITE(sc, sc->tx_base_ptr[i],
			sc->tx_ring[i].desc_phys_addr);
		RT_WRITE(sc, sc->tx_max_cnt[i],
			RT_SOFTC_TX_RING_DESC_COUNT);
		RT_WRITE(sc, sc->tx_ctx_idx[i], 0);
	}

	/* init Rx ring */
	for (i = 0; i < sc->rx_ring_count; i++)
		rt_reset_rx_ring(sc, &sc->rx_ring[i]);

	/* update RX_BASE_PTRx */
	for (i = 0; i < sc->rx_ring_count; i++) {
		RT_WRITE(sc, sc->rx_base_ptr[i],
			sc->rx_ring[i].desc_phys_addr);
		RT_WRITE(sc, sc->rx_max_cnt[i],
			RT_SOFTC_RX_RING_DATA_COUNT);
		RT_WRITE(sc, sc->rx_calc_idx[i],
			RT_SOFTC_RX_RING_DATA_COUNT - 1);
	}

	/* write back DDONE, 16byte burst enable RX/TX DMA */
	tmp = FE_TX_WB_DDONE | FE_DMA_BT_SIZE16 | FE_RX_DMA_EN | FE_TX_DMA_EN;
	if (sc->rt_chipid == RT_CHIPID_MT7620 ||
	    sc->rt_chipid == RT_CHIPID_MT7621)
		tmp |= (1<<31);
	RT_WRITE(sc, sc->pdma_glo_cfg, tmp);

	/* disable interrupts mitigation */
	RT_WRITE(sc, sc->delay_int_cfg, 0);

	/* clear pending interrupts */
	RT_WRITE(sc, sc->fe_int_status, 0xffffffff);

	/* enable interrupts */
	if (sc->rt_chipid == RT_CHIPID_RT5350 ||
	    sc->rt_chipid == RT_CHIPID_MT7620 ||
	    sc->rt_chipid == RT_CHIPID_MT7621)
	  tmp = RT5350_INT_TX_COHERENT |
	  	RT5350_INT_RX_COHERENT |
	  	RT5350_INT_TXQ3_DONE |
	  	RT5350_INT_TXQ2_DONE |
	  	RT5350_INT_TXQ1_DONE |
	  	RT5350_INT_TXQ0_DONE |
	  	RT5350_INT_RXQ1_DONE |
	  	RT5350_INT_RXQ0_DONE;
	else
	  tmp = CNT_PPE_AF |
		CNT_GDM_AF |
		PSE_P2_FC |
		GDM_CRC_DROP |
		PSE_BUF_DROP |
		GDM_OTHER_DROP |
		PSE_P1_FC |
		PSE_P0_FC |
		PSE_FQ_EMPTY |
		INT_TX_COHERENT |
		INT_RX_COHERENT |
		INT_TXQ3_DONE |
		INT_TXQ2_DONE |
		INT_TXQ1_DONE |
		INT_TXQ0_DONE |
		INT_RX_DONE;

	sc->intr_enable_mask = tmp;

	RT_WRITE(sc, sc->fe_int_enable, tmp);

	if (rt_txrx_enable(sc) != 0)
		goto fail;

#ifdef IF_RT_PHY_SUPPORT
	if (mii) mii_mediachg(mii);
#endif /* IF_RT_PHY_SUPPORT */

	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
	ifp->if_drv_flags |= IFF_DRV_RUNNING;

	sc->periodic_round = 0;

	callout_reset(&sc->periodic_ch, hz / 10, rt_periodic, sc);

	return;

fail:
	rt_stop_locked(sc);
}