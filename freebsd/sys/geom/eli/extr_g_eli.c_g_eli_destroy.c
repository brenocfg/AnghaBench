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
struct g_geom {int /*<<< orphan*/  name; int /*<<< orphan*/ * softc; int /*<<< orphan*/  access; int /*<<< orphan*/  provider; } ;
struct g_eli_softc {int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_workers; int /*<<< orphan*/  sc_flags; struct g_geom* sc_geom; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  G_ELI_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  G_ELI_FLAG_DESTROY ; 
 int /*<<< orphan*/  G_ELI_FLAG_RW_DETACH ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct g_provider* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_ELI ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  bzero (struct g_eli_softc*,int) ; 
 int /*<<< orphan*/  free (struct g_eli_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_eli_access ; 
 int /*<<< orphan*/  g_eli_key_destroy (struct g_eli_softc*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_wither_geom_close (struct g_geom*,int) ; 
 int /*<<< orphan*/  g_wither_provider (struct g_provider*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct g_eli_softc*) ; 

int
g_eli_destroy(struct g_eli_softc *sc, boolean_t force)
{
	struct g_geom *gp;
	struct g_provider *pp;

	g_topology_assert();

	if (sc == NULL)
		return (ENXIO);

	gp = sc->sc_geom;
	pp = LIST_FIRST(&gp->provider);
	if (pp != NULL && (pp->acr != 0 || pp->acw != 0 || pp->ace != 0)) {
		if (force) {
			G_ELI_DEBUG(1, "Device %s is still open, so it "
			    "cannot be definitely removed.", pp->name);
			sc->sc_flags |= G_ELI_FLAG_RW_DETACH;
			gp->access = g_eli_access;
			g_wither_provider(pp, ENXIO);
			return (EBUSY);
		} else {
			G_ELI_DEBUG(1,
			    "Device %s is still open (r%dw%de%d).", pp->name,
			    pp->acr, pp->acw, pp->ace);
			return (EBUSY);
		}
	}

	mtx_lock(&sc->sc_queue_mtx);
	sc->sc_flags |= G_ELI_FLAG_DESTROY;
	wakeup(sc);
	while (!LIST_EMPTY(&sc->sc_workers)) {
		msleep(&sc->sc_workers, &sc->sc_queue_mtx, PRIBIO,
		    "geli:destroy", 0);
	}
	mtx_destroy(&sc->sc_queue_mtx);
	gp->softc = NULL;
	g_eli_key_destroy(sc);
	bzero(sc, sizeof(*sc));
	free(sc, M_ELI);

	if (pp == NULL || (pp->acr == 0 && pp->acw == 0 && pp->ace == 0))
		G_ELI_DEBUG(0, "Device %s destroyed.", gp->name);
	g_wither_geom_close(gp, ENXIO);

	return (0);
}