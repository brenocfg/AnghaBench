#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ubt_softc_p ;
struct TYPE_5__ {int sc_task_flags; int /*<<< orphan*/  sc_if_mtx; int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int UBT_FLAG_T_START_ALL ; 
 int UBT_FLAG_T_START_BULK ; 
 int UBT_FLAG_T_START_CTRL ; 
 int UBT_FLAG_T_STOP_ALL ; 
 int /*<<< orphan*/  UBT_IF_0_BULK_DT_RD ; 
 int /*<<< orphan*/  UBT_IF_0_BULK_DT_WR ; 
 int /*<<< orphan*/  UBT_IF_0_CTRL_DT_WR ; 
 int /*<<< orphan*/  UBT_IF_0_INTR_DT_RD ; 
 int /*<<< orphan*/  UBT_IF_1_ISOC_DT_RD1 ; 
 int /*<<< orphan*/  UBT_IF_1_ISOC_DT_RD2 ; 
 int /*<<< orphan*/  UBT_IF_1_ISOC_DT_WR1 ; 
 int /*<<< orphan*/  UBT_IF_1_ISOC_DT_WR2 ; 
 int /*<<< orphan*/  UBT_NG_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  UBT_NG_UNLOCK (TYPE_1__*) ; 
 int UBT_N_TRANSFER ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubt_xfer_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_drain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ubt_task(void *context, int pending)
{
	ubt_softc_p	sc = context;
	int		task_flags, i;

	UBT_NG_LOCK(sc);
	task_flags = sc->sc_task_flags;
	sc->sc_task_flags = 0;
	UBT_NG_UNLOCK(sc);

	/*
	 * Stop all USB transfers synchronously.
	 * Stop interface #0 and #1 transfers at the same time and in the
	 * same loop. usbd_transfer_drain() will do appropriate locking.
	 */

	if (task_flags & UBT_FLAG_T_STOP_ALL)
		for (i = 0; i < UBT_N_TRANSFER; i ++)
			usbd_transfer_drain(sc->sc_xfer[i]);

	/* Start incoming interrupt and bulk, and all isoc. USB transfers */
	if (task_flags & UBT_FLAG_T_START_ALL) {
		/*
		 * Interface #0
		 */

		mtx_lock(&sc->sc_if_mtx);

		ubt_xfer_start(sc, UBT_IF_0_INTR_DT_RD);
		ubt_xfer_start(sc, UBT_IF_0_BULK_DT_RD);

		/*
		 * Interface #1
		 * Start both read and write isoc. transfers by default.
		 * Get them going all the time even if we have nothing
		 * to send to avoid any delays.
		 */

		ubt_xfer_start(sc, UBT_IF_1_ISOC_DT_RD1);
		ubt_xfer_start(sc, UBT_IF_1_ISOC_DT_RD2);
		ubt_xfer_start(sc, UBT_IF_1_ISOC_DT_WR1);
		ubt_xfer_start(sc, UBT_IF_1_ISOC_DT_WR2);

		mtx_unlock(&sc->sc_if_mtx);
	}

 	/* Start outgoing control transfer */
	if (task_flags & UBT_FLAG_T_START_CTRL) {
		mtx_lock(&sc->sc_if_mtx);
		ubt_xfer_start(sc, UBT_IF_0_CTRL_DT_WR);
		mtx_unlock(&sc->sc_if_mtx);
	}

	/* Start outgoing bulk transfer */
	if (task_flags & UBT_FLAG_T_START_BULK) {
		mtx_lock(&sc->sc_if_mtx);
		ubt_xfer_start(sc, UBT_IF_0_BULK_DT_WR);
		mtx_unlock(&sc->sc_if_mtx);
	}
}