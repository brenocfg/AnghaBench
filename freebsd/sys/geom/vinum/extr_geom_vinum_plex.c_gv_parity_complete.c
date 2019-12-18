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
struct gv_softc {int dummy; } ;
struct gv_plex {scalar_t__ synced; int /*<<< orphan*/  name; TYPE_1__* vol_sc; scalar_t__ size; scalar_t__ stripesize; struct gv_softc* vinumconf; } ;
struct bio {int bio_error; int bio_pflags; int /*<<< orphan*/  bio_data; } ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_2__ {int /*<<< orphan*/  provider; } ;

/* Variables and functions */
 int EAGAIN ; 
 int GV_BIO_MALLOC ; 
 int GV_BIO_PARITY ; 
 int /*<<< orphan*/  GV_EVENT_SAVE_CONFIG ; 
 int /*<<< orphan*/  G_VINUM_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  gv_access (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_parity_request (struct gv_plex*,int,scalar_t__) ; 
 int /*<<< orphan*/  gv_post_event (struct gv_softc*,int /*<<< orphan*/ ,struct gv_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gv_parity_complete(struct gv_plex *p, struct bio *bp)
{
	struct gv_softc *sc;
	int error, flags;

	error = bp->bio_error;
	flags = bp->bio_pflags;
	flags &= ~GV_BIO_MALLOC;

	sc = p->vinumconf;
	KASSERT(sc != NULL, ("gv_parity_complete: NULL sc"));

	/* Clean up what we allocated. */
	if (bp->bio_pflags & GV_BIO_MALLOC)
		g_free(bp->bio_data);
	g_destroy_bio(bp);

	if (error == EAGAIN) {
		G_VINUM_DEBUG(0, "parity incorrect at offset 0x%jx",
		    (intmax_t)p->synced);
	}

	/* Any error is fatal, except EAGAIN when we're rebuilding. */
	if (error && !(error == EAGAIN && (flags & GV_BIO_PARITY))) {
		/* Make sure we don't have the lock. */
		g_topology_assert_not();
		g_topology_lock();
		gv_access(p->vol_sc->provider, -1, -1, 0);
		g_topology_unlock();
		G_VINUM_DEBUG(0, "parity check on %s failed at 0x%jx "
		    "errno %d", p->name, (intmax_t)p->synced, error);
		return;
	} else {
		p->synced += p->stripesize;
	}

	if (p->synced >= p->size) {
		/* Make sure we don't have the lock. */
		g_topology_assert_not();
		g_topology_lock();
		gv_access(p->vol_sc->provider, -1, -1, 0);
		g_topology_unlock();
		/* We're finished. */
		G_VINUM_DEBUG(1, "parity operation on %s finished", p->name);
		p->synced = 0;
		gv_post_event(sc, GV_EVENT_SAVE_CONFIG, sc, NULL, 0, 0);
		return;
	}

	/* Send down next. It will determine if we need to itself. */
	gv_parity_request(p, flags, p->synced);
}