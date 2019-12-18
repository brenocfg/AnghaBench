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
struct rsu_softc {int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  keys_bmap; int /*<<< orphan*/  free_keys_bmap; int /*<<< orphan*/  tx_task; int /*<<< orphan*/  calib_task; scalar_t__ sc_calibrating; scalar_t__ sc_vap_is_running; scalar_t__ sc_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSU_LOCK (struct rsu_softc*) ; 
 int RSU_N_TRANSFER ; 
 int /*<<< orphan*/  RSU_UNLOCK (struct rsu_softc*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rsu_drain_mbufq (struct rsu_softc*) ; 
 int /*<<< orphan*/  rsu_power_off (struct rsu_softc*) ; 
 int /*<<< orphan*/  taskqueue_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rsu_stop(struct rsu_softc *sc)
{
	int i;

	RSU_LOCK(sc);
	if (!sc->sc_running) {
		RSU_UNLOCK(sc);
		return;
	}

	sc->sc_running = 0;
	sc->sc_vap_is_running = 0;
	sc->sc_calibrating = 0;
	taskqueue_cancel_timeout(taskqueue_thread, &sc->calib_task, NULL);
	taskqueue_cancel(taskqueue_thread, &sc->tx_task, NULL);

	/* Power off adapter. */
	rsu_power_off(sc);

	/*
	 * CAM is not accessible after shutdown;
	 * all entries are marked (by firmware?) as invalid.
	 */
	memset(sc->free_keys_bmap, 0, sizeof(sc->free_keys_bmap));
	memset(sc->keys_bmap, 0, sizeof(sc->keys_bmap));

	for (i = 0; i < RSU_N_TRANSFER; i++)
		usbd_transfer_stop(sc->sc_xfer[i]);

	/* Ensure the mbuf queue is drained */
	rsu_drain_mbufq(sc);
	RSU_UNLOCK(sc);
}