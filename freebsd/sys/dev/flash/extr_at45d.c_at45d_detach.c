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
struct at45d_softc {scalar_t__ taskstate; int /*<<< orphan*/  dummybuf; int /*<<< orphan*/  bio_queue; scalar_t__ disk; int /*<<< orphan*/  dev; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT45D_LOCK (struct at45d_softc*) ; 
 int /*<<< orphan*/  AT45D_LOCK_DESTROY (struct at45d_softc*) ; 
 int /*<<< orphan*/  AT45D_UNLOCK (struct at45d_softc*) ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 scalar_t__ TSTATE_RUNNING ; 
 scalar_t__ TSTATE_STOPPED ; 
 scalar_t__ TSTATE_STOPPING ; 
 int /*<<< orphan*/  bioq_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct at45d_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disk_destroy (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hz ; 
 int msleep (struct at45d_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wakeup (struct at45d_softc*) ; 

__attribute__((used)) static int
at45d_detach(device_t dev)
{
	struct at45d_softc *sc;
	int err;

	sc = device_get_softc(dev);
	err = 0;

	AT45D_LOCK(sc);
	if (sc->taskstate == TSTATE_RUNNING) {
		sc->taskstate = TSTATE_STOPPING;
		wakeup(sc);
		while (err == 0 && sc->taskstate != TSTATE_STOPPED) {
			err = msleep(sc, &sc->sc_mtx, 0, "at45dt", hz * 3);
			if (err != 0) {
				sc->taskstate = TSTATE_RUNNING;
				device_printf(sc->dev,
				    "Failed to stop queue task\n");
			}
		}
	}
	AT45D_UNLOCK(sc);

	if (err == 0 && sc->taskstate == TSTATE_STOPPED) {
		if (sc->disk) {
			disk_destroy(sc->disk);
			bioq_flush(&sc->bio_queue, NULL, ENXIO);
			free(sc->dummybuf, M_DEVBUF);
		}
		AT45D_LOCK_DESTROY(sc);
	}
	return (err);
}