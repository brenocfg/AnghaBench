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
struct gv_volume {int dummy; } ;
struct gv_softc {int dummy; } ;
struct gv_sd {struct gv_plex* plex_sc; } ;
struct gv_plex {int org; struct gv_volume* vol_sc; } ;
struct bio {struct gv_sd* bio_caller1; } ;

/* Variables and functions */
#define  GV_PLEX_CONCAT 130 
#define  GV_PLEX_RAID5 129 
#define  GV_PLEX_STRIPED 128 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gv_plex_normal_done (struct gv_plex*,struct bio*) ; 
 int /*<<< orphan*/  gv_plex_raid5_done (struct gv_plex*,struct bio*) ; 

void
gv_bio_done(struct gv_softc *sc, struct bio *bp)
{
	struct gv_volume *v;
	struct gv_plex *p;
	struct gv_sd *s;

	s = bp->bio_caller1;
	KASSERT(s != NULL, ("gv_bio_done: NULL s"));
	p = s->plex_sc;
	KASSERT(p != NULL, ("gv_bio_done: NULL p"));
	v = p->vol_sc;
	KASSERT(v != NULL, ("gv_bio_done: NULL v"));

	switch (p->org) {
	case GV_PLEX_CONCAT:
	case GV_PLEX_STRIPED:
		gv_plex_normal_done(p, bp);
		break;
	case GV_PLEX_RAID5:
		gv_plex_raid5_done(p, bp);
		break;
	}
}