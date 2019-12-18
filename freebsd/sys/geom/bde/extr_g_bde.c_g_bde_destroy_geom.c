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
struct gctl_req {int dummy; } ;
struct g_provider {scalar_t__ acr; scalar_t__ acw; scalar_t__ ace; int /*<<< orphan*/  consumers; } ;
struct g_geom {int /*<<< orphan*/  consumer; struct g_bde_softc* softc; int /*<<< orphan*/  provider; int /*<<< orphan*/  name; } ;
struct g_consumer {int dummy; } ;
struct g_class {int /*<<< orphan*/  name; } ;
struct g_bde_softc {int dead; int /*<<< orphan*/  key; int /*<<< orphan*/  worklist_mutex; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 void* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_access (struct g_consumer*,int,int,int) ; 
 int /*<<< orphan*/  g_destroy_consumer (struct g_consumer*) ; 
 int /*<<< orphan*/  g_detach (struct g_consumer*) ; 
 int /*<<< orphan*/  g_free (struct g_bde_softc*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_wither_geom (struct g_geom*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsleep (struct g_bde_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct g_bde_softc*) ; 

__attribute__((used)) static int
g_bde_destroy_geom(struct gctl_req *req, struct g_class *mp, struct g_geom *gp)
{
	struct g_consumer *cp;
	struct g_provider *pp;
	struct g_bde_softc *sc;

	g_trace(G_T_TOPOLOGY, "g_bde_destroy_geom(%s, %s)", mp->name, gp->name);
	g_topology_assert();
	/*
	 * Orderly detachment.
	 */
	KASSERT(gp != NULL, ("NULL geom"));
	pp = LIST_FIRST(&gp->provider);
	KASSERT(pp != NULL, ("NULL provider"));
	if (pp->acr > 0 || pp->acw > 0 || pp->ace > 0)
		return (EBUSY);
	sc = gp->softc;
	cp = LIST_FIRST(&gp->consumer);
	KASSERT(cp != NULL, ("NULL consumer"));
	sc->dead = 1;
	wakeup(sc);
	g_access(cp, -1, -1, -1);
	g_detach(cp);
	g_destroy_consumer(cp);
	while (sc->dead != 2 && !LIST_EMPTY(&pp->consumers))
		tsleep(sc, PRIBIO, "g_bdedie", hz);
	mtx_destroy(&sc->worklist_mutex);
	bzero(&sc->key, sizeof sc->key);
	g_free(sc);
	g_wither_geom(gp, ENXIO);
	return (0);
}