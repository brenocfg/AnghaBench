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
struct ps3disk_softc {int /*<<< orphan*/  sc_dmatag; int /*<<< orphan*/  sc_deferredq; int /*<<< orphan*/  sc_task; } ;
struct bio {int /*<<< orphan*/ * bio_driver1; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  PS3DISK_LOCK (struct ps3disk_softc*) ; 
 int /*<<< orphan*/  PS3DISK_UNLOCK (struct ps3disk_softc*) ; 
 struct bio* bioq_takefirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kproc_suspend_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps3disk_strategy (struct bio*) ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
ps3disk_task(void *arg)
{
	struct ps3disk_softc *sc = (struct ps3disk_softc *) arg;
	struct bio *bp;

	
	while (1) {
		kproc_suspend_check(sc->sc_task);
		tsleep(&sc->sc_deferredq, PRIBIO, "ps3disk", 10);

		PS3DISK_LOCK(sc);
		bp = bioq_takefirst(&sc->sc_deferredq);
		PS3DISK_UNLOCK(sc);

		if (bp == NULL)
			continue;

		if (bp->bio_driver1 != NULL) {
			bus_dmamap_unload(sc->sc_dmatag, (bus_dmamap_t)
			    bp->bio_driver1);
			bus_dmamap_destroy(sc->sc_dmatag, (bus_dmamap_t)
			    bp->bio_driver1);
		}

		ps3disk_strategy(bp);
	}

	kproc_exit(0);
}