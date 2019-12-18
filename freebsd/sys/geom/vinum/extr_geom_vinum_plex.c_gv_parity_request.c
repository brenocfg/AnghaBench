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
struct gv_softc {int dummy; } ;
struct gv_plex {int /*<<< orphan*/  stripesize; int /*<<< orphan*/  name; struct gv_softc* vinumconf; } ;
struct bio {int bio_pflags; int /*<<< orphan*/  bio_offset; void* bio_data; struct gv_plex* bio_caller1; int /*<<< orphan*/  bio_length; scalar_t__ bio_error; int /*<<< orphan*/  bio_done; int /*<<< orphan*/  bio_cmd; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_WRITE ; 
 int GV_BIO_CHECK ; 
 int GV_BIO_MALLOC ; 
 int GV_BIO_REBUILD ; 
 int /*<<< orphan*/  GV_DFLT_SYNCSIZE ; 
 int /*<<< orphan*/  G_VINUM_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* g_malloc (int /*<<< orphan*/ ,int) ; 
 struct bio* g_new_bio () ; 
 int /*<<< orphan*/  gv_done ; 
 int /*<<< orphan*/  gv_post_bio (struct gv_softc*,struct bio*) ; 

void
gv_parity_request(struct gv_plex *p, int flags, off_t offset)
{
	struct gv_softc *sc;
	struct bio *bp;

	KASSERT(p != NULL, ("gv_parity_request: NULL p"));
	sc = p->vinumconf;
	KASSERT(sc != NULL, ("gv_parity_request: NULL sc"));

	bp = g_new_bio();
	if (bp == NULL) {
		G_VINUM_DEBUG(0, "rebuild of %s failed creating bio: "
		    "out of memory", p->name);
		return;
	}

	bp->bio_cmd = BIO_WRITE;
	bp->bio_done = gv_done;
	bp->bio_error = 0;
	bp->bio_length = p->stripesize;
	bp->bio_caller1 = p;

	/*
	 * Check if it's a rebuild of a degraded plex or a user request of
	 * parity rebuild.
	 */
	if (flags & GV_BIO_REBUILD)
		bp->bio_data = g_malloc(GV_DFLT_SYNCSIZE, M_WAITOK);
	else if (flags & GV_BIO_CHECK)
		bp->bio_data = g_malloc(p->stripesize, M_WAITOK | M_ZERO);
	else {
		G_VINUM_DEBUG(0, "invalid flags given in rebuild");
		return;
	}

	bp->bio_pflags = flags;
	bp->bio_pflags |= GV_BIO_MALLOC;

	/* We still have more parity to build. */
	bp->bio_offset = offset;
	gv_post_bio(sc, bp);
	//gv_plex_start(p, bp); /* Send it down to the plex. */
}