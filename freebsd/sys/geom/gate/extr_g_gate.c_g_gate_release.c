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
struct g_gate_softc {scalar_t__ sc_ref; int sc_flags; int /*<<< orphan*/  sc_name; } ;

/* Variables and functions */
 int G_GATE_FLAG_DESTROY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  g_gate_units_lock ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
g_gate_release(struct g_gate_softc *sc)
{

	g_topology_assert_not();
	mtx_lock(&g_gate_units_lock);
	sc->sc_ref--;
	KASSERT(sc->sc_ref >= 0, ("Negative sc_ref for %s.", sc->sc_name));
	if (sc->sc_ref == 0 && (sc->sc_flags & G_GATE_FLAG_DESTROY) != 0)
		wakeup(&sc->sc_ref);
	mtx_unlock(&g_gate_units_lock);
}