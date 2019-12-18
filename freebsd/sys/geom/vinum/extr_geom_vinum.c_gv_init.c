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
struct gv_softc {int /*<<< orphan*/  worker; int /*<<< orphan*/  bqueue_mtx; int /*<<< orphan*/  equeue_mtx; int /*<<< orphan*/  config_mtx; int /*<<< orphan*/  equeue; int /*<<< orphan*/  volumes; int /*<<< orphan*/  plexes; int /*<<< orphan*/  subdisks; int /*<<< orphan*/  drives; void* bqueue_up; void* bqueue_down; struct g_geom* geom; } ;
struct g_geom {struct gv_softc* softc; int /*<<< orphan*/  start; int /*<<< orphan*/  access; void* orphan; void* spoiled; } ;
struct g_class {int dummy; } ;
struct bio_queue_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_init (void*) ; 
 void* g_malloc (int,int) ; 
 struct g_geom* g_new_geomf (struct g_class*,char*) ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,struct g_class*) ; 
 int /*<<< orphan*/  gv_access ; 
 void* gv_orphan ; 
 int /*<<< orphan*/  gv_start ; 
 int /*<<< orphan*/  gv_worker ; 
 int /*<<< orphan*/  kproc_create (int /*<<< orphan*/ ,struct gv_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gv_init(struct g_class *mp)
{
	struct g_geom *gp;
	struct gv_softc *sc;

	g_trace(G_T_TOPOLOGY, "gv_init(%p)", mp);

	gp = g_new_geomf(mp, "VINUM");
	gp->spoiled = gv_orphan;
	gp->orphan = gv_orphan;
	gp->access = gv_access;
	gp->start = gv_start;
	gp->softc = g_malloc(sizeof(struct gv_softc), M_WAITOK | M_ZERO);
	sc = gp->softc;
	sc->geom = gp;
	sc->bqueue_down = g_malloc(sizeof(struct bio_queue_head),
	    M_WAITOK | M_ZERO);
	sc->bqueue_up = g_malloc(sizeof(struct bio_queue_head),
	    M_WAITOK | M_ZERO);
	bioq_init(sc->bqueue_down);
	bioq_init(sc->bqueue_up);
	LIST_INIT(&sc->drives);
	LIST_INIT(&sc->subdisks);
	LIST_INIT(&sc->plexes);
	LIST_INIT(&sc->volumes);
	TAILQ_INIT(&sc->equeue);
	mtx_init(&sc->config_mtx, "gv_config", NULL, MTX_DEF);
	mtx_init(&sc->equeue_mtx, "gv_equeue", NULL, MTX_DEF);
	mtx_init(&sc->bqueue_mtx, "gv_bqueue", NULL, MTX_DEF);
	kproc_create(gv_worker, sc, &sc->worker, 0, 0, "gv_worker");
}