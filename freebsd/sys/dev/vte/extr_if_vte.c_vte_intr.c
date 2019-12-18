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
struct vte_softc {struct ifnet* vte_ifp; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int CSR_READ_2 (struct vte_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct vte_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int MISR_EVENT_CNT_OFLOW ; 
 int MISR_RX_DESC_UNAVAIL ; 
 int MISR_RX_DONE ; 
 int MISR_RX_FIFO_FULL ; 
 int MISR_TX_DONE ; 
 int VTE_INTRS ; 
 int /*<<< orphan*/  VTE_LOCK (struct vte_softc*) ; 
 int /*<<< orphan*/  VTE_MIER ; 
 int /*<<< orphan*/  VTE_MISR ; 
 int /*<<< orphan*/  VTE_UNLOCK (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_rxeof (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_start_locked (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_stats_update (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_txeof (struct vte_softc*) ; 

__attribute__((used)) static void
vte_intr(void *arg)
{
	struct vte_softc *sc;
	struct ifnet *ifp;
	uint16_t status;
	int n;

	sc = (struct vte_softc *)arg;
	VTE_LOCK(sc);

	ifp = sc->vte_ifp;
	/* Reading VTE_MISR acknowledges interrupts. */
	status = CSR_READ_2(sc, VTE_MISR);
	if ((status & VTE_INTRS) == 0) {
		/* Not ours. */
		VTE_UNLOCK(sc);
		return;
	}

	/* Disable interrupts. */
	CSR_WRITE_2(sc, VTE_MIER, 0);
	for (n = 8; (status & VTE_INTRS) != 0;) {
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
			break;
		if ((status & (MISR_RX_DONE | MISR_RX_DESC_UNAVAIL |
		    MISR_RX_FIFO_FULL)) != 0)
			vte_rxeof(sc);
		if ((status & MISR_TX_DONE) != 0)
			vte_txeof(sc);
		if ((status & MISR_EVENT_CNT_OFLOW) != 0)
			vte_stats_update(sc);
		if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			vte_start_locked(sc);
		if (--n > 0)
			status = CSR_READ_2(sc, VTE_MISR);
		else
			break;
	}

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
		/* Re-enable interrupts. */
		CSR_WRITE_2(sc, VTE_MIER, VTE_INTRS);
	}
	VTE_UNLOCK(sc);
}