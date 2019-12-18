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
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;
struct TYPE_2__ {int /*<<< orphan*/  reset_brk_seq; } ;
struct ale_softc {int ale_morework; int /*<<< orphan*/  ale_int_task; int /*<<< orphan*/  ale_tq; int /*<<< orphan*/  ale_dev; TYPE_1__ ale_stats; int /*<<< orphan*/  ale_process_limit; struct ifnet* ale_ifp; } ;

/* Variables and functions */
 int ALE_INTRS ; 
 int /*<<< orphan*/  ALE_INTR_STATUS ; 
 int /*<<< orphan*/  ALE_LOCK (struct ale_softc*) ; 
 int /*<<< orphan*/  ALE_UNLOCK (struct ale_softc*) ; 
 int CSR_READ_4 (struct ale_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ale_softc*,int /*<<< orphan*/ ,int) ; 
 int EAGAIN ; 
 int EIO ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int INTR_DIS_INT ; 
 int INTR_DMA_RD_TO_RST ; 
 int INTR_DMA_WR_TO_RST ; 
 int INTR_RX_PKT ; 
 int /*<<< orphan*/  ale_init_locked (struct ale_softc*) ; 
 int ale_rxeof (struct ale_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ale_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ale_int_task(void *arg, int pending)
{
	struct ale_softc *sc;
	struct ifnet *ifp;
	uint32_t status;
	int more;

	sc = (struct ale_softc *)arg;

	status = CSR_READ_4(sc, ALE_INTR_STATUS);
	ALE_LOCK(sc);
	if (sc->ale_morework != 0)
		status |= INTR_RX_PKT;
	if ((status & ALE_INTRS) == 0)
		goto done;

	/* Acknowledge interrupts but still disable interrupts. */
	CSR_WRITE_4(sc, ALE_INTR_STATUS, status | INTR_DIS_INT);

	ifp = sc->ale_ifp;
	more = 0;
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
		more = ale_rxeof(sc, sc->ale_process_limit);
		if (more == EAGAIN)
			sc->ale_morework = 1;
		else if (more == EIO) {
			sc->ale_stats.reset_brk_seq++;
			ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			ale_init_locked(sc);
			ALE_UNLOCK(sc);
			return;
		}

		if ((status & (INTR_DMA_RD_TO_RST | INTR_DMA_WR_TO_RST)) != 0) {
			if ((status & INTR_DMA_RD_TO_RST) != 0)
				device_printf(sc->ale_dev,
				    "DMA read error! -- resetting\n");
			if ((status & INTR_DMA_WR_TO_RST) != 0)
				device_printf(sc->ale_dev,
				    "DMA write error! -- resetting\n");
			ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			ale_init_locked(sc);
			ALE_UNLOCK(sc);
			return;
		}
		if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			ale_start_locked(ifp);
	}

	if (more == EAGAIN ||
	    (CSR_READ_4(sc, ALE_INTR_STATUS) & ALE_INTRS) != 0) {
		ALE_UNLOCK(sc);
		taskqueue_enqueue(sc->ale_tq, &sc->ale_int_task);
		return;
	}

done:
	ALE_UNLOCK(sc);

	/* Re-enable interrupts. */
	CSR_WRITE_4(sc, ALE_INTR_STATUS, 0x7FFFFFFF);
}