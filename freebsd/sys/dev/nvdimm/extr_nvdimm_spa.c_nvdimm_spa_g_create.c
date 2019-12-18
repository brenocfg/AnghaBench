#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvdimm_spa_dev {int /*<<< orphan*/  spa_len; } ;
struct g_spa {int spa_g_proc_run; int spa_g_proc_exiting; int /*<<< orphan*/  spa_g_devstat; TYPE_1__* spa_p; int /*<<< orphan*/  spa_g_stat_mtx; int /*<<< orphan*/  spa_g_mtx; int /*<<< orphan*/  spa_g_proc; int /*<<< orphan*/  spa_g_queue; struct nvdimm_spa_dev* dev; } ;
struct g_geom {struct g_spa* softc; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  sectorsize; int /*<<< orphan*/  mediasize; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVSTAT_ALL_SUPPORTED ; 
 int /*<<< orphan*/  DEVSTAT_PRIORITY_MAX ; 
 int /*<<< orphan*/  DEVSTAT_TYPE_DIRECT ; 
 int /*<<< orphan*/  DEV_BSIZE ; 
 int G_PF_ACCEPT_UNMAPPED ; 
 int G_PF_DIRECT_RECEIVE ; 
 int G_PF_DIRECT_SEND ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NVDIMM ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devstat_new_entry (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct g_spa*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error_provider (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct g_geom* g_new_geomf (int /*<<< orphan*/ *,char*,char const*) ; 
 TYPE_1__* g_new_providerf (struct g_geom*,char*,char const*) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int kproc_create (int /*<<< orphan*/ ,struct g_spa*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct g_spa* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvdimm_spa_g_class ; 
 int /*<<< orphan*/  nvdimm_spa_g_thread ; 
 int /*<<< orphan*/  printf (char*,char const*,int) ; 

__attribute__((used)) static struct g_geom *
nvdimm_spa_g_create(struct nvdimm_spa_dev *dev, const char *name)
{
	struct g_geom *gp;
	struct g_spa *sc;
	int error;

	gp = NULL;
	sc = malloc(sizeof(struct g_spa), M_NVDIMM, M_WAITOK | M_ZERO);
	sc->dev = dev;
	bioq_init(&sc->spa_g_queue);
	mtx_init(&sc->spa_g_mtx, "spag", NULL, MTX_DEF);
	mtx_init(&sc->spa_g_stat_mtx, "spagst", NULL, MTX_DEF);
	sc->spa_g_proc_run = true;
	sc->spa_g_proc_exiting = false;
	error = kproc_create(nvdimm_spa_g_thread, sc, &sc->spa_g_proc, 0, 0,
	    "g_spa");
	if (error != 0) {
		mtx_destroy(&sc->spa_g_mtx);
		mtx_destroy(&sc->spa_g_stat_mtx);
		free(sc, M_NVDIMM);
		printf("NVDIMM %s cannot create geom worker, error %d\n", name,
		    error);
	} else {
		g_topology_lock();
		gp = g_new_geomf(&nvdimm_spa_g_class, "%s", name);
		gp->softc = sc;
		sc->spa_p = g_new_providerf(gp, "%s", name);
		sc->spa_p->mediasize = dev->spa_len;
		sc->spa_p->sectorsize = DEV_BSIZE;
		sc->spa_p->flags |= G_PF_DIRECT_SEND | G_PF_DIRECT_RECEIVE |
		    G_PF_ACCEPT_UNMAPPED;
		g_error_provider(sc->spa_p, 0);
		sc->spa_g_devstat = devstat_new_entry("spa", -1, DEV_BSIZE,
		    DEVSTAT_ALL_SUPPORTED, DEVSTAT_TYPE_DIRECT,
		    DEVSTAT_PRIORITY_MAX);
		g_topology_unlock();
	}
	return (gp);
}