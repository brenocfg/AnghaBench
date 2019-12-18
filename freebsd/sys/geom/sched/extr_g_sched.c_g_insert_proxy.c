#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct g_sched_softc {int /*<<< orphan*/  sc_flags; } ;
struct g_provider {scalar_t__ nstart; scalar_t__ nend; int /*<<< orphan*/  ace; int /*<<< orphan*/  acw; int /*<<< orphan*/  acr; struct g_geom* geom; int /*<<< orphan*/  index; int /*<<< orphan*/  private; } ;
struct g_geom {int /*<<< orphan*/ * start; int /*<<< orphan*/  provider; struct g_sched_softc* softc; } ;
struct g_consumer {int /*<<< orphan*/  ace; int /*<<< orphan*/  acw; int /*<<< orphan*/  acr; } ;
typedef  int /*<<< orphan*/  g_start_t ;
struct TYPE_2__ {scalar_t__ gs_npending; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  G_SCHED_PROXYING ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct g_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  g_cancel_event (struct g_provider*) ; 
 int /*<<< orphan*/  g_sched_flush_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_sched_start ; 
 int /*<<< orphan*/ * g_sched_temporary_start ; 
 int hz ; 
 TYPE_1__ me ; 
 int /*<<< orphan*/  provider ; 
 int ticks ; 
 int /*<<< orphan*/  tsleep (struct g_provider*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
g_insert_proxy(struct g_geom *gp, struct g_provider *newpp,
    struct g_geom *dstgp, struct g_provider *pp, struct g_consumer *cp)
{
	struct g_sched_softc *sc = gp->softc;
	g_start_t *saved_start, *flush = g_sched_start;
	int error = 0, endticks = ticks + hz;

	g_cancel_event(newpp);	/* prevent taste() */
	/* copy private fields */
	newpp->private = pp->private;
	newpp->index = pp->index;

	/* Queue all the early requests coming for us. */
	me.gs_npending = 0;
	saved_start = pp->geom->start;
	dstgp->start = g_sched_temporary_start;

	while (pp->nstart - pp->nend != me.gs_npending &&
	    endticks - ticks >= 0)
		tsleep(pp, PRIBIO, "-", hz/10);

	if (pp->nstart - pp->nend != me.gs_npending) {
		flush = saved_start;
		error = ETIMEDOUT;
		goto fail;
	}

	/* link pp to this geom */
	LIST_REMOVE(pp, provider);
	pp->geom = gp;
	LIST_INSERT_HEAD(&gp->provider, pp, provider);

	/*
	 * replicate the counts from the parent in the
	 * new provider and consumer nodes
	 */
	cp->acr = newpp->acr = pp->acr;
	cp->acw = newpp->acw = pp->acw;
	cp->ace = newpp->ace = pp->ace;
	sc->sc_flags |= G_SCHED_PROXYING;

fail:
	dstgp->start = saved_start;

	g_sched_flush_pending(flush);

	return (error);
}