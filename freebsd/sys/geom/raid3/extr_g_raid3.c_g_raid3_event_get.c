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
struct g_raid3_softc {int /*<<< orphan*/  sc_events_mtx; int /*<<< orphan*/  sc_events; } ;
struct g_raid3_event {int dummy; } ;

/* Variables and functions */
 struct g_raid3_event* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct g_raid3_event *
g_raid3_event_get(struct g_raid3_softc *sc)
{
	struct g_raid3_event *ep;

	mtx_lock(&sc->sc_events_mtx);
	ep = TAILQ_FIRST(&sc->sc_events);
	mtx_unlock(&sc->sc_events_mtx);
	return (ep);
}