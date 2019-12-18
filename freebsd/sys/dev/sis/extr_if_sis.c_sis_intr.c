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
struct sis_softc {struct ifnet* sis_ifp; } ;
struct ifnet {int if_capenable; int if_drv_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int CSR_READ_4 (struct sis_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sis_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIS_CSR ; 
 int /*<<< orphan*/  SIS_CSR_RX_ENABLE ; 
 int /*<<< orphan*/  SIS_IER ; 
 int SIS_INTRS ; 
 int /*<<< orphan*/  SIS_ISR ; 
 int SIS_ISR_RX_DESC_OK ; 
 int SIS_ISR_RX_ERR ; 
 int SIS_ISR_RX_IDLE ; 
 int SIS_ISR_RX_OFLOW ; 
 int SIS_ISR_RX_OK ; 
 int SIS_ISR_SYSERR ; 
 int SIS_ISR_TX_DESC_OK ; 
 int SIS_ISR_TX_ERR ; 
 int SIS_ISR_TX_IDLE ; 
 int SIS_ISR_TX_OK ; 
 int /*<<< orphan*/  SIS_LOCK (struct sis_softc*) ; 
 int /*<<< orphan*/  SIS_SETBIT (struct sis_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIS_UNLOCK (struct sis_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sis_initl (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_rxeof (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_startl (struct ifnet*) ; 
 int /*<<< orphan*/  sis_txeof (struct sis_softc*) ; 

__attribute__((used)) static void
sis_intr(void *arg)
{
	struct sis_softc	*sc;
	struct ifnet		*ifp;
	uint32_t		status;

	sc = arg;
	ifp = sc->sis_ifp;

	SIS_LOCK(sc);
#ifdef DEVICE_POLLING
	if (ifp->if_capenable & IFCAP_POLLING) {
		SIS_UNLOCK(sc);
		return;
	}
#endif

	/* Reading the ISR register clears all interrupts. */
	status = CSR_READ_4(sc, SIS_ISR);
	if ((status & SIS_INTRS) == 0) {
		/* Not ours. */
		SIS_UNLOCK(sc);
		return;
	}

	/* Disable interrupts. */
	CSR_WRITE_4(sc, SIS_IER, 0);

	for (;(status & SIS_INTRS) != 0;) {
		if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
			break;
		if (status &
		    (SIS_ISR_TX_DESC_OK | SIS_ISR_TX_ERR |
		    SIS_ISR_TX_OK | SIS_ISR_TX_IDLE) )
			sis_txeof(sc);

		if (status & (SIS_ISR_RX_DESC_OK | SIS_ISR_RX_OK |
		    SIS_ISR_RX_ERR | SIS_ISR_RX_IDLE))
			sis_rxeof(sc);

		if (status & SIS_ISR_RX_OFLOW)
			if_inc_counter(ifp, IFCOUNTER_IERRORS, 1);

		if (status & (SIS_ISR_RX_IDLE))
			SIS_SETBIT(sc, SIS_CSR, SIS_CSR_RX_ENABLE);

		if (status & SIS_ISR_SYSERR) {
			ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			sis_initl(sc);
			SIS_UNLOCK(sc);
			return;
		}
		status = CSR_READ_4(sc, SIS_ISR);
	}

	if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
		/* Re-enable interrupts. */
		CSR_WRITE_4(sc, SIS_IER, 1);

		if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			sis_startl(ifp);
	}

	SIS_UNLOCK(sc);
}