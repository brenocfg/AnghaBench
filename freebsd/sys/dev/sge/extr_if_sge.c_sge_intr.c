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
typedef  int uint32_t ;
struct sge_softc {struct ifnet* sge_ifp; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int CSR_READ_4 (struct sge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sge_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int INTR_RX_DONE ; 
 int INTR_RX_IDLE ; 
 int INTR_TX_DONE ; 
 int INTR_TX_IDLE ; 
 int /*<<< orphan*/  IntrMask ; 
 int /*<<< orphan*/  IntrStatus ; 
 int /*<<< orphan*/  RX_CTL ; 
 int RX_CTL_ENB ; 
 int RX_CTL_POLL ; 
 int SGE_INTRS ; 
 int /*<<< orphan*/  SGE_LOCK (struct sge_softc*) ; 
 int /*<<< orphan*/  SGE_UNLOCK (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_rxeof (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  sge_txeof (struct sge_softc*) ; 

__attribute__((used)) static void
sge_intr(void *arg)
{
	struct sge_softc *sc;
	struct ifnet *ifp;
	uint32_t status;

	sc = arg;
	SGE_LOCK(sc);
	ifp = sc->sge_ifp;

	status = CSR_READ_4(sc, IntrStatus);
	if (status == 0xFFFFFFFF || (status & SGE_INTRS) == 0) {
		/* Not ours. */
		SGE_UNLOCK(sc);
		return;
	}
	/* Acknowledge interrupts. */
	CSR_WRITE_4(sc, IntrStatus, status);
	/* Disable further interrupts. */
	CSR_WRITE_4(sc, IntrMask, 0);
	/*
	 * It seems the controller supports some kind of interrupt
	 * moderation mechanism but we still don't know how to
	 * enable that.  To reduce number of generated interrupts
	 * under load we check pending interrupts in a loop.  This
	 * will increase number of register access and is not correct
	 * way to handle interrupt moderation but there seems to be
	 * no other way at this time.
	 */
	for (;;) {
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
			break;
		if ((status & (INTR_RX_DONE | INTR_RX_IDLE)) != 0) {
			sge_rxeof(sc);
			/* Wakeup Rx MAC. */
			if ((status & INTR_RX_IDLE) != 0)
				CSR_WRITE_4(sc, RX_CTL,
				    0x1a00 | 0x000c | RX_CTL_POLL | RX_CTL_ENB);
		}
		if ((status & (INTR_TX_DONE | INTR_TX_IDLE)) != 0)
			sge_txeof(sc);
		status = CSR_READ_4(sc, IntrStatus);
		if ((status & SGE_INTRS) == 0)
			break;
		/* Acknowledge interrupts. */
		CSR_WRITE_4(sc, IntrStatus, status);
	}
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
		/* Re-enable interrupts */
		CSR_WRITE_4(sc, IntrMask, SGE_INTRS);
		if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			sge_start_locked(ifp);
	}
	SGE_UNLOCK(sc);
}