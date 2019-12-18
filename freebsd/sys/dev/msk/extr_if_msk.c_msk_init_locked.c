#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct msk_softc {int msk_hw_id; scalar_t__ msk_hw_rev; int msk_intrmask; int msk_intrhwemask; scalar_t__ msk_int_holdoff; } ;
struct TYPE_2__ {int /*<<< orphan*/  msk_rx_ring_paddr; int /*<<< orphan*/  msk_jumbo_rx_ring_paddr; int /*<<< orphan*/  msk_tx_ring_paddr; } ;
struct msk_if_softc {scalar_t__ msk_framesize; int msk_flags; scalar_t__ msk_port; int /*<<< orphan*/  msk_tick_ch; int /*<<< orphan*/  msk_if_dev; TYPE_1__ msk_rdata; int /*<<< orphan*/  msk_rxq; int /*<<< orphan*/  msk_txq; int /*<<< orphan*/  msk_txsq; int /*<<< orphan*/  msk_miibus; struct msk_softc* msk_softc; struct ifnet* msk_ifp; } ;
struct mii_data {int dummy; } ;
struct ifnet {int if_drv_flags; scalar_t__ if_mtu; int if_hwassist; int if_capenable; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_HWE_IMSK ; 
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  B2_IRQM_CTRL ; 
 int /*<<< orphan*/  B2_IRQM_INI ; 
 int /*<<< orphan*/  B2_IRQM_MSK ; 
 int /*<<< orphan*/  B2_IRQM_VAL ; 
 int BMU_CLR_RESET ; 
 int BMU_DIS_RX_CHKSUM ; 
 int BMU_DIS_RX_RSS_HASH ; 
 int BMU_ENA_RX_CHKSUM ; 
 int BMU_FIFO_OP_ON ; 
 int BMU_OPER_INIT ; 
#define  CHIP_ID_YUKON_EC_U 129 
#define  CHIP_ID_YUKON_EX 128 
 int CHIP_ID_YUKON_FE_P ; 
 int CHIP_ID_YUKON_SUPR ; 
 int CHIP_ID_YUKON_XL ; 
 scalar_t__ CHIP_REV_YU_EC_U_A0 ; 
 scalar_t__ CHIP_REV_YU_EC_U_A1 ; 
 scalar_t__ CHIP_REV_YU_EX_B0 ; 
 scalar_t__ CHIP_REV_YU_FE_P_A0 ; 
 int /*<<< orphan*/  CSR_READ_1 (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct msk_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct msk_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct msk_softc*,int /*<<< orphan*/ ,int) ; 
 int CSUM_TSO ; 
 int /*<<< orphan*/  DATA_BLIND_DEF ; 
 int DATA_BLIND_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ ETHERMTU ; 
 scalar_t__ ETHER_HDR_LEN ; 
 scalar_t__ ETHER_VLAN_ENCAP_LEN ; 
 int F_M_RX_RAM_DIS ; 
 int F_TX_CHK_AUTO_OFF ; 
 int /*<<< orphan*/  GMAC_CTRL ; 
 int /*<<< orphan*/  GMAC_IRQ_SRC ; 
 int /*<<< orphan*/  GMAC_WRITE_2 (struct msk_softc*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int GMC_BYP_MACSECRX_ON ; 
 int GMC_BYP_MACSECTX_ON ; 
 int GMC_BYP_RETR_ON ; 
 int GMC_F_LOOPB_OFF ; 
 int GMC_RST_CLR ; 
 int GMC_RST_SET ; 
 int GMF_OPER_ON ; 
 int GMF_RST_CLR ; 
 int GMF_RST_SET ; 
 int GMF_RX_F_FL_ON ; 
 int GMF_RX_MACSEC_FLUSH_OFF ; 
 int GMF_RX_OVER_ON ; 
 int GMR_FS_ANY_ERR ; 
 int /*<<< orphan*/  GM_GP_CTRL ; 
 int GM_RXCR_CRC_DIS ; 
 int /*<<< orphan*/  GM_RX_CTRL ; 
 int /*<<< orphan*/  GM_RX_IRQ_MSK ; 
 int /*<<< orphan*/  GM_SERIAL_MODE ; 
 int GM_SMOD_JUMBO_ENA ; 
 int GM_SMOD_VLAN_ENA ; 
 int /*<<< orphan*/  GM_SRC_ADDR_1H ; 
 int /*<<< orphan*/  GM_SRC_ADDR_1L ; 
 int /*<<< orphan*/  GM_SRC_ADDR_1M ; 
 int /*<<< orphan*/  GM_SRC_ADDR_2H ; 
 int /*<<< orphan*/  GM_SRC_ADDR_2L ; 
 int /*<<< orphan*/  GM_SRC_ADDR_2M ; 
 int /*<<< orphan*/  GM_TR_IRQ_MSK ; 
 int /*<<< orphan*/  GM_TX_CTRL ; 
 int /*<<< orphan*/  GM_TX_FLOW_CTRL ; 
 int /*<<< orphan*/  GM_TX_IRQ_MSK ; 
 int /*<<< orphan*/  GM_TX_PARAM ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TXCSUM ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int* IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  IPG_DATA_DEF ; 
 int IPG_DATA_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ MCLBYTES ; 
 int /*<<< orphan*/  MR_ADDR (scalar_t__,int /*<<< orphan*/ ) ; 
 int MSK_BMU_RX_WM ; 
 int MSK_BMU_TX_WM ; 
 int MSK_CSUM_FEATURES ; 
 int MSK_ECU_LLPP ; 
 int MSK_ECU_TXFF_LEV ; 
 int MSK_ECU_ULPP ; 
 int MSK_FLAG_DESCV2 ; 
 int MSK_FLAG_JUMBO_NOCSUM ; 
 int MSK_FLAG_LINK ; 
 int MSK_FLAG_RAMBUF ; 
 int /*<<< orphan*/  MSK_IF_LOCK_ASSERT (struct msk_if_softc*) ; 
 scalar_t__ MSK_JUMBO_RX_RING_CNT ; 
 scalar_t__ MSK_PORT_A ; 
 scalar_t__ MSK_RX_BUF_ALIGN ; 
 scalar_t__ MSK_RX_RING_CNT ; 
 scalar_t__ MSK_TX_RING_CNT ; 
 int MSK_USECS (struct msk_softc*,scalar_t__) ; 
 int /*<<< orphan*/  Q_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_AL ; 
 int /*<<< orphan*/  Q_CSR ; 
 int /*<<< orphan*/  Q_F ; 
 int /*<<< orphan*/  Q_WM ; 
 int /*<<< orphan*/  RB_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CTRL ; 
 int RB_RST_SET ; 
 int /*<<< orphan*/  RX_GMF_CTRL_T ; 
 int /*<<< orphan*/  RX_GMF_FL_MSK ; 
 int /*<<< orphan*/  RX_GMF_FL_THR ; 
 int RX_GMF_FL_THR_DEF ; 
 int /*<<< orphan*/  RX_GMF_LP_THR ; 
 int /*<<< orphan*/  RX_GMF_UP_THR ; 
 int TIM_START ; 
 int /*<<< orphan*/  TXA_CTRL ; 
 int TXA_DIS_ALLOC ; 
 int TXA_DIS_FSYNC ; 
 int TXA_ENA_ARB ; 
 int TXA_STOP_RC ; 
 int TX_BACK_OFF_LIM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_BOF_LIM_DEF ; 
 int /*<<< orphan*/  TX_COL_DEF ; 
 int TX_COL_THR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_GMF_CTRL_T ; 
 int /*<<< orphan*/  TX_GMF_EA ; 
 int TX_IPG_JAM_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_IPG_JAM_DEF ; 
 int /*<<< orphan*/  TX_JAM_IPG_DEF ; 
 int TX_JAM_IPG_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_JAM_LEN_DEF ; 
 int TX_JAM_LEN_VAL (int /*<<< orphan*/ ) ; 
 int Y2_HWE_L1_MASK ; 
 int Y2_HWE_L2_MASK ; 
 int Y2_IS_PORT_A ; 
 int Y2_IS_PORT_B ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msk_if_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 
 int msk_init_jumbo_rx_ring (struct msk_if_softc*) ; 
 int msk_init_rx_ring (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_init_tx_ring (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_rxfilter (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_set_prefetch (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msk_set_rambuffer (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_set_tx_stfwd (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_setvlan (struct msk_if_softc*,struct ifnet*) ; 
 int /*<<< orphan*/  msk_stats_clear (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_stop (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_tick ; 

__attribute__((used)) static void
msk_init_locked(struct msk_if_softc *sc_if)
{
	struct msk_softc *sc;
	struct ifnet *ifp;
	struct mii_data	 *mii;
	uint8_t *eaddr;
	uint16_t gmac;
	uint32_t reg;
	int error;

	MSK_IF_LOCK_ASSERT(sc_if);

	ifp = sc_if->msk_ifp;
	sc = sc_if->msk_softc;
	mii = device_get_softc(sc_if->msk_miibus);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	error = 0;
	/* Cancel pending I/O and free all Rx/Tx buffers. */
	msk_stop(sc_if);

	if (ifp->if_mtu < ETHERMTU)
		sc_if->msk_framesize = ETHERMTU;
	else
		sc_if->msk_framesize = ifp->if_mtu;
	sc_if->msk_framesize += ETHER_HDR_LEN + ETHER_VLAN_ENCAP_LEN;
	if (ifp->if_mtu > ETHERMTU &&
	    (sc_if->msk_flags & MSK_FLAG_JUMBO_NOCSUM) != 0) {
		ifp->if_hwassist &= ~(MSK_CSUM_FEATURES | CSUM_TSO);
		ifp->if_capenable &= ~(IFCAP_TSO4 | IFCAP_TXCSUM);
	}

	/* GMAC Control reset. */
	CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, GMAC_CTRL), GMC_RST_SET);
	CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, GMAC_CTRL), GMC_RST_CLR);
	CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, GMAC_CTRL), GMC_F_LOOPB_OFF);
	if (sc->msk_hw_id == CHIP_ID_YUKON_EX ||
	    sc->msk_hw_id == CHIP_ID_YUKON_SUPR)
		CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, GMAC_CTRL),
		    GMC_BYP_MACSECRX_ON | GMC_BYP_MACSECTX_ON |
		    GMC_BYP_RETR_ON);

	/*
	 * Initialize GMAC first such that speed/duplex/flow-control
	 * parameters are renegotiated when interface is brought up.
	 */
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_GP_CTRL, 0);

	/* Dummy read the Interrupt Source Register. */
	CSR_READ_1(sc, MR_ADDR(sc_if->msk_port, GMAC_IRQ_SRC));

	/* Clear MIB stats. */
	msk_stats_clear(sc_if);

	/* Disable FCS. */
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_RX_CTRL, GM_RXCR_CRC_DIS);

