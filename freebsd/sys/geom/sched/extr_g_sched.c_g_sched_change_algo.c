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
typedef  int /*<<< orphan*/  u_long ;
struct gctl_req {int dummy; } ;
struct g_sched_softc {int /*<<< orphan*/  sc_mask; struct g_hash* sc_hash; void* sc_data; struct g_gsched* sc_gsched; } ;
struct g_provider {struct g_geom* geom; } ;
struct g_hash {int dummy; } ;
struct g_gsched {int /*<<< orphan*/  (* gs_fini ) (void*) ;scalar_t__ gs_priv_size; void* (* gs_init ) (struct g_geom*) ;} ;
struct g_geom {struct g_sched_softc* softc; } ;
struct g_class {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HASH_WAITOK ; 
 int /*<<< orphan*/  g_gsched_ref (struct g_gsched*) ; 
 int /*<<< orphan*/  g_sched_hash_fini (struct g_geom*,struct g_hash*,int /*<<< orphan*/ ,struct g_gsched*,void*) ; 
 struct g_hash* g_sched_hash_init (struct g_gsched*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_sched_lock (struct g_geom*) ; 
 int g_sched_remove_locked (struct g_geom*,struct g_gsched*) ; 
 int /*<<< orphan*/  g_sched_unlock (struct g_geom*) ; 
 void* stub1 (struct g_geom*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 

__attribute__((used)) static int
g_sched_change_algo(struct gctl_req *req, struct g_class *mp,
    struct g_provider *pp, struct g_gsched *gsp)
{
	struct g_sched_softc *sc;
	struct g_geom *gp;
	struct g_hash *newh;
	void *data;
	u_long mask;
	int error = 0;

	gp = pp->geom;
	sc = gp->softc;

	data = gsp->gs_init(gp);
	if (data == NULL)
		return (ENOMEM);

	newh = g_sched_hash_init(gsp, &mask, HASH_WAITOK);
	if (gsp->gs_priv_size && !newh) {
		error = ENOMEM;
		goto fail;
	}

	g_sched_lock(gp);
	if (sc->sc_gsched) {	/* can be NULL in some cases */
		error = g_sched_remove_locked(gp, sc->sc_gsched);
		if (error)
			goto fail;
	}

	g_gsched_ref(gsp);
	sc->sc_gsched = gsp;
	sc->sc_data = data;
	sc->sc_hash = newh;
	sc->sc_mask = mask;

	g_sched_unlock(gp);

	return (0);

fail:
	if (newh)
		g_sched_hash_fini(gp, newh, mask, gsp, data);

	if (data)
		gsp->gs_fini(data);

	g_sched_unlock(gp);

	return (error);
}