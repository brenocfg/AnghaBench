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
struct g_provider {scalar_t__ acr; scalar_t__ acw; scalar_t__ ace; int /*<<< orphan*/  name; } ;
struct g_mountver_softc {struct g_mountver_softc* sc_provider_name; } ;
struct g_geom {struct g_mountver_softc* softc; int /*<<< orphan*/  name; int /*<<< orphan*/  provider; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  G_MOUNTVER_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 struct g_provider* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (struct g_mountver_softc*) ; 
 int /*<<< orphan*/  g_mountver_discard_queued (struct g_geom*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_wither_geom (struct g_geom*,int) ; 
 int /*<<< orphan*/  g_wither_provider (struct g_provider*,int) ; 

__attribute__((used)) static int
g_mountver_destroy(struct g_geom *gp, boolean_t force)
{
	struct g_mountver_softc *sc;
	struct g_provider *pp;

	g_topology_assert();
	if (gp->softc == NULL)
		return (ENXIO);
	sc = gp->softc;
	pp = LIST_FIRST(&gp->provider);
	if (pp != NULL && (pp->acr != 0 || pp->acw != 0 || pp->ace != 0)) {
		if (force) {
			G_MOUNTVER_DEBUG(0, "Device %s is still open, so it "
			    "can't be definitely removed.", pp->name);
		} else {
			G_MOUNTVER_DEBUG(1, "Device %s is still open (r%dw%de%d).",
			    pp->name, pp->acr, pp->acw, pp->ace);
			return (EBUSY);
		}
	} else {
		G_MOUNTVER_DEBUG(0, "Device %s removed.", gp->name);
	}
	if (pp != NULL)
		g_wither_provider(pp, ENXIO);
	g_mountver_discard_queued(gp);
	g_free(sc->sc_provider_name);
	g_free(gp->softc);
	gp->softc = NULL;
	g_wither_geom(gp, ENXIO);

	return (0);
}