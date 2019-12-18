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
struct g_provider {int /*<<< orphan*/  name; struct g_geom* geom; } ;
struct g_mountver_softc {int sc_access_r; int sc_access_w; int sc_access_e; scalar_t__ sc_orphaned; } ;
struct g_geom {struct g_mountver_softc* softc; int /*<<< orphan*/  consumer; } ;
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int g_access (struct g_consumer*,int,int,int) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

__attribute__((used)) static int
g_mountver_access(struct g_provider *pp, int dr, int dw, int de)
{
	struct g_mountver_softc *sc;
	struct g_geom *gp;
	struct g_consumer *cp;

	g_topology_assert();

	gp = pp->geom;
	cp = LIST_FIRST(&gp->consumer);
	sc = gp->softc;
	if (sc == NULL && dr <= 0 && dw <= 0 && de <= 0)
		return (0);
	KASSERT(sc != NULL, ("Trying to access withered provider \"%s\".", pp->name));

	sc->sc_access_r += dr;
	sc->sc_access_w += dw;
	sc->sc_access_e += de;

	if (sc->sc_orphaned)
		return (0);

	return (g_access(cp, dr, dw, de));
}