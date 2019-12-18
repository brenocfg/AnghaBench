#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct g_journal_softc {struct g_consumer* sc_dconsumer; int /*<<< orphan*/  sc_copy_in_progress; } ;
struct g_consumer {int dummy; } ;
struct bio {scalar_t__ bio_cflags; scalar_t__ bio_error; int /*<<< orphan*/  bio_data; int /*<<< orphan*/  bio_length; TYPE_3__* bio_to; struct bio* bio_parent; TYPE_2__* bio_from; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__* geom; } ;
struct TYPE_4__ {struct g_journal_softc* softc; } ;

/* Variables and functions */
 scalar_t__ GJ_BIO_COPY ; 
 int /*<<< orphan*/  GJ_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GJ_LOGREQ (int,struct bio*,char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 
 int /*<<< orphan*/  gj_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_journal_copy_read_done(struct bio *bp)
{
	struct g_journal_softc *sc;
	struct g_consumer *cp;
	struct bio *pbp;

	KASSERT(bp->bio_cflags == GJ_BIO_COPY,
	    ("Invalid bio (%d != %d).", bp->bio_cflags, GJ_BIO_COPY));

	sc = bp->bio_from->geom->softc;
	pbp = bp->bio_parent;

	if (bp->bio_error != 0) {
		GJ_DEBUG(0, "Error while reading data from %s (error=%d).",
		    bp->bio_to->name, bp->bio_error);
		/*
		 * We will not be able to deliver WRITE request as well.
		 */
		gj_free(bp->bio_data, bp->bio_length);
		g_destroy_bio(pbp);
		g_destroy_bio(bp);
		sc->sc_copy_in_progress--;
		return (1);
	}
	pbp->bio_data = bp->bio_data;
	cp = sc->sc_dconsumer;
	g_io_request(pbp, cp);
	GJ_LOGREQ(4, bp, "READ DONE");
	g_destroy_bio(bp);
	return (0);
}