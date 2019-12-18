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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct mii_data {int dummy; } ;
struct ifnet {int if_drv_flags; scalar_t__ if_mtu; int if_capenable; } ;
struct ether_vlan_header {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  age_smb_block_paddr; int /*<<< orphan*/  age_cmb_block_paddr; int /*<<< orphan*/  age_tx_ring_paddr; int /*<<< orphan*/  age_rr_ring_paddr; int /*<<< orphan*/  age_rx_ring_paddr; } ;
struct age_softc {int age_int_mod; int age_max_frame_size; int age_flags; int age_chip_rev; int age_dma_rd_burst; int age_dma_wr_burst; int /*<<< orphan*/  age_tick_ch; int /*<<< orphan*/  age_dev; TYPE_1__ age_rdata; int /*<<< orphan*/  age_miibus; struct ifnet* age_ifp; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int AGE_ADDR_HI (int /*<<< orphan*/ ) ; 
 int AGE_ADDR_LO (int /*<<< orphan*/ ) ; 
 int AGE_CMB_WR_THRESH ; 
 int AGE_CMB_WR_TIMER ; 
 int /*<<< orphan*/  AGE_COMMIT_MBOX (struct age_softc*) ; 
 int AGE_CSMB_CTRL ; 
 int AGE_DESC_ADDR_HI ; 
 int AGE_DESC_CMB_ADDR_LO ; 
 int AGE_DESC_RD_ADDR_LO ; 
 int AGE_DESC_RRD_ADDR_LO ; 
 int AGE_DESC_RRD_RD_CNT ; 
 int AGE_DESC_SMB_ADDR_LO ; 
 int AGE_DESC_TPD_ADDR_LO ; 
 int AGE_DESC_TPD_CNT ; 
 int AGE_DMA_BLOCK ; 
 int AGE_DMA_CFG ; 
 int AGE_FLAG_LINK ; 
 int AGE_FLAG_PCIE ; 
 int AGE_FRAME_SIZE ; 
 int AGE_HDPX_CFG ; 
 int /*<<< orphan*/  AGE_IM_TIMER ; 
 int AGE_INTRS ; 
 int /*<<< orphan*/  AGE_INTR_CLR_TIMER ; 
 int AGE_INTR_MASK ; 
 int AGE_INTR_STATUS ; 
 int AGE_IPG_IFG_CFG ; 
 int /*<<< orphan*/  AGE_LOCK_ASSERT (struct age_softc*) ; 
 int AGE_MAC_CFG ; 
 int AGE_MASTER_CFG ; 
 int AGE_PAR0 ; 
 int AGE_PAR1 ; 
 int AGE_RR_RING_CNT ; 
 int AGE_RXQ_CFG ; 
 int AGE_RXQ_FIFO_PAUSE_THRESH ; 
 int AGE_RXQ_JUMBO_CFG ; 
 int AGE_RXQ_RRD_PAUSE_THRESH ; 
 int AGE_RX_RING_CNT ; 
 int AGE_SMB_TIMER ; 
 int AGE_SRAM_RRD_LEN ; 
 int AGE_SRAM_RX_FIFO_LEN ; 
 int AGE_TXQ_CFG ; 
 int AGE_TX_JUMBO_TPD_TH_IPG ; 
 int AGE_TX_RING_CNT ; 
 int AGE_USECS (int) ; 
 int AGE_WOL_CFG ; 
 int CMB_WR_THRESH_RRD_DEFAULT ; 
 int CMB_WR_THRESH_RRD_MASK ; 
 int CMB_WR_THRESH_RRD_SHIFT ; 
 int CMB_WR_THRESH_TPD_DEFAULT ; 
 int CMB_WR_THRESH_TPD_MASK ; 
 int CMB_WR_THRESH_TPD_SHIFT ; 
 int CMB_WR_TIMER_RX_MASK ; 
 int CMB_WR_TIMER_RX_SHIFT ; 
 int CMB_WR_TIMER_TX_MASK ; 
 int CMB_WR_TIMER_TX_SHIFT ; 
 int CSMB_CTRL_CMB_ENB ; 
 int CSMB_CTRL_SMB_ENB ; 
 int CSR_READ_4 (struct age_softc*,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct age_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct age_softc*,int,int) ; 
 int DESC_RD_CNT_MASK ; 
 int DESC_RD_CNT_SHIFT ; 
 int DESC_RRD_CNT_MASK ; 
 int DESC_RRD_CNT_SHIFT ; 
 int DESC_TPD_CNT_MASK ; 
 int DESC_TPD_CNT_SHIFT ; 
 int DMA_BLOCK_LOAD ; 
 int DMA_CFG_ENH_ORDER ; 
 int DMA_CFG_RCB_64 ; 
 int DMA_CFG_RD_ENB ; 
 int DMA_CFG_WR_ENB ; 
 scalar_t__ ETHERMTU ; 
 int ETHER_ADDR_LEN ; 
 scalar_t__ ETHER_CRC_LEN ; 
 scalar_t__ ETHER_HDR_LEN ; 
 int HDPX_CFG_ABEBT_DEFAULT ; 
 int HDPX_CFG_ABEBT_MASK ; 
 int HDPX_CFG_ABEBT_SHIFT ; 
 int HDPX_CFG_EXC_DEF_EN ; 
 int HDPX_CFG_JAMIPG_DEFAULT ; 
 int HDPX_CFG_JAMIPG_MASK ; 
 int HDPX_CFG_JAMIPG_SHIFT ; 
 int HDPX_CFG_LCOL_DEFAULT ; 
 int HDPX_CFG_LCOL_MASK ; 
 int HDPX_CFG_LCOL_SHIFT ; 
 int HDPX_CFG_RETRY_DEFAULT ; 
 int HDPX_CFG_RETRY_MASK ; 
 int HDPX_CFG_RETRY_SHIFT ; 
 int IFCAP_RXCSUM ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int IPG_IFG_IPG1_DEFAULT ; 
 int IPG_IFG_IPG1_MASK ; 
 int IPG_IFG_IPG1_SHIFT ; 
 int IPG_IFG_IPG2_DEFAULT ; 
 int IPG_IFG_IPG2_MASK ; 
 int IPG_IFG_IPG2_SHIFT ; 
 int IPG_IFG_IPGT_DEFAULT ; 
 int IPG_IFG_IPGT_MASK ; 
 int IPG_IFG_IPGT_SHIFT ; 
 int IPG_IFG_MIFG_DEFAULT ; 
 int IPG_IFG_MIFG_MASK ; 
 int IPG_IFG_MIFG_SHIFT ; 
 int MAC_CFG_FULL_DUPLEX ; 
 int MAC_CFG_PREAMBLE_DEFAULT ; 
 int MAC_CFG_PREAMBLE_MASK ; 
 int MAC_CFG_PREAMBLE_SHIFT ; 
 int MAC_CFG_RXCSUM_ENB ; 
 int MAC_CFG_RX_ENB ; 
 int MAC_CFG_SPEED_1000 ; 
 int MAC_CFG_TX_AUTO_PAD ; 
 int MAC_CFG_TX_CRC_ENB ; 
 int MAC_CFG_TX_ENB ; 
 int MASTER_ITIMER_ENB ; 
 int MASTER_MTIMER_ENB ; 
 int RXQ_CFG_CUT_THROUGH_ENB ; 
 int RXQ_CFG_ENB ; 
 int RXQ_CFG_RD_BURST_DEFAULT ; 
 int RXQ_CFG_RD_BURST_MASK ; 
 int RXQ_CFG_RD_BURST_SHIFT ; 
 int RXQ_CFG_RD_PREF_MIN_IPG_DEFAULT ; 
 int RXQ_CFG_RD_PREF_MIN_IPG_MASK ; 
 int RXQ_CFG_RD_PREF_MIN_IPG_SHIFT ; 
 int RXQ_CFG_RRD_BURST_THRESH_DEFAULT ; 
 int RXQ_CFG_RRD_BURST_THRESH_MASK ; 
 int RXQ_CFG_RRD_BURST_THRESH_SHIFT ; 
 int RXQ_FIFO_PAUSE_THRESH_HI_MASK ; 
 int RXQ_FIFO_PAUSE_THRESH_HI_SHIFT ; 
 int RXQ_FIFO_PAUSE_THRESH_LO_MASK ; 
 int RXQ_FIFO_PAUSE_THRESH_LO_SHIFT ; 
 int RXQ_JUMBO_CFG_LKAH_DEFAULT ; 
 int RXQ_JUMBO_CFG_LKAH_MASK ; 
 int RXQ_JUMBO_CFG_LKAH_SHIFT ; 
 int RXQ_JUMBO_CFG_RRD_TIMER_MASK ; 
 int RXQ_JUMBO_CFG_RRD_TIMER_SHIFT ; 
 int RXQ_JUMBO_CFG_SZ_THRESH_MASK ; 
 int RXQ_JUMBO_CFG_SZ_THRESH_SHIFT ; 
 int RXQ_RRD_PAUSE_THRESH_HI_MASK ; 
 int RXQ_RRD_PAUSE_THRESH_HI_SHIFT ; 
 int RXQ_RRD_PAUSE_THRESH_LO_MASK ; 
 int RXQ_RRD_PAUSE_THRESH_LO_SHIFT ; 
 int TXQ_CFG_ENB ; 
 int TXQ_CFG_TPD_BURST_DEFAULT ; 
 int TXQ_CFG_TPD_BURST_MASK ; 
 int TXQ_CFG_TPD_BURST_SHIFT ; 
 int TXQ_CFG_TPD_FETCH_DEFAULT ; 
 int TXQ_CFG_TPD_FETCH_THRESH_MASK ; 
 int TXQ_CFG_TPD_FETCH_THRESH_SHIFT ; 
 int TXQ_CFG_TX_FIFO_BURST_DEFAULT ; 
 int TXQ_CFG_TX_FIFO_BURST_MASK ; 
 int TXQ_CFG_TX_FIFO_BURST_SHIFT ; 
 int TX_JUMBO_TPD_IPG_DEFAULT ; 
 int TX_JUMBO_TPD_IPG_MASK ; 
 int TX_JUMBO_TPD_IPG_SHIFT ; 
 int TX_JUMBO_TPD_TH_MASK ; 
 int TX_JUMBO_TPD_TH_SHIFT ; 
 int /*<<< orphan*/  age_init_cmb_block (struct age_softc*) ; 
 int /*<<< orphan*/  age_init_rr_ring (struct age_softc*) ; 
 int age_init_rx_ring (struct age_softc*) ; 
 int /*<<< orphan*/  age_init_smb_block (struct age_softc*) ; 
 int /*<<< orphan*/  age_init_tx_ring (struct age_softc*) ; 
 int /*<<< orphan*/  age_reset (struct age_softc*) ; 
 int /*<<< orphan*/  age_rxfilter (struct age_softc*) ; 
 int /*<<< orphan*/  age_rxvlan (struct age_softc*) ; 
 int /*<<< orphan*/  age_stop (struct age_softc*) ; 
 int /*<<< orphan*/  age_tick ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct age_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 
 int roundup (int,int) ; 

__attribute__((used)) static void
age_init_locked(struct age_softc *sc)
{
	struct ifnet *ifp;
	struct mii_data *mii;
	uint8_t eaddr[ETHER_ADDR_LEN];
	bus_addr_t paddr;
	uint32_t reg, fsize;
	uint32_t rxf_hi, rxf_lo, rrd_hi, rrd_lo;
	int error;

	AGE_LOCK_ASSERT(sc);

	ifp = sc->age_ifp;
	mii = device_get_softc(sc->age_miibus);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	/*
	 * Cancel any pending I/O.
	 */
	age_stop(sc);

	/*
	 * Reset the chip to a known state.
	 */
	age_reset(sc);

	/* Initialize descriptors. */
	error = age_init_rx_ring(sc);
        if (error != 0) {
                device_printf(sc->age_dev, "no memory for Rx buffers.\n");
                age_stop(sc);
		return;
        }
	age_init_rr_ring(sc);
	age_init_tx_ring(sc);
	age_init_cmb_block(sc);
	age_init_smb_block(sc);

	/* Reprogram the station address. */
	bcopy(IF_LLADDR(ifp), eaddr, ETHER_ADDR_LEN);
	CSR_WRITE_4(sc, AGE_PAR0,
	    eaddr[2] << 24 | eaddr[3] << 16 | eaddr[4] << 8 | eaddr[5]);
	CSR_WRITE_4(sc, AGE_PAR1, eaddr[0] << 8 | eaddr[1]);

	/* Set descriptor base addresses. */
	paddr = sc->age_rdata.age_tx_ring_paddr;
	CSR_WRITE_4(sc, AGE_DESC_ADDR_HI, AGE_ADDR_HI(paddr));
	paddr = sc->age_rdata.age_rx_ring_paddr;
	CSR_WRITE_4(sc, AGE_DESC_RD_ADDR_LO, AGE_ADDR_LO(paddr));
	paddr = sc->age_rdata.age_rr_ring_paddr;
	CSR_WRITE_4(sc, AGE_DESC_RRD_ADDR_LO, AGE_ADDR_LO(paddr));
	paddr = sc->age_rdata.age_tx_ring_paddr;
	CSR_WRITE_4(sc, AGE_DESC_TPD_ADDR_LO, AGE_ADDR_LO(paddr));
	paddr = sc->age_rdata.age_cmb_block_paddr;
	CSR_WRITE_4(sc, AGE_DESC_CMB_ADDR_LO, AGE_ADDR_LO(paddr));
	paddr = sc->age_rdata.age_smb_block_paddr;
	CSR_WRITE_4(sc, AGE_DESC_SMB_ADDR_LO, AGE_ADDR_LO(paddr));
	/* Set Rx/Rx return descriptor counter. */
	CSR_WRITE_4(sc, AGE_DESC_RRD_RD_CNT,
	    ((AGE_RR_RING_CNT << DESC_RRD_CNT_SHIFT) &
	    DESC_RRD_CNT_MASK) |
	    ((AGE_RX_RING_CNT << DESC_RD_CNT_SHIFT) & DESC_RD_CNT_MASK));
	/* Set Tx descriptor counter. */
	CSR_WRITE_4(sc, AGE_DESC_TPD_CNT,
	    (AGE_TX_RING_CNT << DESC_TPD_CNT_SHIFT) & DESC_TPD_CNT_MASK);

	/* Tell hardware that we're ready to load descriptors. */
	CSR_WRITE_4(sc, AGE_DMA_BLOCK, DMA_BLOCK_LOAD);

	/*
	 * Initialize mailbox register.
	 * Updated producer/consumer index information is exchanged
	 * through this mailbox register. However Tx producer and
	 * Rx return consumer/Rx producer are all shared such that
	 * it's hard to separate code path between Tx and Rx without
	 * locking. If L1 hardware have a separate mail box register
	 * for Tx and Rx consumer/producer management we could have
	 * indepent Tx/Rx handler which in turn Rx handler could have
	 * been run without any locking.
	 */
	AGE_COMMIT_MBOX(sc);

	/* Configure IPG/IFG parameters. */
	CSR_WRITE_4(sc, AGE_IPG_IFG_CFG,
	    ((IPG_IFG_IPG2_DEFAULT << IPG_IFG_IPG2_SHIFT) & IPG_IFG_IPG2_MASK) |
	    ((IPG_IFG_IPG1_DEFAULT << IPG_IFG_IPG1_SHIFT) & IPG_IFG_IPG1_MASK) |
	    ((IPG_IFG_MIFG_DEFAULT << IPG_IFG_MIFG_SHIFT) & IPG_IFG_MIFG_MASK) |
	    ((IPG_IFG_IPGT_DEFAULT << IPG_IFG_IPGT_SHIFT) & IPG_IFG_IPGT_MASK));

	/* Set parameters for half-duplex media. */
	CSR_WRITE_4(sc, AGE_HDPX_CFG,
	    ((HDPX_CFG_LCOL_DEFAULT << HDPX_CFG_LCOL_SHIFT) &
	    HDPX_CFG_LCOL_MASK) |
	    ((HDPX_CFG_RETRY_DEFAULT << HDPX_CFG_RETRY_SHIFT) &
	    HDPX_CFG_RETRY_MASK) | HDPX_CFG_EXC_DEF_EN |
	    ((HDPX_CFG_ABEBT_DEFAULT << HDPX_CFG_ABEBT_SHIFT) &
	    HDPX_CFG_ABEBT_MASK) |
	    ((HDPX_CFG_JAMIPG_DEFAULT << HDPX_CFG_JAMIPG_SHIFT) &
	    HDPX_CFG_JAMIPG_MASK));

	/* Configure interrupt moderation timer. */
	CSR_WRITE_2(sc, AGE_IM_TIMER, AGE_USECS(sc->age_int_mod));
	reg = CSR_READ_4(sc, AGE_MASTER_CFG);
	reg &= ~MASTER_MTIMER_ENB;
	if (AGE_USECS(sc->age_int_mod) == 0)
		reg &= ~MASTER_ITIMER_ENB;
	else
		reg |= MASTER_ITIMER_ENB;
	CSR_WRITE_4(sc, AGE_MASTER_CFG, reg);
	if (bootverbose)
		device_printf(sc->age_dev, "interrupt moderation is %d us.\n",
		    sc->age_int_mod);
	CSR_WRITE_2(sc, AGE_INTR_CLR_TIMER, AGE_USECS(1000));

	/* Set Maximum frame size but don't let MTU be lass than ETHER_MTU. */
	if (ifp->if_mtu < ETHERMTU)
		sc->age_max_frame_size = ETHERMTU;
	else
		sc->age_max_frame_size = ifp->if_mtu;
	sc->age_max_frame_size += ETHER_HDR_LEN +
	    sizeof(struct ether_vlan_header) + ETHER_CRC_LEN;
	CSR_WRITE_4(sc, AGE_FRAME_SIZE, sc->age_max_frame_size);
	/* Configure jumbo frame. */
	fsize = roundup(sc->age_max_frame_size, sizeof(uint64_t));
	CSR_WRITE_4(sc, AGE_RXQ_JUMBO_CFG,
	    (((fsize / sizeof(uint64_t)) <<
	    RXQ_JUMBO_CFG_SZ_THRESH_SHIFT) & RXQ_JUMBO_CFG_SZ_THRESH_MASK) |
	    ((RXQ_JUMBO_CFG_LKAH_DEFAULT <<
	    RXQ_JUMBO_CFG_LKAH_SHIFT) & RXQ_JUMBO_CFG_LKAH_MASK) |
	    ((AGE_USECS(8) << RXQ_JUMBO_CFG_RRD_TIMER_SHIFT) &
	    RXQ_JUMBO_CFG_RRD_TIMER_MASK));

	/* Configure flow-control parameters. From Linux. */
	if ((sc->age_flags & AGE_FLAG_PCIE) != 0) {
		/*
		 * Magic workaround for old-L1.
		 * Don't know which hw revision requires this magic.
		 */
		CSR_WRITE_4(sc, 0x12FC, 0x6500);
		/*
		 * Another magic workaround for flow-control mode
		 * change. From Linux.
		 */
		CSR_WRITE_4(sc, 0x1008, CSR_READ_4(sc, 0x1008) | 0x8000);
	}
	/*
	 * TODO
	 *  Should understand pause parameter relationships between FIFO
	 *  size and number of Rx descriptors and Rx return descriptors.
	 *
	 *  Magic parameters came from Linux.
	 */
	switch (sc->age_chip_rev) {
	case 0x8001:
	case 0x9001:
	case 0x9002:
	case 0x9003:
		rxf_hi = AGE_RX_RING_CNT / 16;
		rxf_lo = (AGE_RX_RING_CNT * 7) / 8;
		rrd_hi = (AGE_RR_RING_CNT * 7) / 8;
		rrd_lo = AGE_RR_RING_CNT / 16;
		break;
	default:
		reg = CSR_READ_4(sc, AGE_SRAM_RX_FIFO_LEN);
		rxf_lo = reg / 16;
		if (rxf_lo < 192)
			rxf_lo = 192;
		rxf_hi = (reg * 7) / 8;
		if (rxf_hi < rxf_lo)
			rxf_hi = rxf_lo + 16;
		reg = CSR_READ_4(sc, AGE_SRAM_RRD_LEN);
		rrd_lo = reg / 8;
		rrd_hi = (reg * 7) / 8;
		if (rrd_lo < 2)
			rrd_lo = 2;
		if (rrd_hi < rrd_lo)
			rrd_hi = rrd_lo + 3;
		break;
	}
	CSR_WRITE_4(sc, AGE_RXQ_FIFO_PAUSE_THRESH,
	    ((rxf_lo << RXQ_FIFO_PAUSE_THRESH_LO_SHIFT) &
	    RXQ_FIFO_PAUSE_THRESH_LO_MASK) |
	    ((rxf_hi << RXQ_FIFO_PAUSE_THRESH_HI_SHIFT) &
	    RXQ_FIFO_PAUSE_THRESH_HI_MASK));
	CSR_WRITE_4(sc, AGE_RXQ_RRD_PAUSE_THRESH,
	    ((rrd_lo << RXQ_RRD_PAUSE_THRESH_LO_SHIFT) &
	    RXQ_RRD_PAUSE_THRESH_LO_MASK) |
	    ((rrd_hi << RXQ_RRD_PAUSE_THRESH_HI_SHIFT) &
	    RXQ_RRD_PAUSE_THRESH_HI_MASK));

	/* Configure RxQ. */
	CSR_WRITE_4(sc, AGE_RXQ_CFG,
	    ((RXQ_CFG_RD_BURST_DEFAULT << RXQ_CFG_RD_BURST_SHIFT) &
	    RXQ_CFG_RD_BURST_MASK) |
	    ((RXQ_CFG_RRD_BURST_THRESH_DEFAULT <<
	    RXQ_CFG_RRD_BURST_THRESH_SHIFT) & RXQ_CFG_RRD_BURST_THRESH_MASK) |
	    ((RXQ_CFG_RD_PREF_MIN_IPG_DEFAULT <<
	    RXQ_CFG_RD_PREF_MIN_IPG_SHIFT) & RXQ_CFG_RD_PREF_MIN_IPG_MASK) |
	    RXQ_CFG_CUT_THROUGH_ENB | RXQ_CFG_ENB);

	/* Configure TxQ. */
	CSR_WRITE_4(sc, AGE_TXQ_CFG,
	    ((TXQ_CFG_TPD_BURST_DEFAULT << TXQ_CFG_TPD_BURST_SHIFT) &
	    TXQ_CFG_TPD_BURST_MASK) |
	    ((TXQ_CFG_TX_FIFO_BURST_DEFAULT << TXQ_CFG_TX_FIFO_BURST_SHIFT) &
	    TXQ_CFG_TX_FIFO_BURST_MASK) |
	    ((TXQ_CFG_TPD_FETCH_DEFAULT <<
	    TXQ_CFG_TPD_FETCH_THRESH_SHIFT) & TXQ_CFG_TPD_FETCH_THRESH_MASK) |
	    TXQ_CFG_ENB);

	CSR_WRITE_4(sc, AGE_TX_JUMBO_TPD_TH_IPG,
	    (((fsize / sizeof(uint64_t) << TX_JUMBO_TPD_TH_SHIFT)) &
	    TX_JUMBO_TPD_TH_MASK) |
	    ((TX_JUMBO_TPD_IPG_DEFAULT << TX_JUMBO_TPD_IPG_SHIFT) &
	    TX_JUMBO_TPD_IPG_MASK));
	/* Configure DMA parameters. */
	CSR_WRITE_4(sc, AGE_DMA_CFG,
	    DMA_CFG_ENH_ORDER | DMA_CFG_RCB_64 |
	    sc->age_dma_rd_burst | DMA_CFG_RD_ENB |
	    sc->age_dma_wr_burst | DMA_CFG_WR_ENB);

	/* Configure CMB DMA write threshold. */
	CSR_WRITE_4(sc, AGE_CMB_WR_THRESH,
	    ((CMB_WR_THRESH_RRD_DEFAULT << CMB_WR_THRESH_RRD_SHIFT) &
	    CMB_WR_THRESH_RRD_MASK) |
	    ((CMB_WR_THRESH_TPD_DEFAULT << CMB_WR_THRESH_TPD_SHIFT) &
	    CMB_WR_THRESH_TPD_MASK));

	/* Set CMB/SMB timer and enable them. */
	CSR_WRITE_4(sc, AGE_CMB_WR_TIMER,
	    ((AGE_USECS(2) << CMB_WR_TIMER_TX_SHIFT) & CMB_WR_TIMER_TX_MASK) |
	    ((AGE_USECS(2) << CMB_WR_TIMER_RX_SHIFT) & CMB_WR_TIMER_RX_MASK));
	/* Request SMB updates for every seconds. */
	CSR_WRITE_4(sc, AGE_SMB_TIMER, AGE_USECS(1000 * 1000));
	CSR_WRITE_4(sc, AGE_CSMB_CTRL, CSMB_CTRL_SMB_ENB | CSMB_CTRL_CMB_ENB);

	/*
	 * Disable all WOL bits as WOL can interfere normal Rx
	 * operation.
	 */
	CSR_WRITE_4(sc, AGE_WOL_CFG, 0);

	/*
	 * Configure Tx/Rx MACs.
	 *  - Auto-padding for short frames.
	 *  - Enable CRC generation.
	 *  Start with full-duplex/1000Mbps media. Actual reconfiguration
	 *  of MAC is followed after link establishment.
	 */
	CSR_WRITE_4(sc, AGE_MAC_CFG,
	    MAC_CFG_TX_CRC_ENB | MAC_CFG_TX_AUTO_PAD |
	    MAC_CFG_FULL_DUPLEX | MAC_CFG_SPEED_1000 |
	    ((MAC_CFG_PREAMBLE_DEFAULT << MAC_CFG_PREAMBLE_SHIFT) &
	    MAC_CFG_PREAMBLE_MASK));
	/* Set up the receive filter. */
	age_rxfilter(sc);
	age_rxvlan(sc);

	reg = CSR_READ_4(sc, AGE_MAC_CFG);
	if ((ifp->if_capenable & IFCAP_RXCSUM) != 0)
		reg |= MAC_CFG_RXCSUM_ENB;

	/* Ack all pending interrupts and clear it. */
	CSR_WRITE_4(sc, AGE_INTR_STATUS, 0);
	CSR_WRITE_4(sc, AGE_INTR_MASK, AGE_INTRS);

	/* Finally enable Tx/Rx MAC. */
	CSR_WRITE_4(sc, AGE_MAC_CFG, reg | MAC_CFG_TX_ENB | MAC_CFG_RX_ENB);

	sc->age_flags &= ~AGE_FLAG_LINK;
	/* Switch to the current media. */
	mii_mediachg(mii);

	callout_reset(&sc->age_tick_ch, hz, age_tick, sc);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
}