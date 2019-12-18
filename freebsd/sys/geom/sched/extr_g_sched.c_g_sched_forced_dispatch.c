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
struct g_sched_softc {int /*<<< orphan*/  sc_data; int /*<<< orphan*/  sc_mtx; struct g_gsched* sc_gsched; } ;
struct g_gsched {struct bio* (* gs_next ) (int /*<<< orphan*/ ,int) ;} ;
struct g_geom {int /*<<< orphan*/  consumer; struct g_sched_softc* softc; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_owned (int /*<<< orphan*/ *) ; 
 struct bio* stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
g_sched_forced_dispatch(struct g_geom *gp)
{
	struct g_sched_softc *sc = gp->softc;
	struct g_gsched *gsp = sc->sc_gsched;
	struct bio *bp;

	KASSERT(mtx_owned(&sc->sc_mtx),
	    ("sc_mtx not owned during forced dispatch"));

	while ((bp = gsp->gs_next(sc->sc_data, 1)) != NULL)
		g_io_request(bp, LIST_FIRST(&gp->consumer));
}