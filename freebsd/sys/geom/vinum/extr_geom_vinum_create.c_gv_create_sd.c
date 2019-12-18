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
struct gv_softc {int /*<<< orphan*/  subdisks; } ;
struct gv_sd {int flags; struct gv_softc* vinumconf; TYPE_1__* drive_sc; int /*<<< orphan*/  name; int /*<<< orphan*/  plex; int /*<<< orphan*/  drive; } ;
struct gv_plex {int flags; int /*<<< orphan*/  name; } ;
struct gv_drive {int flags; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int GV_DRIVE_REFERENCED ; 
 int GV_ERR_CREATE ; 
 int GV_PLEX_NEWBORN ; 
 int GV_SD_NEWBORN ; 
 int GV_SD_TASTED ; 
 int /*<<< orphan*/  G_VINUM_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct gv_sd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct gv_sd*,int /*<<< orphan*/ ) ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  from_drive ; 
 int /*<<< orphan*/  g_free (struct gv_sd*) ; 
 struct gv_drive* g_malloc (int,int) ; 
 int /*<<< orphan*/  gv_create_drive (struct gv_softc*,struct gv_drive*) ; 
 struct gv_drive* gv_find_drive (struct gv_softc*,int /*<<< orphan*/ ) ; 
 struct gv_plex* gv_find_plex (struct gv_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_free_sd (struct gv_sd*) ; 
 int /*<<< orphan*/  gv_rm_plex (struct gv_softc*,struct gv_plex*) ; 
 scalar_t__ gv_sd_to_drive (struct gv_sd*,struct gv_drive*) ; 
 scalar_t__ gv_sd_to_plex (struct gv_sd*,struct gv_plex*) ; 
 int /*<<< orphan*/  sd ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
gv_create_sd(struct gv_softc *sc, struct gv_sd *s)
{
	struct gv_plex *p;
	struct gv_drive *d;

	KASSERT(s != NULL, ("gv_create_sd: NULL s"));

	/* Find the drive where this subdisk should be put on. */
	d = gv_find_drive(sc, s->drive);
	if (d == NULL) {
		/*
		 * It's possible that the subdisk references a drive that
		 * doesn't exist yet (during the taste process), so create a
		 * practically empty "referenced" drive.
		 */
		if (s->flags & GV_SD_TASTED) {
			d = g_malloc(sizeof(struct gv_drive),
			    M_WAITOK | M_ZERO);
			d->flags |= GV_DRIVE_REFERENCED;
			strlcpy(d->name, s->drive, sizeof(d->name));
			gv_create_drive(sc, d);
		} else {
			G_VINUM_DEBUG(0, "create sd '%s': drive '%s' not found",
			    s->name, s->drive);
			g_free(s);
			return (GV_ERR_CREATE);
		}
	}

	/* Find the plex where this subdisk belongs to. */
	p = gv_find_plex(sc, s->plex);
	if (p == NULL) {
		G_VINUM_DEBUG(0, "create sd '%s': plex '%s' not found",
		    s->name, s->plex);
		g_free(s);
		return (GV_ERR_CREATE);
	}

	/*
	 * First we give the subdisk to the drive, to handle autosized
	 * values ...
	 */
	if (gv_sd_to_drive(s, d) != 0) {
		g_free(s);
		return (GV_ERR_CREATE);
	}

	/*
	 * Then, we give the subdisk to the plex; we check if the
	 * given values are correct and maybe adjust them.
	 */
	if (gv_sd_to_plex(s, p) != 0) {
		G_VINUM_DEBUG(0, "unable to give sd '%s' to plex '%s'",
		    s->name, p->name);
		if (s->drive_sc && !(s->drive_sc->flags & GV_DRIVE_REFERENCED))
			LIST_REMOVE(s, from_drive);
		gv_free_sd(s);
		g_free(s);
		/*
		 * If this subdisk can't be created, we won't create
		 * the attached plex either, if it is also a new one.
		 */
		if (!(p->flags & GV_PLEX_NEWBORN))
			return (GV_ERR_CREATE);
		gv_rm_plex(sc, p);
		return (GV_ERR_CREATE);
	}
	s->flags |= GV_SD_NEWBORN;

	s->vinumconf = sc;
	LIST_INSERT_HEAD(&sc->subdisks, s, sd);

	return (0);
}