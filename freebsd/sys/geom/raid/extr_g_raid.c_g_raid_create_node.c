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
struct g_raid_softc {struct g_geom* sc_geom; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_worker; int /*<<< orphan*/  sc_queue; int /*<<< orphan*/  sc_events; int /*<<< orphan*/  sc_disks; int /*<<< orphan*/  sc_volumes; scalar_t__ sc_flags; struct g_raid_md_object* sc_md; } ;
struct g_raid_md_object {int dummy; } ;
struct g_geom {struct g_raid_softc* softc; int /*<<< orphan*/  dumpconf; int /*<<< orphan*/  access; int /*<<< orphan*/  orphan; int /*<<< orphan*/  start; } ;
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG (int,char*,char const*) ; 
 int /*<<< orphan*/  G_RAID_DEBUG1 (int /*<<< orphan*/ ,struct g_raid_softc*,char*,char const*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_RAID ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct g_raid_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_destroy_geom (struct g_geom*) ; 
 struct g_geom* g_new_geomf (struct g_class*,char*,char const*) ; 
 int /*<<< orphan*/  g_raid_access ; 
 int /*<<< orphan*/  g_raid_dumpconf ; 
 int /*<<< orphan*/  g_raid_orphan ; 
 int /*<<< orphan*/  g_raid_start ; 
 int /*<<< orphan*/  g_raid_worker ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int kproc_create (int /*<<< orphan*/ ,struct g_raid_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 struct g_raid_softc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

struct g_raid_softc *
g_raid_create_node(struct g_class *mp,
    const char *name, struct g_raid_md_object *md)
{
	struct g_raid_softc *sc;
	struct g_geom *gp;
	int error;

	g_topology_assert();
	G_RAID_DEBUG(1, "Creating array %s.", name);

	gp = g_new_geomf(mp, "%s", name);
	sc = malloc(sizeof(*sc), M_RAID, M_WAITOK | M_ZERO);
	gp->start = g_raid_start;
	gp->orphan = g_raid_orphan;
	gp->access = g_raid_access;
	gp->dumpconf = g_raid_dumpconf;

	sc->sc_md = md;
	sc->sc_geom = gp;
	sc->sc_flags = 0;
	TAILQ_INIT(&sc->sc_volumes);
	TAILQ_INIT(&sc->sc_disks);
	sx_init(&sc->sc_lock, "graid:lock");
	mtx_init(&sc->sc_queue_mtx, "graid:queue", NULL, MTX_DEF);
	TAILQ_INIT(&sc->sc_events);
	bioq_init(&sc->sc_queue);
	gp->softc = sc;
	error = kproc_create(g_raid_worker, sc, &sc->sc_worker, 0, 0,
	    "g_raid %s", name);
	if (error != 0) {
		G_RAID_DEBUG(0, "Cannot create kernel thread for %s.", name);
		mtx_destroy(&sc->sc_queue_mtx);
		sx_destroy(&sc->sc_lock);
		g_destroy_geom(sc->sc_geom);
		free(sc, M_RAID);
		return (NULL);
	}

	G_RAID_DEBUG1(0, sc, "Array %s created.", name);
	return (sc);
}