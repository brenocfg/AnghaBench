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
struct TYPE_2__ {struct bio* jj_queue; } ;
struct g_journal_softc {scalar_t__ sc_copy_in_progress; int /*<<< orphan*/  sc_dconsumer; int /*<<< orphan*/  sc_copy_queue; int /*<<< orphan*/  sc_mtx; TYPE_1__ sc_inactive; } ;
struct bio {scalar_t__ bio_joffset; int /*<<< orphan*/ * bio_data; int /*<<< orphan*/  bio_cflags; } ;

/* Variables and functions */
 struct bio* GJQ_FIRST (struct bio*) ; 
 int /*<<< orphan*/  GJQ_INSERT_AFTER (struct bio*,struct bio*,struct bio*) ; 
 int /*<<< orphan*/  GJQ_INSERT_HEAD (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  GJQ_REMOVE (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  GJ_BIO_COPY ; 
 int /*<<< orphan*/  GJ_LOGREQ (int,struct bio*,char*) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ g_journal_do_optimize ; 
 scalar_t__ g_journal_optimize (struct bio*) ; 
 scalar_t__ g_journal_parallel_copies ; 
 int /*<<< orphan*/  g_journal_read_first (struct g_journal_softc*,struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_journal_copy_send(struct g_journal_softc *sc)
{
	struct bio *bioq, *bp, *lbp;

	bioq = lbp = NULL;
	mtx_lock(&sc->sc_mtx);
	for (; sc->sc_copy_in_progress < g_journal_parallel_copies;) {
		bp = GJQ_FIRST(sc->sc_inactive.jj_queue);
		if (bp == NULL)
			break;
		GJQ_REMOVE(sc->sc_inactive.jj_queue, bp);
		sc->sc_copy_in_progress++;
		GJQ_INSERT_AFTER(bioq, bp, lbp);
		lbp = bp;
	}
	mtx_unlock(&sc->sc_mtx);
	if (g_journal_do_optimize)
		sc->sc_copy_in_progress += g_journal_optimize(bioq);
	while ((bp = GJQ_FIRST(bioq)) != NULL) {
		GJQ_REMOVE(bioq, bp);
		GJQ_INSERT_HEAD(sc->sc_copy_queue, bp);
		bp->bio_cflags = GJ_BIO_COPY;
		if (bp->bio_data == NULL)
			g_journal_read_first(sc, bp);
		else {
			bp->bio_joffset = 0;
			GJ_LOGREQ(4, bp, "SEND");
			g_io_request(bp, sc->sc_dconsumer);
		}
	}
}