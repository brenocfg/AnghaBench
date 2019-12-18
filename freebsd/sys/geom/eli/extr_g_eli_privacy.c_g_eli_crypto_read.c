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
struct g_eli_softc {int sc_flags; TYPE_1__* sc_geom; int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_inflight; int /*<<< orphan*/  sc_queue; } ;
struct g_consumer {int /*<<< orphan*/  provider; } ;
struct bio {int /*<<< orphan*/  bio_to; int /*<<< orphan*/  bio_done; struct bio* bio_driver1; int /*<<< orphan*/ * bio_driver2; scalar_t__ bio_pflags; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_ELI_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int G_ELI_FLAG_SUSPEND ; 
 int /*<<< orphan*/  G_ELI_LOGREQ (int,struct bio*,char*) ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  g_eli_read_done ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct g_eli_softc*) ; 

void
g_eli_crypto_read(struct g_eli_softc *sc, struct bio *bp, boolean_t fromworker)
{
	struct g_consumer *cp;
	struct bio *cbp;

	if (!fromworker) {
		/*
		 * We are not called from the worker thread, so check if
		 * device is suspended.
		 */
		mtx_lock(&sc->sc_queue_mtx);
		if (sc->sc_flags & G_ELI_FLAG_SUSPEND) {
			/*
			 * If device is suspended, we place the request onto
			 * the queue, so it can be handled after resume.
			 */
			G_ELI_DEBUG(0, "device suspended, move onto queue");
			bioq_insert_tail(&sc->sc_queue, bp);
			mtx_unlock(&sc->sc_queue_mtx);
			wakeup(sc);
			return;
		}
		atomic_add_int(&sc->sc_inflight, 1);
		mtx_unlock(&sc->sc_queue_mtx);
	}
	bp->bio_pflags = 0;
	bp->bio_driver2 = NULL;
	cbp = bp->bio_driver1;
	cbp->bio_done = g_eli_read_done;
	cp = LIST_FIRST(&sc->sc_geom->consumer);
	cbp->bio_to = cp->provider;
	G_ELI_LOGREQ(2, cbp, "Sending request.");
	/*
	 * Read encrypted data from provider.
	 */
	g_io_request(cbp, cp);
}