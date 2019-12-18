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
struct mii_data {int mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct jme_txdesc {scalar_t__ tx_ndesc; int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; } ;
struct TYPE_2__ {scalar_t__ jme_tx_cnt; scalar_t__ jme_rx_cons; int /*<<< orphan*/  jme_tx_tag; struct jme_txdesc* jme_txdesc; int /*<<< orphan*/ * jme_rxhead; } ;
struct jme_softc {int jme_flags; int jme_rxcsr; int jme_txcsr; int /*<<< orphan*/  jme_tq; int /*<<< orphan*/  jme_tick_ch; scalar_t__ jme_morework; TYPE_1__ jme_cdata; int /*<<< orphan*/  jme_int_task; scalar_t__ jme_watchdog_timer; struct ifnet* jme_ifp; int /*<<< orphan*/  jme_miibus; } ;
struct ifnet {int if_drv_flags; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int CSR_READ_4 (struct jme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct jme_softc*,int /*<<< orphan*/ ,int) ; 
 int GHC_TX_MAC_CLK_DIS ; 
 int GPREG1_RX_MAC_CLK_DIS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
#define  IFM_1000_T 130 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_AVALID ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int JME_ADDR_HI (int /*<<< orphan*/ ) ; 
 int JME_ADDR_LO (int /*<<< orphan*/ ) ; 
 int JME_FLAG_FASTETH ; 
 int JME_FLAG_LINK ; 
 int JME_FLAG_RXCLK ; 
 int JME_FLAG_TXCLK ; 
 int /*<<< orphan*/  JME_GHC ; 
 int /*<<< orphan*/  JME_GPREG1 ; 
 int JME_INTRS ; 
 int /*<<< orphan*/  JME_INTR_MASK_CLR ; 
 int /*<<< orphan*/  JME_INTR_MASK_SET ; 
 int /*<<< orphan*/  JME_LOCK (struct jme_softc*) ; 
 int /*<<< orphan*/  JME_RXCHAIN_RESET (struct jme_softc*) ; 
 int /*<<< orphan*/  JME_RXCSR ; 
 int /*<<< orphan*/  JME_RXDBA_HI ; 
 int /*<<< orphan*/  JME_RXDBA_LO ; 
 int /*<<< orphan*/  JME_RX_RING_ADDR (struct jme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JME_TXCSR ; 
 int /*<<< orphan*/  JME_TXDBA_HI ; 
 int /*<<< orphan*/  JME_TXDBA_LO ; 
 int /*<<< orphan*/  JME_TX_RING_ADDR (struct jme_softc*,int /*<<< orphan*/ ) ; 
 int JME_TX_RING_CNT ; 
 int /*<<< orphan*/  JME_UNLOCK (struct jme_softc*) ; 
 int RXCSR_RXQ_START ; 
 int RXCSR_RX_ENB ; 
 int TXCSR_TX_ENB ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jme_softc*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jme_init_ssb (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_init_tx_ring (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_mac_config (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_stats_clear (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_stop_rx (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_stop_tx (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_tick ; 
 int /*<<< orphan*/  jme_txeof (struct jme_softc*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_unblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
jme_link_task(void *arg, int pending)
{
	struct jme_softc *sc;
	struct mii_data *mii;
	struct ifnet *ifp;
	struct jme_txdesc *txd;
	bus_addr_t paddr;
	int i;

	sc = (struct jme_softc *)arg;

	JME_LOCK(sc);
	mii = device_get_softc(sc->jme_miibus);
	ifp = sc->jme_ifp;
	if (mii == NULL || ifp == NULL ||
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
		JME_UNLOCK(sc);
		return;
	}

	sc->jme_flags &= ~JME_FLAG_LINK;
	if ((mii->mii_media_status & IFM_AVALID) != 0) {
		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_10_T:
		case IFM_100_TX:
			sc->jme_flags |= JME_FLAG_LINK;
			break;
		case IFM_1000_T:
			if ((sc->jme_flags & JME_FLAG_FASTETH) != 0)
				break;
			sc->jme_flags |= JME_FLAG_LINK;
			break;
		default:
			break;
		}
	}

	/*
	 * Disabling Rx/Tx MACs have a side-effect of resetting
	 * JME_TXNDA/JME_RXNDA register to the first address of
	 * Tx/Rx descriptor address. So driver should reset its
	 * internal procucer/consumer pointer and reclaim any
	 * allocated resources. Note, just saving the value of
	 * JME_TXNDA and JME_RXNDA registers before stopping MAC
	 * and restoring JME_TXNDA/JME_RXNDA register is not
	 * sufficient to make sure correct MAC state because
	 * stopping MAC operation can take a while and hardware
	 * might have updated JME_TXNDA/JME_RXNDA registers
	 * during the stop operation.
	 */
	/* Block execution of task. */
	taskqueue_block(sc->jme_tq);
	/* Disable interrupts and stop driver. */
	CSR_WRITE_4(sc, JME_INTR_MASK_CLR, JME_INTRS);
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	callout_stop(&sc->jme_tick_ch);
	sc->jme_watchdog_timer = 0;

	/* Stop receiver/transmitter. */
	jme_stop_rx(sc);
	jme_stop_tx(sc);

	/* XXX Drain all queued tasks. */
	JME_UNLOCK(sc);
	taskqueue_drain(sc->jme_tq, &sc->jme_int_task);
	JME_LOCK(sc);

	if (sc->jme_cdata.jme_rxhead != NULL)
		m_freem(sc->jme_cdata.jme_rxhead);
	JME_RXCHAIN_RESET(sc);
	jme_txeof(sc);
	if (sc->jme_cdata.jme_tx_cnt != 0) {
		/* Remove queued packets for transmit. */
		for (i = 0; i < JME_TX_RING_CNT; i++) {
			txd = &sc->jme_cdata.jme_txdesc[i];
			if (txd->tx_m != NULL) {
				bus_dmamap_sync(
				    sc->jme_cdata.jme_tx_tag,
				    txd->tx_dmamap,
				    BUS_DMASYNC_POSTWRITE);
				bus_dmamap_unload(
				    sc->jme_cdata.jme_tx_tag,
				    txd->tx_dmamap);
				m_freem(txd->tx_m);
				txd->tx_m = NULL;
				txd->tx_ndesc = 0;
				if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
			}
		}
	}

	/*
	 * Reuse configured Rx descriptors and reset
	 * producer/consumer index.
	 */
	sc->jme_cdata.jme_rx_cons = 0;
	sc->jme_morework = 0;
	jme_init_tx_ring(sc);
	/* Initialize shadow status block. */
	jme_init_ssb(sc);

	/* Program MAC with resolved speed/duplex/flow-control. */
	if ((sc->jme_flags & JME_FLAG_LINK) != 0) {
		jme_mac_config(sc);
		jme_stats_clear(sc);

		CSR_WRITE_4(sc, JME_RXCSR, sc->jme_rxcsr);
		CSR_WRITE_4(sc, JME_TXCSR, sc->jme_txcsr);

		/* Set Tx ring address to the hardware. */
		paddr = JME_TX_RING_ADDR(sc, 0);
		CSR_WRITE_4(sc, JME_TXDBA_HI, JME_ADDR_HI(paddr));
		CSR_WRITE_4(sc, JME_TXDBA_LO, JME_ADDR_LO(paddr));

		/* Set Rx ring address to the hardware. */
		paddr = JME_RX_RING_ADDR(sc, 0);
		CSR_WRITE_4(sc, JME_RXDBA_HI, JME_ADDR_HI(paddr));
		CSR_WRITE_4(sc, JME_RXDBA_LO, JME_ADDR_LO(paddr));

		/* Restart receiver/transmitter. */
		CSR_WRITE_4(sc, JME_RXCSR, sc->jme_rxcsr | RXCSR_RX_ENB |
		    RXCSR_RXQ_START);
		CSR_WRITE_4(sc, JME_TXCSR, sc->jme_txcsr | TXCSR_TX_ENB);
		/* Lastly enable TX/RX clock. */
		if ((sc->jme_flags & JME_FLAG_TXCLK) != 0)
			CSR_WRITE_4(sc, JME_GHC,
			    CSR_READ_4(sc, JME_GHC) & ~GHC_TX_MAC_CLK_DIS);
		if ((sc->jme_flags & JME_FLAG_RXCLK) != 0)
			CSR_WRITE_4(sc, JME_GPREG1,
			    CSR_READ_4(sc, JME_GPREG1) & ~GPREG1_RX_MAC_CLK_DIS);
	}

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
	callout_reset(&sc->jme_tick_ch, hz, jme_tick, sc);
	/* Unblock execution of task. */
	taskqueue_unblock(sc->jme_tq);
	/* Reenable interrupts. */
	CSR_WRITE_4(sc, JME_INTR_MASK_SET, JME_INTRS);

	JME_UNLOCK(sc);
}