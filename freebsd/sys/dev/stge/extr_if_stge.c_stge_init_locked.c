#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct stge_softc {int sc_txthresh; int sc_IntEnable; unsigned int sc_DMACtrl; int sc_if_framesize; int sc_rev; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_tick_ch; scalar_t__ sc_link; int /*<<< orphan*/  sc_rxint_dmawait; int /*<<< orphan*/  sc_rxint_nframe; int /*<<< orphan*/  sc_miibus; struct ifnet* sc_ifp; } ;
struct mii_data {int dummy; } ;
struct ifnet {int if_drv_flags; int if_capenable; int if_mtu; } ;

/* Variables and functions */
 int CSR_READ_2 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 unsigned int CSR_READ_4 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct stge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct stge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct stge_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int DMAC_TxBurstLimit (int) ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int ETHER_CRC_LEN ; 
 int ETHER_HDR_LEN ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int IS_HostError ; 
 int IS_RFDListEnd ; 
 int IS_RxDMAComplete ; 
 int IS_TxComplete ; 
 int IS_TxDMAComplete ; 
 int /*<<< orphan*/  MC_IFS96bit ; 
 unsigned int MC_IFSSelect (int /*<<< orphan*/ ) ; 
 unsigned int MC_MASK ; 
 unsigned int MC_RxEnable ; 
 unsigned int MC_StatisticsEnable ; 
 unsigned int MC_TxEnable ; 
 unsigned int RDIC_RxDMAWaitTime (int /*<<< orphan*/ ) ; 
 unsigned int RDIC_RxFrameCount (int /*<<< orphan*/ ) ; 
 unsigned int STGE_ADDR_HI (int /*<<< orphan*/ ) ; 
 unsigned int STGE_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STGE_DMACtrl ; 
 int /*<<< orphan*/  STGE_DebugCtrl ; 
 int /*<<< orphan*/  STGE_FlowOffThresh ; 
 int /*<<< orphan*/  STGE_FlowOnTresh ; 
 int /*<<< orphan*/  STGE_IntEnable ; 
 int /*<<< orphan*/  STGE_LOCK_ASSERT (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_MACCtrl ; 
 int /*<<< orphan*/  STGE_MaxFrameSize ; 
 int /*<<< orphan*/  STGE_RESET_FULL ; 
 int /*<<< orphan*/  STGE_RFDListPtrHi ; 
 int /*<<< orphan*/  STGE_RFDListPtrLo ; 
 int /*<<< orphan*/  STGE_RMONStatisticsMask ; 
 int /*<<< orphan*/  STGE_RXINT_USECS2TICK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STGE_RX_RING_ADDR (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STGE_RxDMABurstThresh ; 
 int /*<<< orphan*/  STGE_RxDMAIntCtrl ; 
 int /*<<< orphan*/  STGE_RxDMAPollPeriod ; 
 int /*<<< orphan*/  STGE_RxDMAUrgentThresh ; 
 int /*<<< orphan*/  STGE_RxEarlyThresh ; 
 int /*<<< orphan*/  STGE_StationAddress0 ; 
 int /*<<< orphan*/  STGE_StationAddress1 ; 
 int /*<<< orphan*/  STGE_StationAddress2 ; 
 int /*<<< orphan*/  STGE_StatisticsMask ; 
 int /*<<< orphan*/  STGE_TFDListPtrHi ; 
 int /*<<< orphan*/  STGE_TFDListPtrLo ; 
 int /*<<< orphan*/  STGE_TX_RING_ADDR (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STGE_TxDMABurstThresh ; 
 int /*<<< orphan*/  STGE_TxDMAPollPeriod ; 
 int /*<<< orphan*/  STGE_TxDMAUrgentThresh ; 
 int /*<<< orphan*/  STGE_TxStartThresh ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stge_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 
 int stge_init_rx_ring (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_init_tx_ring (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_reset (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stge_set_filter (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_set_multi (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_start_rx (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_start_tx (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_stop (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_tick ; 
 int /*<<< orphan*/  stge_vlan_setup (struct stge_softc*) ; 

__attribute__((used)) static void
stge_init_locked(struct stge_softc *sc)
{
	struct ifnet *ifp;
	struct mii_data *mii;
	uint16_t eaddr[3];
	uint32_t v;
	int error;

	STGE_LOCK_ASSERT(sc);

	ifp = sc->sc_ifp;
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;
	mii = device_get_softc(sc->sc_miibus);

	/*
	 * Cancel any pending I/O.
	 */
	stge_stop(sc);

	/*
	 * Reset the chip to a known state.
	 */
	stge_reset(sc, STGE_RESET_FULL);

	/* Init descriptors. */
	error = stge_init_rx_ring(sc);
        if (error != 0) {
                device_printf(sc->sc_dev,
                    "initialization failed: no memory for rx buffers\n");
                stge_stop(sc);
		goto out;
        }
	stge_init_tx_ring(sc);

	/* Set the station address. */
	bcopy(IF_LLADDR(ifp), eaddr, ETHER_ADDR_LEN);
	CSR_WRITE_2(sc, STGE_StationAddress0, htole16(eaddr[0]));
	CSR_WRITE_2(sc, STGE_StationAddress1, htole16(eaddr[1]));
	CSR_WRITE_2(sc, STGE_StationAddress2, htole16(eaddr[2]));

	/*
	 * Set the statistics masks.  Disable all the RMON stats,
	 * and disable selected stats in the non-RMON stats registers.
	 */
	CSR_WRITE_4(sc, STGE_RMONStatisticsMask, 0xffffffff);
	CSR_WRITE_4(sc, STGE_StatisticsMask,
	    (1U << 1) | (1U << 2) | (1U << 3) | (1U << 4) | (1U << 5) |
	    (1U << 6) | (1U << 7) | (1U << 8) | (1U << 9) | (1U << 10) |
	    (1U << 13) | (1U << 14) | (1U << 15) | (1U << 19) | (1U << 20) |
	    (1U << 21));

	/* Set up the receive filter. */
	stge_set_filter(sc);
	/* Program multicast filter. */
	stge_set_multi(sc);

	/*
	 * Give the transmit and receive ring to the chip.
	 */
	CSR_WRITE_4(sc, STGE_TFDListPtrHi,
	    STGE_ADDR_HI(STGE_TX_RING_ADDR(sc, 0)));
	CSR_WRITE_4(sc, STGE_TFDListPtrLo,
	    STGE_ADDR_LO(STGE_TX_RING_ADDR(sc, 0)));

	CSR_WRITE_4(sc, STGE_RFDListPtrHi,
	    STGE_ADDR_HI(STGE_RX_RING_ADDR(sc, 0)));
	CSR_WRITE_4(sc, STGE_RFDListPtrLo,
	    STGE_ADDR_LO(STGE_RX_RING_ADDR(sc, 0)));

	/*
	 * Initialize the Tx auto-poll period.  It's OK to make this number
	 * large (255 is the max, but we use 127) -- we explicitly kick the
	 * transmit engine when there's actually a packet.
	 */
	CSR_WRITE_1(sc, STGE_TxDMAPollPeriod, 127);

	/* ..and the Rx auto-poll period. */
	CSR_WRITE_1(sc, STGE_RxDMAPollPeriod, 1);

	/* Initialize the Tx start threshold. */
	CSR_WRITE_2(sc, STGE_TxStartThresh, sc->sc_txthresh);

	/* Rx DMA thresholds, from Linux */
	CSR_WRITE_1(sc, STGE_RxDMABurstThresh, 0x30);
	CSR_WRITE_1(sc, STGE_RxDMAUrgentThresh, 0x30);

	/* Rx early threhold, from Linux */
	CSR_WRITE_2(sc, STGE_RxEarlyThresh, 0x7ff);

	/* Tx DMA thresholds, from Linux */
	CSR_WRITE_1(sc, STGE_TxDMABurstThresh, 0x30);
	CSR_WRITE_1(sc, STGE_TxDMAUrgentThresh, 0x04);

	/*
	 * Initialize the Rx DMA interrupt control register.  We
	 * request an interrupt after every incoming packet, but
	 * defer it for sc_rxint_dmawait us. When the number of
	 * interrupts pending reaches STGE_RXINT_NFRAME, we stop
	 * deferring the interrupt, and signal it immediately.
	 */
	CSR_WRITE_4(sc, STGE_RxDMAIntCtrl,
	    RDIC_RxFrameCount(sc->sc_rxint_nframe) |
	    RDIC_RxDMAWaitTime(STGE_RXINT_USECS2TICK(sc->sc_rxint_dmawait)));

	/*
	 * Initialize the interrupt mask.
	 */
	sc->sc_IntEnable = IS_HostError | IS_TxComplete |
	    IS_TxDMAComplete | IS_RxDMAComplete | IS_RFDListEnd;
#ifdef DEVICE_POLLING
	/* Disable interrupts if we are polling. */
	if ((ifp->if_capenable & IFCAP_POLLING) != 0)
		CSR_WRITE_2(sc, STGE_IntEnable, 0);
	else
#endif
	CSR_WRITE_2(sc, STGE_IntEnable, sc->sc_IntEnable);

	/*
	 * Configure the DMA engine.
	 * XXX Should auto-tune TxBurstLimit.
	 */
	CSR_WRITE_4(sc, STGE_DMACtrl, sc->sc_DMACtrl | DMAC_TxBurstLimit(3));

	/*
	 * Send a PAUSE frame when we reach 29,696 bytes in the Rx
	 * FIFO, and send an un-PAUSE frame when we reach 3056 bytes
	 * in the Rx FIFO.
	 */
	CSR_WRITE_2(sc, STGE_FlowOnTresh, 29696 / 16);
	CSR_WRITE_2(sc, STGE_FlowOffThresh, 3056 / 16);

	/*
	 * Set the maximum frame size.
	 */
	sc->sc_if_framesize = ifp->if_mtu + ETHER_HDR_LEN + ETHER_CRC_LEN;
	CSR_WRITE_2(sc, STGE_MaxFrameSize, sc->sc_if_framesize);

	/*
	 * Initialize MacCtrl -- do it before setting the media,
	 * as setting the media will actually program the register.
	 *
	 * Note: We have to poke the IFS value before poking
	 * anything else.
	 */
	/* Tx/Rx MAC should be disabled before programming IFS.*/
	CSR_WRITE_4(sc, STGE_MACCtrl, MC_IFSSelect(MC_IFS96bit));

	stge_vlan_setup(sc);

	if (sc->sc_rev >= 6) {		/* >= B.2 */
		/* Multi-frag frame bug work-around. */
		CSR_WRITE_2(sc, STGE_DebugCtrl,
		    CSR_READ_2(sc, STGE_DebugCtrl) | 0x0200);

		/* Tx Poll Now bug work-around. */
		CSR_WRITE_2(sc, STGE_DebugCtrl,
		    CSR_READ_2(sc, STGE_DebugCtrl) | 0x0010);
		/* Tx Poll Now bug work-around. */
		CSR_WRITE_2(sc, STGE_DebugCtrl,
		    CSR_READ_2(sc, STGE_DebugCtrl) | 0x0020);
	}

	v = CSR_READ_4(sc, STGE_MACCtrl) & MC_MASK;
	v |= MC_StatisticsEnable | MC_TxEnable | MC_RxEnable;
	CSR_WRITE_4(sc, STGE_MACCtrl, v);
	/*
	 * It seems that transmitting frames without checking the state of
	 * Rx/Tx MAC wedge the hardware.
	 */
	stge_start_tx(sc);
	stge_start_rx(sc);

	sc->sc_link = 0;
	/*
	 * Set the current media.
	 */
	mii_mediachg(mii);

	/*
	 * Start the one second MII clock.
	 */
	callout_reset(&sc->sc_tick_ch, hz, stge_tick, sc);

	/*
	 * ...all done!
	 */
	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

 out:
	if (error != 0)
		device_printf(sc->sc_dev, "interface not running\n");
}