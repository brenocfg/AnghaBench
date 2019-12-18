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
struct g_spa {int spa_g_proc_run; int /*<<< orphan*/  spa_g_stat_mtx; int /*<<< orphan*/  spa_g_mtx; int /*<<< orphan*/ * spa_g_devstat; int /*<<< orphan*/ * spa_p; int /*<<< orphan*/  spa_g_queue; int /*<<< orphan*/  spa_g_proc_exiting; } ;
struct g_geom {struct g_spa* softc; } ;
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  M_NVDIMM ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  devstat_remove_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct g_spa*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  g_wither_geom (struct g_geom*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvdimm_spa_g_destroy_geom(struct gctl_req *req, struct g_class *cp,
    struct g_geom *gp)
{
	struct g_spa *sc;

	sc = gp->softc;
	mtx_lock(&sc->spa_g_mtx);
	sc->spa_g_proc_run = false;
	wakeup(&sc->spa_g_queue);
	while (!sc->spa_g_proc_exiting)
		msleep(&sc->spa_g_queue, &sc->spa_g_mtx, PRIBIO, "spa_e", 0);
	mtx_unlock(&sc->spa_g_mtx);
	g_topology_assert();
	g_wither_geom(gp, ENXIO);
	sc->spa_p = NULL;
	if (sc->spa_g_devstat != NULL) {
		devstat_remove_entry(sc->spa_g_devstat);
		sc->spa_g_devstat = NULL;
	}
	mtx_destroy(&sc->spa_g_mtx);
	mtx_destroy(&sc->spa_g_stat_mtx);
	free(sc, M_NVDIMM);
	return (0);
}