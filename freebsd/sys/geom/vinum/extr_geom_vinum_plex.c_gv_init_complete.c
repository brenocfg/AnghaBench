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
struct gv_sd {scalar_t__ drive_offset; scalar_t__ size; scalar_t__ initialized; int /*<<< orphan*/  name; struct gv_drive* drive_sc; } ;
struct gv_plex {struct gv_softc* vinumconf; } ;
struct gv_drive {struct g_consumer* consumer; } ;
struct g_consumer {int dummy; } ;
struct bio {scalar_t__ bio_offset; scalar_t__ bio_length; int bio_error; int /*<<< orphan*/ * bio_data; struct gv_sd* bio_caller1; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GV_EVENT_SAVE_CONFIG ; 
 int /*<<< orphan*/  GV_SD_STALE ; 
 int /*<<< orphan*/  GV_SD_UP ; 
 int GV_SETSTATE_CONFIG ; 
 int GV_SETSTATE_FORCE ; 
 int /*<<< orphan*/  G_VINUM_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_access (struct g_consumer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  gv_init_request (struct gv_sd*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gv_post_event (struct gv_softc*,int /*<<< orphan*/ ,struct gv_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_set_sd_state (struct gv_sd*,int /*<<< orphan*/ ,int) ; 

void
gv_init_complete(struct gv_plex *p, struct bio *bp)
{
	struct gv_softc *sc;
	struct gv_drive *d;
	struct g_consumer *cp;
	struct gv_sd *s;
	off_t start, length;
	caddr_t data;
	int error;

	s = bp->bio_caller1;
	start = bp->bio_offset;
	length = bp->bio_length;
	error = bp->bio_error;
	data = bp->bio_data;

	KASSERT(s != NULL, ("gv_init_complete: NULL s"));
	d = s->drive_sc;
	KASSERT(d != NULL, ("gv_init_complete: NULL d"));
	cp = d->consumer;
	KASSERT(cp != NULL, ("gv_init_complete: NULL cp"));
	sc = p->vinumconf;
	KASSERT(sc != NULL, ("gv_init_complete: NULL sc"));

	g_destroy_bio(bp);

	/*
	 * First we need to find out if it was okay, and abort if it's not.
	 * Then we need to free previous buffers, find out the correct subdisk,
	 * as well as getting the correct starting point and length of the BIO.
	 */
	if (start >= s->drive_offset + s->size) {
		/* Free the data we initialized. */
		if (data != NULL)
			g_free(data);
		g_topology_assert_not();
		g_topology_lock();
		g_access(cp, 0, -1, 0);
		g_topology_unlock();
		if (error) {
			gv_set_sd_state(s, GV_SD_STALE, GV_SETSTATE_FORCE |
			    GV_SETSTATE_CONFIG);
		} else {
			gv_set_sd_state(s, GV_SD_UP, GV_SETSTATE_CONFIG);
			s->initialized = 0;
			gv_post_event(sc, GV_EVENT_SAVE_CONFIG, sc, NULL, 0, 0);
			G_VINUM_DEBUG(1, "subdisk '%s' init: finished "
			    "successfully", s->name);
		}
		return;
	}
	s->initialized += length;
	start += length;
	gv_init_request(s, start, data, length);
}