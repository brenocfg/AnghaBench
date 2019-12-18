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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct cyapa_softc {int detaching; int /*<<< orphan*/  mutex; TYPE_1__ selinfo; int /*<<< orphan*/  devnode; scalar_t__ poll_thread_running; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCATCH ; 
 int /*<<< orphan*/  cyapa_lock (struct cyapa_softc*) ; 
 int /*<<< orphan*/  cyapa_unlock (struct cyapa_softc*) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 struct cyapa_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  knlist_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seldrain (TYPE_1__*) ; 

__attribute__((used)) static int
cyapa_detach(device_t dev)
{
	struct cyapa_softc *sc;

	sc = device_get_softc(dev);

	/* Cleanup poller thread */
	cyapa_lock(sc);
	while (sc->poll_thread_running) {
		sc->detaching = 1;
		mtx_sleep(&sc->detaching, &sc->mutex, PCATCH, "cyapadet", hz);
	}
	cyapa_unlock(sc);

	destroy_dev(sc->devnode);

	knlist_clear(&sc->selinfo.si_note, 0);
	seldrain(&sc->selinfo);
	knlist_destroy(&sc->selinfo.si_note);

	mtx_destroy(&sc->mutex);

	return (0);
}