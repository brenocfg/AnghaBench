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
struct gctl_req {int dummy; } ;
struct g_geom {struct gv_softc* softc; } ;
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,struct g_class*) ; 
 int /*<<< orphan*/  g_wither_geom (struct g_geom*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gv_worker_exit (struct gv_softc*) ; 

__attribute__((used)) static int
gv_unload(struct gctl_req *req, struct g_class *mp, struct g_geom *gp)
{
	struct gv_softc *sc;

	g_trace(G_T_TOPOLOGY, "gv_unload(%p)", mp);

	g_topology_assert();
	sc = gp->softc;

	if (sc != NULL) {
		gv_worker_exit(sc);
		gp->softc = NULL;
		g_wither_geom(gp, ENXIO);
	}

	return (0);
}