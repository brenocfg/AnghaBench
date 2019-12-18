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
typedef  int u_int16_t ;
struct rl_softc {int rl_flags; int /*<<< orphan*/  rl_inttask; int /*<<< orphan*/  rl_txstart; scalar_t__ suspended; struct ifnet* rl_ifp; } ;
struct ifnet {int if_drv_flags; int if_capenable; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int CSR_READ_2 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct rl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int RL_FLAG_PCIE ; 
 int /*<<< orphan*/  RL_IMR ; 
 int RL_INTRS_CPLUS ; 
 int /*<<< orphan*/  RL_ISR ; 
 int RL_ISR_FIFO_OFLOW ; 
 int RL_ISR_RX_ERR ; 
 int RL_ISR_RX_OK ; 
 int RL_ISR_SYSTEM_ERR ; 
 int RL_ISR_TIMEOUT_EXPIRED ; 
 int RL_ISR_TX_DESC_UNAVAIL ; 
 int RL_ISR_TX_ERR ; 
 int RL_ISR_TX_OK ; 
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_TXSTART_START ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  re_init_locked (struct rl_softc*) ; 
 int re_rxeof (struct rl_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  re_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  re_txeof (struct rl_softc*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_fast ; 

__attribute__((used)) static void
re_int_task(void *arg, int npending)
{
	struct rl_softc		*sc;
	struct ifnet		*ifp;
	u_int16_t		status;
	int			rval = 0;

	sc = arg;
	ifp = sc->rl_ifp;

	RL_LOCK(sc);

	status = CSR_READ_2(sc, RL_ISR);
        CSR_WRITE_2(sc, RL_ISR, status);

	if (sc->suspended ||
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
		RL_UNLOCK(sc);
		return;
	}

#ifdef DEVICE_POLLING
	if  (ifp->if_capenable & IFCAP_POLLING) {
		RL_UNLOCK(sc);
		return;
	}
#endif

	if (status & (RL_ISR_RX_OK|RL_ISR_RX_ERR|RL_ISR_FIFO_OFLOW))
		rval = re_rxeof(sc, NULL);

	/*
	 * Some chips will ignore a second TX request issued
	 * while an existing transmission is in progress. If
	 * the transmitter goes idle but there are still
	 * packets waiting to be sent, we need to restart the
	 * channel here to flush them out. This only seems to
	 * be required with the PCIe devices.
	 */
	if ((status & (RL_ISR_TX_OK | RL_ISR_TX_DESC_UNAVAIL)) &&
	    (sc->rl_flags & RL_FLAG_PCIE))
		CSR_WRITE_1(sc, sc->rl_txstart, RL_TXSTART_START);
	if (status & (
#ifdef RE_TX_MODERATION
	    RL_ISR_TIMEOUT_EXPIRED|
#else
	    RL_ISR_TX_OK|
#endif
	    RL_ISR_TX_ERR|RL_ISR_TX_DESC_UNAVAIL))
		re_txeof(sc);

	if (status & RL_ISR_SYSTEM_ERR) {
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		re_init_locked(sc);
	}

	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		re_start_locked(ifp);

	RL_UNLOCK(sc);

        if ((CSR_READ_2(sc, RL_ISR) & RL_INTRS_CPLUS) || rval) {
		taskqueue_enqueue(taskqueue_fast, &sc->rl_inttask);
		return;
	}

	CSR_WRITE_2(sc, RL_IMR, RL_INTRS_CPLUS);
}