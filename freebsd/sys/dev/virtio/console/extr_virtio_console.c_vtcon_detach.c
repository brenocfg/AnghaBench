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
struct vtcon_softc {int vtcon_flags; int /*<<< orphan*/  vtcon_ctrl_tx_mtx; int /*<<< orphan*/  vtcon_mtx; int /*<<< orphan*/  vtcon_ctrl_task; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int VTCON_FLAG_DETACHED ; 
 int VTCON_FLAG_MULTIPORT ; 
 int /*<<< orphan*/  VTCON_LOCK (struct vtcon_softc*) ; 
 int /*<<< orphan*/  VTCON_UNLOCK (struct vtcon_softc*) ; 
 struct vtcon_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  vtcon_ctrl_deinit (struct vtcon_softc*) ; 
 int /*<<< orphan*/  vtcon_destroy_ports (struct vtcon_softc*) ; 
 int /*<<< orphan*/  vtcon_stop (struct vtcon_softc*) ; 

__attribute__((used)) static int
vtcon_detach(device_t dev)
{
	struct vtcon_softc *sc;

	sc = device_get_softc(dev);

	VTCON_LOCK(sc);
	sc->vtcon_flags |= VTCON_FLAG_DETACHED;
	if (device_is_attached(dev))
		vtcon_stop(sc);
	VTCON_UNLOCK(sc);

	if (sc->vtcon_flags & VTCON_FLAG_MULTIPORT) {
		taskqueue_drain(taskqueue_thread, &sc->vtcon_ctrl_task);
		vtcon_ctrl_deinit(sc);
	}

	vtcon_destroy_ports(sc);
	mtx_destroy(&sc->vtcon_mtx);
	mtx_destroy(&sc->vtcon_ctrl_tx_mtx);

	return (0);
}