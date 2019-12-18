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
struct gv_volume {int flags; int /*<<< orphan*/  plexes; int /*<<< orphan*/  plexcount; } ;
struct gv_softc {int /*<<< orphan*/  plexes; } ;
struct gv_plex {void* rqueue; void* wqueue; void* bqueue; int /*<<< orphan*/  packets; int /*<<< orphan*/  subdisks; int /*<<< orphan*/  flags; scalar_t__ synced; struct gv_softc* vinumconf; struct gv_volume* vol_sc; int /*<<< orphan*/  volume; int /*<<< orphan*/  name; } ;
struct bio_queue_head {int dummy; } ;

/* Variables and functions */
 int GV_ERR_CREATE ; 
 int /*<<< orphan*/  GV_PLEX_ADDED ; 
 int /*<<< orphan*/  GV_PLEX_NEWBORN ; 
 int GV_VOL_NEWBORN ; 
 int /*<<< orphan*/  G_VINUM_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct gv_plex*,int /*<<< orphan*/ ) ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_init (void*) ; 
 int /*<<< orphan*/  g_free (struct gv_plex*) ; 
 void* g_malloc (int,int) ; 
 struct gv_volume* gv_find_vol (struct gv_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_volume ; 
 int /*<<< orphan*/  plex ; 

int
gv_create_plex(struct gv_softc *sc, struct gv_plex *p)
{
	struct gv_volume *v;

	KASSERT(p != NULL, ("gv_create_plex: NULL p"));

	/* Find the volume this plex should be attached to. */
	v = gv_find_vol(sc, p->volume);
	if (v == NULL) {
		G_VINUM_DEBUG(0, "create plex '%s': volume '%s' not found",
		    p->name, p->volume);
		g_free(p);
		return (GV_ERR_CREATE);
	}
	if (!(v->flags & GV_VOL_NEWBORN))
		p->flags |= GV_PLEX_ADDED;
	p->vol_sc = v;
	v->plexcount++;
	p->vinumconf = sc;
	p->synced = 0;
	p->flags |= GV_PLEX_NEWBORN;
	LIST_INSERT_HEAD(&v->plexes, p, in_volume);
	LIST_INIT(&p->subdisks);
	TAILQ_INIT(&p->packets);
	LIST_INSERT_HEAD(&sc->plexes, p, plex);
	p->bqueue = g_malloc(sizeof(struct bio_queue_head), M_WAITOK | M_ZERO);
	bioq_init(p->bqueue);
	p->wqueue = g_malloc(sizeof(struct bio_queue_head), M_WAITOK | M_ZERO);
	bioq_init(p->wqueue);
	p->rqueue = g_malloc(sizeof(struct bio_queue_head), M_WAITOK | M_ZERO);
	bioq_init(p->rqueue);
	return (0);
}