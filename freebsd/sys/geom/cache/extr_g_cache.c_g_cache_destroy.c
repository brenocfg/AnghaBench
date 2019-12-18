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
struct g_geom {int /*<<< orphan*/ * softc; int /*<<< orphan*/  name; int /*<<< orphan*/  provider; } ;
struct g_cache_softc {int /*<<< orphan*/  sc_zone; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_desclist; int /*<<< orphan*/  sc_callout; struct g_geom* sc_geom; } ;
struct g_cache_desc {int dummy; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int G_CACHE_BUCKETS ; 
 int /*<<< orphan*/  G_CACHE_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 void* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct g_cache_desc* LIST_NEXT (struct g_cache_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_next ; 
 int /*<<< orphan*/  g_cache_free (struct g_cache_softc*,struct g_cache_desc*) ; 
 int /*<<< orphan*/  g_free (struct g_cache_softc*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_wither_geom (struct g_geom*,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_cache_destroy(struct g_cache_softc *sc, boolean_t force)
{
	struct g_geom *gp;
	struct g_provider *pp;
	struct g_cache_desc *dp, *dp2;
	int i;

	g_topology_assert();
	if (sc == NULL)
		return (ENXIO);
	gp = sc->sc_geom;
	pp = LIST_FIRST(&gp->provider);
	if (pp != NULL && (pp->acr != 0 || pp->acw != 0 || pp->ace != 0)) {
		if (force) {
			G_CACHE_DEBUG(0, "Device %s is still open, so it "
			    "can't be definitely removed.", pp->name);
		} else {
			G_CACHE_DEBUG(1, "Device %s is still open (r%dw%de%d).",
			    pp->name, pp->acr, pp->acw, pp->ace);
			return (EBUSY);
		}
	} else {
		G_CACHE_DEBUG(0, "Device %s removed.", gp->name);
	}
	callout_drain(&sc->sc_callout);
	mtx_lock(&sc->sc_mtx);
	for (i = 0; i < G_CACHE_BUCKETS; i++) {
		dp = LIST_FIRST(&sc->sc_desclist[i]);
		while (dp != NULL) {
			dp2 = LIST_NEXT(dp, d_next);
			g_cache_free(sc, dp);
			dp = dp2;
		}
	}
	mtx_unlock(&sc->sc_mtx);
	mtx_destroy(&sc->sc_mtx);
	uma_zdestroy(sc->sc_zone);
	g_free(sc);
	gp->softc = NULL;
	g_wither_geom(gp, ENXIO);

	return (0);
}