	/* Setup Transmit Control Register. */
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_TX_CTRL, TX_COL_THR(TX_COL_DEF));

	/* Setup Transmit Flow Control Register. */
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_TX_FLOW_CTRL, 0xffff);

	/* Setup Transmit Parameter Register. */
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_TX_PARAM,
	    TX_JAM_LEN_VAL(TX_JAM_LEN_DEF) | TX_JAM_IPG_VAL(TX_JAM_IPG_DEF) |
	    TX_IPG_JAM_DATA(TX_IPG_JAM_DEF) | TX_BACK_OFF_LIM(TX_BOF_LIM_DEF));

	gmac = DATA_BLIND_VAL(DATA_BLIND_DEF) |
	    GM_SMOD_VLAN_ENA | IPG_DATA_VAL(IPG_DATA_DEF);

	if (ifp->if_mtu > ETHERMTU)
		gmac |= GM_SMOD_JUMBO_ENA;
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_SERIAL_MODE, gmac);

	/* Set station address. */
	eaddr = IF_LLADDR(ifp);
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_SRC_ADDR_1L,
	    eaddr[0] | (eaddr[1] << 8));
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_SRC_ADDR_1M,
	    eaddr[2] | (eaddr[3] << 8));
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_SRC_ADDR_1H,
	    eaddr[4] | (eaddr[5] << 8));
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_SRC_ADDR_2L,
	    eaddr[0] | (eaddr[1] << 8));
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_SRC_ADDR_2M,
	    eaddr[2] | (eaddr[3] << 8));
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_SRC_ADDR_2H,
	    eaddr[4] | (eaddr[5] << 8));

	/* Disable interrupts for counter overflows. */
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_TX_IRQ_MSK, 0);
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_RX_IRQ_MSK, 0);
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_TR_IRQ_MSK, 0);

	/* Configure Rx MAC FIFO. */
	CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, RX_GMF_CTRL_T), GMF_RST_SET);
	CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, RX_GMF_CTRL_T), GMF_RST_CLR);
	reg = GMF_OPER_ON | GMF_RX_F_FL_ON;
	if (sc->msk_hw_id == CHIP_ID_YUKON_FE_P ||
	    sc->msk_hw_id == CHIP_ID_YUKON_EX)
		reg |= GMF_RX_OVER_ON;
	CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, RX_GMF_CTRL_T), reg);

	/* Set receive filter. */
	msk_rxfilter(sc_if);

	if (sc->msk_hw_id == CHIP_ID_YUKON_XL) {
		/* Clear flush mask - HW bug. */
		CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, RX_GMF_FL_MSK), 0);
	} else {
		/* Flush Rx MAC FIFO on any flow control or error. */
		CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, RX_GMF_FL_MSK),
		    GMR_FS_ANY_ERR);
	}

	/*
	 * Set Rx FIFO flush threshold to 64 bytes + 1 FIFO word
	 * due to hardware hang on receipt of pause frames.
	 */
	reg = RX_GMF_FL_THR_DEF + 1;
	/* Another magic for Yukon FE+ - From Linux. */
	if (sc->msk_hw_id == CHIP_ID_YUKON_FE_P &&
	    sc->msk_hw_rev == CHIP_REV_YU_FE_P_A0)
		reg = 0x178;
	CSR_WRITE_2(sc, MR_ADDR(sc_if->msk_port, RX_GMF_FL_THR), reg);

	/* Configure Tx MAC FIFO. */
	CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, TX_GMF_CTRL_T), GMF_RST_SET);
	CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, TX_GMF_CTRL_T), GMF_RST_CLR);
	CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, TX_GMF_CTRL_T), GMF_OPER_ON);

	/* Configure hardware VLAN tag insertion/stripping. */
	msk_setvlan(sc_if, ifp);

	if ((sc_if->msk_flags & MSK_FLAG_RAMBUF) == 0) {
		/* Set Rx Pause threshold. */
		CSR_WRITE_2(sc, MR_ADDR(sc_if->msk_port, RX_GMF_LP_THR),
		    MSK_ECU_LLPP);
		CSR_WRITE_2(sc, MR_ADDR(sc_if->msk_port, RX_GMF_UP_THR),
		    MSK_ECU_ULPP);
		/* Configure store-and-forward for Tx. */
		msk_set_tx_stfwd(sc_if);
	}

	if (sc->msk_hw_id == CHIP_ID_YUKON_FE_P &&
	    sc->msk_hw_rev == CHIP_REV_YU_FE_P_A0) {
		/* Disable dynamic watermark - from Linux. */
		reg = CSR_READ_4(sc, MR_ADDR(sc_if->msk_port, TX_GMF_EA));
		reg &= ~0x03;
		CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, TX_GMF_EA), reg);
	}

	/*
	 * Disable Force Sync bit and Alloc bit in Tx RAM interface
	 * arbiter as we don't use Sync Tx queue.
	 */
	CSR_WRITE_1(sc, MR_ADDR(sc_if->msk_port, TXA_CTRL),
	    TXA_DIS_FSYNC | TXA_DIS_ALLOC | TXA_STOP_RC);
	/* Enable the RAM Interface Arbiter. */
	CSR_WRITE_1(sc, MR_ADDR(sc_if->msk_port, TXA_CTRL), TXA_ENA_ARB);

	/* Setup RAM buffer. */
	msk_set_rambuffer(sc_if);

	/* Disable Tx sync Queue. */
	CSR_WRITE_1(sc, RB_ADDR(sc_if->msk_txsq, RB_CTRL), RB_RST_SET);

	/* Setup Tx Queue Bus Memory Interface. */
	CSR_WRITE_4(sc, Q_ADDR(sc_if->msk_txq, Q_CSR), BMU_CLR_RESET);
	CSR_WRITE_4(sc, Q_ADDR(sc_if->msk_txq, Q_CSR), BMU_OPER_INIT);
	CSR_WRITE_4(sc, Q_ADDR(sc_if->msk_txq, Q_CSR), BMU_FIFO_OP_ON);
	CSR_WRITE_2(sc, Q_ADDR(sc_if->msk_txq, Q_WM), MSK_BMU_TX_WM);
	switch (sc->msk_hw_id) {
	case CHIP_ID_YUKON_EC_U:
		if (sc->msk_hw_rev == CHIP_REV_YU_EC_U_A0) {
			/* Fix for Yukon-EC Ultra: set BMU FIFO level */
			CSR_WRITE_2(sc, Q_ADDR(sc_if->msk_txq, Q_AL),
			    MSK_ECU_TXFF_LEV);
		}
		break;
	case CHIP_ID_YUKON_EX:
		/*
		 * Yukon Extreme seems to have silicon bug for
		 * automatic Tx checksum calculation capability.
		 */
		if (sc->msk_hw_rev == CHIP_REV_YU_EX_B0)
			CSR_WRITE_4(sc, Q_ADDR(sc_if->msk_txq, Q_F),
			    F_TX_CHK_AUTO_OFF);
		break;
	}

	/* Setup Rx Queue Bus Memory Interface. */
	CSR_WRITE_4(sc, Q_ADDR(sc_if->msk_rxq, Q_CSR), BMU_CLR_RESET);
	CSR_WRITE_4(sc, Q_ADDR(sc_if->msk_rxq, Q_CSR), BMU_OPER_INIT);
	CSR_WRITE_4(sc, Q_ADDR(sc_if->msk_rxq, Q_CSR), BMU_FIFO_OP_ON);
	CSR_WRITE_2(sc, Q_ADDR(sc_if->msk_rxq, Q_WM), MSK_BMU_RX_WM);
        if (sc->msk_hw_id == CHIP_ID_YUKON_EC_U &&
	    sc->msk_hw_rev >= CHIP_REV_YU_EC_U_A1) {
		/* MAC Rx RAM Read is controlled by hardware. */
                CSR_WRITE_4(sc, Q_ADDR(sc_if->msk_rxq, Q_F), F_M_RX_RAM_DIS);
	}

	msk_set_prefetch(sc, sc_if->msk_txq,
	    sc_if->msk_rdata.msk_tx_ring_paddr, MSK_TX_RING_CNT - 1);
	msk_init_tx_ring(sc_if);

	/* Disable Rx checksum offload and RSS hash. */
	reg = BMU_DIS_RX_RSS_HASH;
	if ((sc_if->msk_flags & MSK_FLAG_DESCV2) == 0 &&
	    (ifp->if_capenable & IFCAP_RXCSUM) != 0)
		reg |= BMU_ENA_RX_CHKSUM;
	else
		reg |= BMU_DIS_RX_CHKSUM;
	CSR_WRITE_4(sc, Q_ADDR(sc_if->msk_rxq, Q_CSR), reg);
	if (sc_if->msk_framesize > (MCLBYTES - MSK_RX_BUF_ALIGN)) {
		msk_set_prefetch(sc, sc_if->msk_rxq,
		    sc_if->msk_rdata.msk_jumbo_rx_ring_paddr,
		    MSK_JUMBO_RX_RING_CNT - 1);
		error = msk_init_jumbo_rx_ring(sc_if);
	 } else {
		msk_set_prefetch(sc, sc_if->msk_rxq,
		    sc_if->msk_rdata.msk_rx_ring_paddr,
		    MSK_RX_RING_CNT - 1);
		error = msk_init_rx_ring(sc_if);
	}
	if (error != 0) {
		device_printf(sc_if->msk_if_dev,
		    "initialization failed: no memory for Rx buffers\n");
		msk_stop(sc_if);
		return;
	}
	if (sc->msk_hw_id == CHIP_ID_YUKON_EX ||
	    sc->msk_hw_id == CHIP_ID_YUKON_SUPR) {
		/* Disable flushing of non-ASF packets. */
		CSR_WRITE_4(sc, MR_ADDR(sc_if->msk_port, RX_GMF_CTRL_T),
		    GMF_RX_MACSEC_FLUSH_OFF);
	}

	/* Configure interrupt handling. */
	if (sc_if->msk_port == MSK_PORT_A) {
		sc->msk_intrmask |= Y2_IS_PORT_A;
		sc->msk_intrhwemask |= Y2_HWE_L1_MASK;
	} else {
		sc->msk_intrmask |= Y2_IS_PORT_B;
		sc->msk_intrhwemask |= Y2_HWE_L2_MASK;
	}
	/* Configure IRQ moderation mask. */
	CSR_WRITE_4(sc, B2_IRQM_MSK, sc->msk_intrmask);
	if (sc->msk_int_holdoff > 0) {
		/* Configure initial IRQ moderation timer value. */
		CSR_WRITE_4(sc, B2_IRQM_INI,
		    MSK_USECS(sc, sc->msk_int_holdoff));
		CSR_WRITE_4(sc, B2_IRQM_VAL,
		    MSK_USECS(sc, sc->msk_int_holdoff));
		/* Start IRQ moderation. */
		CSR_WRITE_1(sc, B2_IRQM_CTRL, TIM_START);
	}
	CSR_WRITE_4(sc, B0_HWE_IMSK, sc->msk_intrhwemask);
	CSR_READ_4(sc, B0_HWE_IMSK);
	CSR_WRITE_4(sc, B0_IMSK, sc->msk_intrmask);
	CSR_READ_4(sc, B0_IMSK);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	sc_if->msk_flags &= ~MSK_FLAG_LINK;
	mii_mediachg(mii);

	callout_reset(&sc_if->msk_tick_ch, hz, msk_tick, sc_if);
}