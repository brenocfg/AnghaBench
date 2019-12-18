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
typedef  int uint32_t ;
struct tsec_softc {int tsec_tx_raddr; int tsec_rx_raddr; int /*<<< orphan*/  tsec_callout; scalar_t__ tsec_watchdog; int /*<<< orphan*/  tsec_if_flags; scalar_t__ is_etsec; int /*<<< orphan*/  tsec_rx_dmap; int /*<<< orphan*/  tsec_rx_dtag; TYPE_1__* rx_data; int /*<<< orphan*/  tsec_tx_dmap; int /*<<< orphan*/  tsec_tx_dtag; int /*<<< orphan*/  tsec_mii; struct ifnet* tsec_ifp; struct tsec_desc* tsec_rx_vaddr; struct tsec_desc* tsec_tx_vaddr; } ;
struct tsec_desc {int flags; scalar_t__ length; scalar_t__ bufptr; } ;
struct ifnet {int if_drv_flags; int if_capenable; int /*<<< orphan*/  if_flags; int /*<<< orphan*/  if_mtu; } ;
struct TYPE_2__ {scalar_t__ paddr; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int MCLBYTES ; 
 int TSEC_ATTR_RBDSEN ; 
 int TSEC_ATTR_RDSEN ; 
 int TSEC_ECNTRL_R100M ; 
 int TSEC_ECNTRL_SGMIIM ; 
 int TSEC_ECNTRL_STEN ; 
 int TSEC_ECNTRL_TBIM ; 
 int TSEC_FIFO_PAUSE_CTRL_EN ; 
 int /*<<< orphan*/  TSEC_GLOBAL_LOCK_ASSERT (struct tsec_softc*) ; 
 int TSEC_MACCFG1_RX_EN ; 
 int TSEC_MACCFG1_TX_EN ; 
 int TSEC_MACCFG2_FULLDUPLEX ; 
 int TSEC_MACCFG2_GMII ; 
 int TSEC_MACCFG2_PADCRC ; 
 int TSEC_MACCFG2_PRECNT ; 
 int /*<<< orphan*/  TSEC_MIIMCFG_CLKDIV28 ; 
 int /*<<< orphan*/  TSEC_MIIMCFG_RESETMGMT ; 
 int /*<<< orphan*/  TSEC_MIIMIND_BUSY ; 
 int TSEC_MIN_FRAME_SIZE ; 
 int /*<<< orphan*/  TSEC_PHY_LOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_PHY_UNLOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_PHY_WRITE (struct tsec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TSEC_READ (struct tsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSEC_REG_ATTR ; 
 int /*<<< orphan*/  TSEC_REG_ATTRELI ; 
 int /*<<< orphan*/  TSEC_REG_ECNTRL ; 
 int /*<<< orphan*/  TSEC_REG_FIFO_PAUSE_CTRL ; 
 int /*<<< orphan*/  TSEC_REG_GADDR0 ; 
 int /*<<< orphan*/  TSEC_REG_GADDR1 ; 
 int /*<<< orphan*/  TSEC_REG_GADDR2 ; 
 int /*<<< orphan*/  TSEC_REG_GADDR3 ; 
 int /*<<< orphan*/  TSEC_REG_GADDR4 ; 
 int /*<<< orphan*/  TSEC_REG_GADDR5 ; 
 int /*<<< orphan*/  TSEC_REG_GADDR6 ; 
 int /*<<< orphan*/  TSEC_REG_GADDR7 ; 
 int /*<<< orphan*/  TSEC_REG_IADDR0 ; 
 int /*<<< orphan*/  TSEC_REG_IADDR1 ; 
 int /*<<< orphan*/  TSEC_REG_IADDR2 ; 
 int /*<<< orphan*/  TSEC_REG_IADDR3 ; 
 int /*<<< orphan*/  TSEC_REG_IADDR4 ; 
 int /*<<< orphan*/  TSEC_REG_IADDR5 ; 
 int /*<<< orphan*/  TSEC_REG_IADDR6 ; 
 int /*<<< orphan*/  TSEC_REG_IADDR7 ; 
 int /*<<< orphan*/  TSEC_REG_ID2 ; 
 int /*<<< orphan*/  TSEC_REG_IEVENT ; 
 int /*<<< orphan*/  TSEC_REG_MACCFG1 ; 
 int /*<<< orphan*/  TSEC_REG_MACCFG2 ; 
 int /*<<< orphan*/  TSEC_REG_MIIMCFG ; 
 int /*<<< orphan*/  TSEC_REG_MINFLR ; 
 int /*<<< orphan*/  TSEC_REG_MON_CAM1 ; 
 int /*<<< orphan*/  TSEC_REG_MON_CAM2 ; 
 int /*<<< orphan*/  TSEC_REG_MON_TLCL ; 
 int /*<<< orphan*/  TSEC_REG_MON_TMCL ; 
 int /*<<< orphan*/  TSEC_REG_MON_TNCL ; 
 int /*<<< orphan*/  TSEC_REG_MON_TSCL ; 
 int /*<<< orphan*/  TSEC_REG_MON_TXCL ; 
 int /*<<< orphan*/  TSEC_REG_MRBLR ; 
 int /*<<< orphan*/  TSEC_REG_RBASE ; 
 int /*<<< orphan*/  TSEC_REG_RCTRL ; 
 int /*<<< orphan*/  TSEC_REG_TBASE ; 
 int /*<<< orphan*/  TSEC_REG_TBIPA ; 
 int TSEC_RXBD_E ; 
 int TSEC_RXBD_I ; 
 int TSEC_RXBD_W ; 
 int TSEC_RX_NUM_DESC ; 
 int TSEC_TXBD_W ; 
 int TSEC_TX_NUM_DESC ; 
 int /*<<< orphan*/  TSEC_TX_RX_COUNTERS_INIT (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_WRITE (struct tsec_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tsec_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  mii_mediachg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsec_dma_ctl (struct tsec_softc*,int) ; 
 int /*<<< orphan*/  tsec_intrs_ctl (struct tsec_softc*,int) ; 
 int tsec_mii_wait (struct tsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsec_offload_setup (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_reset_mac (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_set_mac_address (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_set_mtu (struct tsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsec_setup_multicast (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_stop (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_tick ; 

__attribute__((used)) static void
tsec_init_locked(struct tsec_softc *sc)
{
	struct tsec_desc *tx_desc = sc->tsec_tx_vaddr;
	struct tsec_desc *rx_desc = sc->tsec_rx_vaddr;
	struct ifnet *ifp = sc->tsec_ifp;
	uint32_t val, i;
	int timeout;

	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		return;

	TSEC_GLOBAL_LOCK_ASSERT(sc);
	tsec_stop(sc);

	/*
	 * These steps are according to the MPC8555E PowerQUICCIII RM:
	 * 14.7 Initialization/Application Information
	 */

	/* Step 1: soft reset MAC */
	tsec_reset_mac(sc);

	/* Step 2: Initialize MACCFG2 */
	TSEC_WRITE(sc, TSEC_REG_MACCFG2,
	    TSEC_MACCFG2_FULLDUPLEX |	/* Full Duplex = 1 */
	    TSEC_MACCFG2_PADCRC |	/* PAD/CRC append */
	    TSEC_MACCFG2_GMII |		/* I/F Mode bit */
	    TSEC_MACCFG2_PRECNT		/* Preamble count = 7 */
	);

	/* Step 3: Initialize ECNTRL
	 * While the documentation states that R100M is ignored if RPM is
	 * not set, it does seem to be needed to get the orange boxes to
	 * work (which have a Marvell 88E1111 PHY). Go figure.
	 */

	/*
	 * XXX kludge - use circumstancial evidence to program ECNTRL
	 * correctly. Ideally we need some board information to guide
	 * us here.
	 */
	i = TSEC_READ(sc, TSEC_REG_ID2);
	val = (i & 0xffff)
	    ? (TSEC_ECNTRL_TBIM | TSEC_ECNTRL_SGMIIM)	/* Sumatra */
	    : TSEC_ECNTRL_R100M;			/* Orange + CDS */
	TSEC_WRITE(sc, TSEC_REG_ECNTRL, TSEC_ECNTRL_STEN | val);

	/* Step 4: Initialize MAC station address */
	tsec_set_mac_address(sc);

	/*
	 * Step 5: Assign a Physical address to the TBI so as to not conflict
	 * with the external PHY physical address
	 */
	TSEC_WRITE(sc, TSEC_REG_TBIPA, 5);

	TSEC_PHY_LOCK(sc);

	/* Step 6: Reset the management interface */
	TSEC_PHY_WRITE(sc, TSEC_REG_MIIMCFG, TSEC_MIIMCFG_RESETMGMT);

	/* Step 7: Setup the MII Mgmt clock speed */
	TSEC_PHY_WRITE(sc, TSEC_REG_MIIMCFG, TSEC_MIIMCFG_CLKDIV28);

	/* Step 8: Read MII Mgmt indicator register and check for Busy = 0 */
	timeout = tsec_mii_wait(sc, TSEC_MIIMIND_BUSY);

	TSEC_PHY_UNLOCK(sc);
	if (timeout) {
		if_printf(ifp, "tsec_init_locked(): Mgmt busy timeout\n");
		return;
	}

	/* Step 9: Setup the MII Mgmt */
	mii_mediachg(sc->tsec_mii);

	/* Step 10: Clear IEVENT register */
	TSEC_WRITE(sc, TSEC_REG_IEVENT, 0xffffffff);

	/* Step 11: Enable interrupts */
#ifdef DEVICE_POLLING
	/*
	 * ...only if polling is not turned on. Disable interrupts explicitly
	 * if polling is enabled.
	 */
	if (ifp->if_capenable & IFCAP_POLLING )
		tsec_intrs_ctl(sc, 0);
	else
#endif /* DEVICE_POLLING */
	tsec_intrs_ctl(sc, 1);

	/* Step 12: Initialize IADDRn */
	TSEC_WRITE(sc, TSEC_REG_IADDR0, 0);
	TSEC_WRITE(sc, TSEC_REG_IADDR1, 0);
	TSEC_WRITE(sc, TSEC_REG_IADDR2, 0);
	TSEC_WRITE(sc, TSEC_REG_IADDR3, 0);
	TSEC_WRITE(sc, TSEC_REG_IADDR4, 0);
	TSEC_WRITE(sc, TSEC_REG_IADDR5, 0);
	TSEC_WRITE(sc, TSEC_REG_IADDR6, 0);
	TSEC_WRITE(sc, TSEC_REG_IADDR7, 0);

	/* Step 13: Initialize GADDRn */
	TSEC_WRITE(sc, TSEC_REG_GADDR0, 0);
	TSEC_WRITE(sc, TSEC_REG_GADDR1, 0);
	TSEC_WRITE(sc, TSEC_REG_GADDR2, 0);
	TSEC_WRITE(sc, TSEC_REG_GADDR3, 0);
	TSEC_WRITE(sc, TSEC_REG_GADDR4, 0);
	TSEC_WRITE(sc, TSEC_REG_GADDR5, 0);
	TSEC_WRITE(sc, TSEC_REG_GADDR6, 0);
	TSEC_WRITE(sc, TSEC_REG_GADDR7, 0);

	/* Step 14: Initialize RCTRL */
	TSEC_WRITE(sc, TSEC_REG_RCTRL, 0);

	/* Step 15: Initialize DMACTRL */
	tsec_dma_ctl(sc, 1);

	/* Step 16: Initialize FIFO_PAUSE_CTRL */
	TSEC_WRITE(sc, TSEC_REG_FIFO_PAUSE_CTRL, TSEC_FIFO_PAUSE_CTRL_EN);

	/*
	 * Step 17: Initialize transmit/receive descriptor rings.
	 * Initialize TBASE and RBASE.
	 */
	TSEC_WRITE(sc, TSEC_REG_TBASE, sc->tsec_tx_raddr);
	TSEC_WRITE(sc, TSEC_REG_RBASE, sc->tsec_rx_raddr);

	for (i = 0; i < TSEC_TX_NUM_DESC; i++) {
		tx_desc[i].bufptr = 0;
		tx_desc[i].length = 0;
		tx_desc[i].flags = ((i == TSEC_TX_NUM_DESC - 1) ?
		    TSEC_TXBD_W : 0);
	}
	bus_dmamap_sync(sc->tsec_tx_dtag, sc->tsec_tx_dmap,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	for (i = 0; i < TSEC_RX_NUM_DESC; i++) {
		rx_desc[i].bufptr = sc->rx_data[i].paddr;
		rx_desc[i].length = 0;
		rx_desc[i].flags = TSEC_RXBD_E | TSEC_RXBD_I |
		    ((i == TSEC_RX_NUM_DESC - 1) ? TSEC_RXBD_W : 0);
	}
	bus_dmamap_sync(sc->tsec_rx_dtag, sc->tsec_rx_dmap,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	/* Step 18: Initialize the maximum receive buffer length */
	TSEC_WRITE(sc, TSEC_REG_MRBLR, MCLBYTES);

	/* Step 19: Configure ethernet frame sizes */
	TSEC_WRITE(sc, TSEC_REG_MINFLR, TSEC_MIN_FRAME_SIZE);
	tsec_set_mtu(sc, ifp->if_mtu);

	/* Step 20: Enable Rx and RxBD sdata snooping */
	TSEC_WRITE(sc, TSEC_REG_ATTR, TSEC_ATTR_RDSEN | TSEC_ATTR_RBDSEN);
	TSEC_WRITE(sc, TSEC_REG_ATTRELI, 0);

	/* Step 21: Reset collision counters in hardware */
	TSEC_WRITE(sc, TSEC_REG_MON_TSCL, 0);
	TSEC_WRITE(sc, TSEC_REG_MON_TMCL, 0);
	TSEC_WRITE(sc, TSEC_REG_MON_TLCL, 0);
	TSEC_WRITE(sc, TSEC_REG_MON_TXCL, 0);
	TSEC_WRITE(sc, TSEC_REG_MON_TNCL, 0);

	/* Step 22: Mask all CAM interrupts */
	TSEC_WRITE(sc, TSEC_REG_MON_CAM1, 0xffffffff);
	TSEC_WRITE(sc, TSEC_REG_MON_CAM2, 0xffffffff);

	/* Step 23: Enable Rx and Tx */
	val = TSEC_READ(sc, TSEC_REG_MACCFG1);
	val |= (TSEC_MACCFG1_RX_EN | TSEC_MACCFG1_TX_EN);
	TSEC_WRITE(sc, TSEC_REG_MACCFG1, val);

	/* Step 24: Reset TSEC counters for Tx and Rx rings */
	TSEC_TX_RX_COUNTERS_INIT(sc);

	/* Step 25: Setup TCP/IP Off-Load engine */
	if (sc->is_etsec)
		tsec_offload_setup(sc);

	/* Step 26: Setup multicast filters */
	tsec_setup_multicast(sc);
	
	/* Step 27: Activate network interface */
	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
	sc->tsec_if_flags = ifp->if_flags;
	sc->tsec_watchdog = 0;

	/* Schedule watchdog timeout */
	callout_reset(&sc->tsec_callout, hz, tsec_tick, sc);
}