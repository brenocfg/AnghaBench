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
struct g_mirror_softc {int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_done_mtx; int /*<<< orphan*/  sc_events_mtx; int /*<<< orphan*/  sc_queue_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MIRROR ; 
 int /*<<< orphan*/  free (struct g_mirror_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_mirror_free_device(struct g_mirror_softc *sc)
{

	g_topology_assert();

	mtx_destroy(&sc->sc_queue_mtx);
	mtx_destroy(&sc->sc_events_mtx);
	mtx_destroy(&sc->sc_done_mtx);
	sx_destroy(&sc->sc_lock);
	free(sc, M_MIRROR);
}