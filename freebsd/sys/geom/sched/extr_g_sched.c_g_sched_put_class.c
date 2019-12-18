#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_sched_softc {int /*<<< orphan*/  sc_data; TYPE_1__* sc_gsched; } ;
struct g_sched_class {scalar_t__ gsc_refs; scalar_t__ gsc_expire; } ;
struct g_geom {struct g_sched_softc* softc; } ;
struct TYPE_4__ {int gs_expire_secs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* gs_fini_class ) (int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct g_sched_class*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GEOM_SCHED ; 
 int /*<<< orphan*/  free (struct g_sched_class*,int /*<<< orphan*/ ) ; 
 struct g_sched_class* g_sched_priv2class (void*) ; 
 int /*<<< orphan*/  gsc_clist ; 
 int hz ; 
 TYPE_2__ me ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ ticks ; 

void
g_sched_put_class(struct g_geom *gp, void *priv)
{
	struct g_sched_class *gsc;
	struct g_sched_softc *sc;

	gsc = g_sched_priv2class(priv);
	gsc->gsc_expire = ticks + me.gs_expire_secs * hz;

	if (--gsc->gsc_refs > 0)
		return;

	sc = gp->softc;
	sc->sc_gsched->gs_fini_class(sc->sc_data, priv);

	LIST_REMOVE(gsc, gsc_clist);
	free(gsc, M_GEOM_SCHED);
}