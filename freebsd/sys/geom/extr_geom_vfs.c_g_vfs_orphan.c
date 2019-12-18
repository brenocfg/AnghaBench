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
struct g_vfs_softc {int sc_orphaned; scalar_t__ sc_active; int /*<<< orphan*/  sc_mtx; } ;
struct g_geom {struct g_vfs_softc* softc; int /*<<< orphan*/  name; } ;
struct g_consumer {struct g_geom* geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,struct g_consumer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_vfs_destroy (struct g_consumer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_vfs_orphan(struct g_consumer *cp)
{
	struct g_geom *gp;
	struct g_vfs_softc *sc;
	int destroy;

	g_topology_assert();

	gp = cp->geom;
	g_trace(G_T_TOPOLOGY, "g_vfs_orphan(%p(%s))", cp, gp->name);
	sc = gp->softc;
	if (sc == NULL)
		return;
	mtx_lock(&sc->sc_mtx);
	sc->sc_orphaned = 1;
	destroy = (sc->sc_active == 0);
	mtx_unlock(&sc->sc_mtx);
	if (destroy)
		g_vfs_destroy(cp, 0);

	/*
	 * Do not destroy the geom.  Filesystem will do that during unmount.
	 */
}