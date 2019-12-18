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
struct TYPE_2__ {int /*<<< orphan*/  ste_rx_list_paddr; } ;
struct ste_softc {int ste_tx_thresh; int /*<<< orphan*/  ste_callout; int /*<<< orphan*/  ste_flags; TYPE_1__ ste_ldata; int /*<<< orphan*/  ste_dev; struct ifnet* ste_ifp; int /*<<< orphan*/  ste_miibus; } ;
struct mii_data {int dummy; } ;
struct ifnet {int if_drv_flags; int if_capenable; } ;

/* Variables and functions */
 int CSR_READ_1 (struct ste_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct ste_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct ste_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ste_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ETHER_ADDR_LEN ; 
 int ETHER_MAX_LEN ; 
 int ETHER_VLAN_ENCAP_LEN ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int* IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  STE_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STE_CLRBIT4 (struct ste_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ STE_COUNTDOWN ; 
 int /*<<< orphan*/  STE_DMACTL ; 
 int STE_DMACTL_COUNTDOWN_MODE ; 
 int STE_DMACTL_COUNTDOWN_SPEED ; 
 int /*<<< orphan*/  STE_DMACTL_RXDMA_STALL ; 
 int /*<<< orphan*/  STE_DMACTL_RXDMA_UNSTALL ; 
 int /*<<< orphan*/  STE_DMACTL_TXDMA_STALL ; 
 int /*<<< orphan*/  STE_DMACTL_TXDMA_UNSTALL ; 
 int /*<<< orphan*/  STE_FLAG_LINK ; 
 scalar_t__ STE_IMR ; 
 int STE_INTRS ; 
 scalar_t__ STE_ISR ; 
 int /*<<< orphan*/  STE_LOCK_ASSERT (struct ste_softc*) ; 
 scalar_t__ STE_MACCTL0 ; 
 scalar_t__ STE_MACCTL1 ; 
 int /*<<< orphan*/  STE_MACCTL1_RX_ENABLE ; 
 int /*<<< orphan*/  STE_MACCTL1_STATS_ENABLE ; 
 int /*<<< orphan*/  STE_MACCTL1_TX_ENABLE ; 
 scalar_t__ STE_MAX_FRAMELEN ; 
 int STE_PACKET_SIZE ; 
 scalar_t__ STE_PAR0 ; 
 int /*<<< orphan*/  STE_RX_DMALIST_PTR ; 
 int /*<<< orphan*/  STE_RX_DMAPOLL_PERIOD ; 
 int /*<<< orphan*/  STE_SETBIT2 (struct ste_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STE_SETBIT4 (struct ste_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STE_TX_DMABURST_THRESH ; 
 int /*<<< orphan*/  STE_TX_DMALIST_PTR ; 
 int /*<<< orphan*/  STE_TX_DMAPOLL_PERIOD ; 
 int /*<<< orphan*/  STE_TX_RECLAIM_THRESH ; 
 scalar_t__ STE_TX_STARTTHRESH ; 
 int STE_WAKEEVENT_LINKEVT_ENB ; 
 int STE_WAKEEVENT_MAGICPKT_ENB ; 
 int STE_WAKEEVENT_WAKEONLAN_ENB ; 
 int STE_WAKEEVENT_WAKEPKT_ENB ; 
 int /*<<< orphan*/  STE_WAKE_EVENT ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ste_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 
 scalar_t__ ste_init_rx_list (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_init_tx_list (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_reset (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_rxfilter (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_stats_clear (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_stop (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_tick ; 
 int /*<<< orphan*/  ste_wait (struct ste_softc*) ; 

__attribute__((used)) static void
ste_init_locked(struct ste_softc *sc)
{
	struct ifnet *ifp;
	struct mii_data *mii;
	uint8_t val;
	int i;

	STE_LOCK_ASSERT(sc);
	ifp = sc->ste_ifp;
	mii = device_get_softc(sc->ste_miibus);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	ste_stop(sc);
	/* Reset the chip to a known state. */
	ste_reset(sc);

	/* Init our MAC address */
	for (i = 0; i < ETHER_ADDR_LEN; i += 2) {
		CSR_WRITE_2(sc, STE_PAR0 + i,
		    ((IF_LLADDR(sc->ste_ifp)[i] & 0xff) |
		     IF_LLADDR(sc->ste_ifp)[i + 1] << 8));
	}

	/* Init RX list */
	if (ste_init_rx_list(sc) != 0) {
		device_printf(sc->ste_dev,
		    "initialization failed: no memory for RX buffers\n");
		ste_stop(sc);
		return;
	}

	/* Set RX polling interval */
	CSR_WRITE_1(sc, STE_RX_DMAPOLL_PERIOD, 64);

	/* Init TX descriptors */
	ste_init_tx_list(sc);

	/* Clear and disable WOL. */
	val = CSR_READ_1(sc, STE_WAKE_EVENT);
	val &= ~(STE_WAKEEVENT_WAKEPKT_ENB | STE_WAKEEVENT_MAGICPKT_ENB |
	    STE_WAKEEVENT_LINKEVT_ENB | STE_WAKEEVENT_WAKEONLAN_ENB);
	CSR_WRITE_1(sc, STE_WAKE_EVENT, val);

	/* Set the TX freethresh value */
	CSR_WRITE_1(sc, STE_TX_DMABURST_THRESH, STE_PACKET_SIZE >> 8);

	/* Set the TX start threshold for best performance. */
	CSR_WRITE_2(sc, STE_TX_STARTTHRESH, sc->ste_tx_thresh);

	/* Set the TX reclaim threshold. */
	CSR_WRITE_1(sc, STE_TX_RECLAIM_THRESH, (STE_PACKET_SIZE >> 4));

	/* Accept VLAN length packets */
	CSR_WRITE_2(sc, STE_MAX_FRAMELEN, ETHER_MAX_LEN + ETHER_VLAN_ENCAP_LEN);

	/* Set up the RX filter. */
	ste_rxfilter(sc);

	/* Load the address of the RX list. */
	STE_SETBIT4(sc, STE_DMACTL, STE_DMACTL_RXDMA_STALL);
	ste_wait(sc);
	CSR_WRITE_4(sc, STE_RX_DMALIST_PTR,
	    STE_ADDR_LO(sc->ste_ldata.ste_rx_list_paddr));
	STE_SETBIT4(sc, STE_DMACTL, STE_DMACTL_RXDMA_UNSTALL);
	STE_SETBIT4(sc, STE_DMACTL, STE_DMACTL_RXDMA_UNSTALL);

	/* Set TX polling interval(defer until we TX first packet). */
	CSR_WRITE_1(sc, STE_TX_DMAPOLL_PERIOD, 0);

	/* Load address of the TX list */
	STE_SETBIT4(sc, STE_DMACTL, STE_DMACTL_TXDMA_STALL);
	ste_wait(sc);
	CSR_WRITE_4(sc, STE_TX_DMALIST_PTR, 0);
	STE_SETBIT4(sc, STE_DMACTL, STE_DMACTL_TXDMA_UNSTALL);
	STE_SETBIT4(sc, STE_DMACTL, STE_DMACTL_TXDMA_UNSTALL);
	ste_wait(sc);
	/* Select 3.2us timer. */
	STE_CLRBIT4(sc, STE_DMACTL, STE_DMACTL_COUNTDOWN_SPEED |
	    STE_DMACTL_COUNTDOWN_MODE);

	/* Enable receiver and transmitter */
	CSR_WRITE_2(sc, STE_MACCTL0, 0);
	CSR_WRITE_2(sc, STE_MACCTL1, 0);
	STE_SETBIT2(sc, STE_MACCTL1, STE_MACCTL1_TX_ENABLE);
	STE_SETBIT2(sc, STE_MACCTL1, STE_MACCTL1_RX_ENABLE);

	/* Enable stats counters. */
	STE_SETBIT2(sc, STE_MACCTL1, STE_MACCTL1_STATS_ENABLE);
	/* Clear stats counters. */
	ste_stats_clear(sc);

	CSR_WRITE_2(sc, STE_COUNTDOWN, 0);
	CSR_WRITE_2(sc, STE_ISR, 0xFFFF);
#ifdef DEVICE_POLLING
	/* Disable interrupts if we are polling. */
	if (ifp->if_capenable & IFCAP_POLLING)
		CSR_WRITE_2(sc, STE_IMR, 0);
	else
#endif
	/* Enable interrupts. */
	CSR_WRITE_2(sc, STE_IMR, STE_INTRS);

	sc->ste_flags &= ~STE_FLAG_LINK;
	/* Switch to the current media. */
	mii_mediachg(mii);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	callout_reset(&sc->ste_callout, hz, ste_tick, sc);
}