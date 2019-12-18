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
struct g_delay_softc {int /*<<< orphan*/  sc_wait; int /*<<< orphan*/  sc_geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct g_delay_softc*) ; 
 int /*<<< orphan*/  g_sched_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_sched_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_sched_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_delay_timeout(void *data)
{
	struct g_delay_softc *sc = data;
	
	g_sched_lock(sc->sc_geom);
	g_sched_dispatch(sc->sc_geom);
	g_sched_unlock(sc->sc_geom);
	callout_reset(&sc->sc_wait, 1, g_delay_timeout, sc);
}