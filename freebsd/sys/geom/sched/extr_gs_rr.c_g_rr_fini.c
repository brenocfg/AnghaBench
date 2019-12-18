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
struct g_rr_softc {int /*<<< orphan*/  sc_rr_tailq; int /*<<< orphan*/ * sc_active; int /*<<< orphan*/  sc_wait; } ;
struct TYPE_2__ {int /*<<< orphan*/  units; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_rr_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_GEOM_SCHED ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct g_rr_softc*,int /*<<< orphan*/ ) ; 
 TYPE_1__ me ; 
 int /*<<< orphan*/  sc_next ; 

__attribute__((used)) static void
g_rr_fini(void *data)
{
	struct g_rr_softc *sc = data;

	callout_drain(&sc->sc_wait);
	KASSERT(sc->sc_active == NULL, ("still a queue under service"));
	KASSERT(TAILQ_EMPTY(&sc->sc_rr_tailq), ("still scheduled queues"));

	LIST_REMOVE(sc, sc_next);
	me.units--;
	free(sc, M_GEOM_SCHED);
}