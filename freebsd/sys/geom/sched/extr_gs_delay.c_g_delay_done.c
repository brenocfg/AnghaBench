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
struct g_delay_softc {int /*<<< orphan*/  sc_geom; int /*<<< orphan*/  sc_in_flight; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_sched_dispatch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_delay_done(void *data, struct bio *bp)
{
	struct g_delay_softc *sc = data;

	sc->sc_in_flight--;

	g_sched_dispatch(sc->sc_geom);
}