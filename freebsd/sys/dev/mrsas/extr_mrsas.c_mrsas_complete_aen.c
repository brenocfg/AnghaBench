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
struct mrsas_softc {scalar_t__ remove_in_progress; int mrsas_aen_triggered; int /*<<< orphan*/  ev_task; int /*<<< orphan*/  ev_tq; int /*<<< orphan*/ * aen_cmd; int /*<<< orphan*/  aen_lock; int /*<<< orphan*/  mrsas_select; scalar_t__ mrsas_poll_waiting; } ;
struct mrsas_mfi_cmd {scalar_t__ abort_aen; } ;

/* Variables and functions */
 int /*<<< orphan*/  mrsas_release_mfi_cmd (struct mrsas_mfi_cmd*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selwakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
mrsas_complete_aen(struct mrsas_softc *sc, struct mrsas_mfi_cmd *cmd)
{
	/*
	 * Don't signal app if it is just an aborted previously registered
	 * aen
	 */
	if ((!cmd->abort_aen) && (sc->remove_in_progress == 0)) {
		sc->mrsas_aen_triggered = 1;
		mtx_lock(&sc->aen_lock);
		if (sc->mrsas_poll_waiting) {
			sc->mrsas_poll_waiting = 0;
			selwakeup(&sc->mrsas_select);
		}
		mtx_unlock(&sc->aen_lock);
	} else
		cmd->abort_aen = 0;

	sc->aen_cmd = NULL;
	mrsas_release_mfi_cmd(cmd);

	taskqueue_enqueue(sc->ev_tq, &sc->ev_task);

	return;
}