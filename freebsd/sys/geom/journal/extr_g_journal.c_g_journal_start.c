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
struct g_journal_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_regular_queue; } ;
struct bio {int bio_cmd; TYPE_2__* bio_to; int /*<<< orphan*/  bio_completed; int /*<<< orphan*/  bio_length; int /*<<< orphan*/  bio_data; int /*<<< orphan*/  bio_attribute; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_journal_softc* softc; } ;

/* Variables and functions */
#define  BIO_DELETE 131 
#define  BIO_GETATTR 130 
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  GJ_LOGREQ (int,struct bio*,char*) ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct g_journal_softc*) ; 

__attribute__((used)) static void
g_journal_start(struct bio *bp)
{
	struct g_journal_softc *sc;

	sc = bp->bio_to->geom->softc;
	GJ_LOGREQ(3, bp, "Request received.");

	switch (bp->bio_cmd) {
	case BIO_READ:
	case BIO_WRITE:
		mtx_lock(&sc->sc_mtx);
		bioq_insert_tail(&sc->sc_regular_queue, bp);
		wakeup(sc);
		mtx_unlock(&sc->sc_mtx);
		return;
	case BIO_GETATTR:
		if (strcmp(bp->bio_attribute, "GJOURNAL::provider") == 0) {
			strlcpy(bp->bio_data, bp->bio_to->name, bp->bio_length);
			bp->bio_completed = strlen(bp->bio_to->name) + 1;
			g_io_deliver(bp, 0);
			return;
		}
		/* FALLTHROUGH */
	case BIO_DELETE:
	default:
		g_io_deliver(bp, EOPNOTSUPP);
		return;
	}
}