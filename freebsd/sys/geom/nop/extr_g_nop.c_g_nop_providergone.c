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
struct g_provider {struct g_geom* geom; } ;
struct g_nop_softc {int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_physpath; int /*<<< orphan*/  sc_head_delay; } ;
struct g_geom {struct g_nop_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_GEOM ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (struct g_nop_softc*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_nop_providergone(struct g_provider *pp)
{
	struct g_geom *gp = pp->geom;
	struct g_nop_softc *sc = gp->softc;

	KASSERT(TAILQ_EMPTY(&sc->sc_head_delay),
	    ("delayed request list is not empty"));

	gp->softc = NULL;
	free(sc->sc_physpath, M_GEOM);
	mtx_destroy(&sc->sc_lock);
	g_free(sc);
}