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
struct mambodisk_softc {int running; int /*<<< orphan*/  disk; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBODISK_LOCK (struct mambodisk_softc*) ; 
 int /*<<< orphan*/  MBODISK_LOCK_DESTROY (struct mambodisk_softc*) ; 
 int /*<<< orphan*/  MBODISK_UNLOCK (struct mambodisk_softc*) ; 
 int /*<<< orphan*/  PRIBIO ; 
 struct mambodisk_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (struct mambodisk_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct mambodisk_softc*) ; 

__attribute__((used)) static int
mambodisk_detach(device_t dev)
{
	struct mambodisk_softc *sc = device_get_softc(dev);

	/* kill thread */
	MBODISK_LOCK(sc);
	sc->running = 0;
	wakeup(sc);
	MBODISK_UNLOCK(sc);

	/* wait for thread to finish.  XXX probably want timeout.  -sorbo */
	MBODISK_LOCK(sc);
	while (sc->running != -1)
		msleep(sc, &sc->sc_mtx, PRIBIO, "detach", 0);
	MBODISK_UNLOCK(sc);

	/* kill disk */
	disk_destroy(sc->disk);
	/* XXX destroy anything in queue */

	MBODISK_LOCK_DESTROY(sc);

	return (0);
}