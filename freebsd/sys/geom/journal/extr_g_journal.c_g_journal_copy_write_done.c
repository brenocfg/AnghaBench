#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_journal_softc {scalar_t__ sc_copy_in_progress; scalar_t__ sc_journal_copying; int /*<<< orphan*/  sc_copy_queue; } ;
struct bio {scalar_t__ bio_cflags; scalar_t__ bio_error; int /*<<< orphan*/  bio_length; int /*<<< orphan*/  bio_data; TYPE_2__* bio_from; } ;
struct TYPE_4__ {TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_journal_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GJQ_REMOVE (int /*<<< orphan*/ ,struct bio*) ; 
 scalar_t__ GJ_BIO_COPY ; 
 int /*<<< orphan*/  GJ_DEBUG (int,char*) ; 
 int /*<<< orphan*/  GJ_LOGREQ (int,struct bio*,char*,...) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  gj_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_journal_copy_write_done(struct bio *bp)
{
	struct g_journal_softc *sc;

	KASSERT(bp->bio_cflags == GJ_BIO_COPY,
	    ("Invalid bio (%d != %d).", bp->bio_cflags, GJ_BIO_COPY));

	sc = bp->bio_from->geom->softc;
	sc->sc_copy_in_progress--;

	if (bp->bio_error != 0) {
		GJ_LOGREQ(0, bp, "[copy] Error while writing data (error=%d)",
		    bp->bio_error);
	}
	GJQ_REMOVE(sc->sc_copy_queue, bp);
	gj_free(bp->bio_data, bp->bio_length);
	GJ_LOGREQ(4, bp, "DONE");
	g_destroy_bio(bp);

	if (sc->sc_copy_in_progress == 0) {
		/*
		 * This was the last write request for this journal.
		 */
		GJ_DEBUG(1, "Data has been copied.");
		sc->sc_journal_copying = 0;
	}
}