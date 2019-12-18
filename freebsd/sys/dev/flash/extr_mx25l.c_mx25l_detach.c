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
struct mx25l_softc {scalar_t__ sc_taskstate; int /*<<< orphan*/  sc_bio_queue; int /*<<< orphan*/  sc_disk; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  M25PXX_LOCK (struct mx25l_softc*) ; 
 int /*<<< orphan*/  M25PXX_LOCK_DESTROY (struct mx25l_softc*) ; 
 int /*<<< orphan*/  M25PXX_UNLOCK (struct mx25l_softc*) ; 
 scalar_t__ TSTATE_RUNNING ; 
 scalar_t__ TSTATE_STOPPED ; 
 scalar_t__ TSTATE_STOPPING ; 
 int /*<<< orphan*/  bioq_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mx25l_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disk_destroy (int /*<<< orphan*/ ) ; 
 int hz ; 
 int msleep (struct mx25l_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wakeup (struct mx25l_softc*) ; 

__attribute__((used)) static int
mx25l_detach(device_t dev)
{
	struct mx25l_softc *sc;
	int err;

	sc = device_get_softc(dev);
	err = 0;

	M25PXX_LOCK(sc);
	if (sc->sc_taskstate == TSTATE_RUNNING) {
		sc->sc_taskstate = TSTATE_STOPPING;
		wakeup(sc);
		while (err == 0 && sc->sc_taskstate != TSTATE_STOPPED) {
			err = msleep(sc, &sc->sc_mtx, 0, "mx25dt", hz * 3);
			if (err != 0) {
				sc->sc_taskstate = TSTATE_RUNNING;
				device_printf(sc->sc_dev,
				    "Failed to stop queue task\n");
			}
		}
	}
	M25PXX_UNLOCK(sc);

	if (err == 0 && sc->sc_taskstate == TSTATE_STOPPED) {
		disk_destroy(sc->sc_disk);
		bioq_flush(&sc->sc_bio_queue, NULL, ENXIO);
		M25PXX_LOCK_DESTROY(sc);
	}
	return (err);
}