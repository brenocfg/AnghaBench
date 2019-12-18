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
struct g_sched_softc {int /*<<< orphan*/  sc_mtx; } ;
struct g_geom {struct g_sched_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 

void
g_sched_lock(struct g_geom *gp)
{
	struct g_sched_softc *sc = gp->softc;

	mtx_lock(&sc->sc_mtx);
}