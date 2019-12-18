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
typedef  int uint16_t ;
struct ste_softc {int ste_int_rx_act; scalar_t__ ste_int_rx_mod; struct ifnet* ste_ifp; } ;
struct ifnet {int if_capenable; int if_drv_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int CSR_READ_2 (struct ste_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct ste_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STE_COUNTDOWN ; 
 int /*<<< orphan*/  STE_IMR ; 
 int STE_IMR_RX_DMADONE ; 
 int STE_INTRS ; 
 int /*<<< orphan*/  STE_ISR_ACK ; 
 int STE_ISR_HOSTERR ; 
 int STE_ISR_RX_DMADONE ; 
 int STE_ISR_SOFTINTR ; 
 int STE_ISR_STATS_OFLOW ; 
 int STE_ISR_TX_DMADONE ; 
 int STE_ISR_TX_DONE ; 
 int /*<<< orphan*/  STE_LOCK (struct ste_softc*) ; 
 int STE_TIMER_USECS (scalar_t__) ; 
 int /*<<< orphan*/  STE_UNLOCK (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_init_locked (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_rxeof (struct ste_softc*,int) ; 
 int /*<<< orphan*/  ste_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  ste_stats_update (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_txeoc (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_txeof (struct ste_softc*) ; 

__attribute__((used)) static void
ste_intr(void *xsc)
{
	struct ste_softc *sc;
	struct ifnet *ifp;
	uint16_t intrs, status;

	sc = xsc;
	STE_LOCK(sc);
	ifp = sc->ste_ifp;

#ifdef DEVICE_POLLING
	if (ifp->if_capenable & IFCAP_POLLING) {
		STE_UNLOCK(sc);
		return;
	}
#endif
	/* Reading STE_ISR_ACK clears STE_IMR register. */
	status = CSR_READ_2(sc, STE_ISR_ACK);
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
		STE_UNLOCK(sc);
		return;
	}

	intrs = STE_INTRS;
	if (status == 0xFFFF || (status & intrs) == 0)
		goto done;

	if (sc->ste_int_rx_act > 0) {
		status &= ~STE_ISR_RX_DMADONE;
		intrs &= ~STE_IMR_RX_DMADONE;
	}

	if ((status & (STE_ISR_SOFTINTR | STE_ISR_RX_DMADONE)) != 0) {
		ste_rxeof(sc, -1);
		/*
		 * The controller has no ability to Rx interrupt
		 * moderation feature. Receiving 64 bytes frames
		 * from wire generates too many interrupts which in
		 * turn make system useless to process other useful
		 * things. Fortunately ST201 supports single shot
		 * timer so use the timer to implement Rx interrupt
		 * moderation in driver. This adds more register
		 * access but it greatly reduces number of Rx
		 * interrupts under high network load.
		 */
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0 &&
		    (sc->ste_int_rx_mod != 0)) {
			if ((status & STE_ISR_RX_DMADONE) != 0) {
				CSR_WRITE_2(sc, STE_COUNTDOWN,
				    STE_TIMER_USECS(sc->ste_int_rx_mod));
				intrs &= ~STE_IMR_RX_DMADONE;
				sc->ste_int_rx_act = 1;
			} else {
				intrs |= STE_IMR_RX_DMADONE;
				sc->ste_int_rx_act = 0;
			}
		}
	}
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
		if ((status & STE_ISR_TX_DMADONE) != 0)
			ste_txeof(sc);
		if ((status & STE_ISR_TX_DONE) != 0)
			ste_txeoc(sc);
		if ((status & STE_ISR_STATS_OFLOW) != 0)
			ste_stats_update(sc);
		if ((status & STE_ISR_HOSTERR) != 0) {
			ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			ste_init_locked(sc);
			STE_UNLOCK(sc);
			return;
		}
		if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			ste_start_locked(ifp);
done:
		/* Re-enable interrupts */
		CSR_WRITE_2(sc, STE_IMR, intrs);
	}
	STE_UNLOCK(sc);
}