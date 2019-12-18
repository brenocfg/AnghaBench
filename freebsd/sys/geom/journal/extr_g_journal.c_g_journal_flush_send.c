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
struct g_journal_softc {scalar_t__ sc_flush_in_progress; struct bio* sc_flush_queue; int /*<<< orphan*/  sc_flush_count; struct g_consumer* sc_jconsumer; } ;
struct g_consumer {int dummy; } ;
struct bio {scalar_t__ bio_joffset; scalar_t__ bio_offset; } ;

/* Variables and functions */
 struct bio* GJQ_FIRST (struct bio*) ; 
 int /*<<< orphan*/  GJQ_INSERT_AFTER (struct bio*,struct bio*,struct bio*) ; 
 int /*<<< orphan*/  GJQ_REMOVE (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  GJ_LOGREQ (int,struct bio*,char*) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 
 scalar_t__ g_journal_do_optimize ; 
 scalar_t__ g_journal_optimize (struct bio*) ; 
 scalar_t__ g_journal_parallel_flushes ; 
 int /*<<< orphan*/  g_journal_release_delayed (struct g_journal_softc*) ; 

__attribute__((used)) static void
g_journal_flush_send(struct g_journal_softc *sc)
{
	struct g_consumer *cp;
	struct bio *bioq, *bp, *lbp;

	cp = sc->sc_jconsumer;
	bioq = lbp = NULL;
	while (sc->sc_flush_in_progress < g_journal_parallel_flushes) {
		/* Send one flush requests to the active journal. */
		bp = GJQ_FIRST(sc->sc_flush_queue);
		if (bp != NULL) {
			GJQ_REMOVE(sc->sc_flush_queue, bp);
			sc->sc_flush_count--;
			bp->bio_offset = bp->bio_joffset;
			bp->bio_joffset = 0;
			sc->sc_flush_in_progress++;
			GJQ_INSERT_AFTER(bioq, bp, lbp);
			lbp = bp;
		}
		/* Try to release delayed requests. */
		g_journal_release_delayed(sc);
		/* If there are no requests to flush, leave. */
		if (GJQ_FIRST(sc->sc_flush_queue) == NULL)
			break;
	}
	if (g_journal_do_optimize)
		sc->sc_flush_in_progress += g_journal_optimize(bioq);
	while ((bp = GJQ_FIRST(bioq)) != NULL) {
		GJQ_REMOVE(bioq, bp);
		GJ_LOGREQ(3, bp, "Flush request send");
		g_io_request(bp, cp);
	}
}