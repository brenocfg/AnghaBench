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
struct ieee80211com {int dummy; } ;
struct rsu_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  tx_task; int /*<<< orphan*/  del_key_task; int /*<<< orphan*/  calib_task; int /*<<< orphan*/  sc_xfer; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RSU_DELKEY_BMAP_LOCK_DESTROY (struct rsu_softc*) ; 
 int /*<<< orphan*/  RSU_LOCK (struct rsu_softc*) ; 
 int /*<<< orphan*/  RSU_N_TRANSFER ; 
 int /*<<< orphan*/  RSU_UNLOCK (struct rsu_softc*) ; 
 struct rsu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsu_free_rx_list (struct rsu_softc*) ; 
 int /*<<< orphan*/  rsu_free_tx_list (struct rsu_softc*) ; 
 int /*<<< orphan*/  rsu_stop (struct rsu_softc*) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rsu_detach(device_t self)
{
	struct rsu_softc *sc = device_get_softc(self);
	struct ieee80211com *ic = &sc->sc_ic;

	rsu_stop(sc);

	usbd_transfer_unsetup(sc->sc_xfer, RSU_N_TRANSFER);

	/*
	 * Free buffers /before/ we detach from net80211, else node
	 * references to destroyed vaps will lead to a panic.
	 */
	/* Free Tx/Rx buffers. */
	RSU_LOCK(sc);
	rsu_free_tx_list(sc);
	rsu_free_rx_list(sc);
	RSU_UNLOCK(sc);

	/* Frames are freed; detach from net80211 */
	ieee80211_ifdetach(ic);

	taskqueue_drain_timeout(taskqueue_thread, &sc->calib_task);
	taskqueue_drain(taskqueue_thread, &sc->del_key_task);
	taskqueue_drain(taskqueue_thread, &sc->tx_task);

	RSU_DELKEY_BMAP_LOCK_DESTROY(sc);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}