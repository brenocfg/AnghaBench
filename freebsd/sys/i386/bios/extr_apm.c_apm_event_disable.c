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
struct apm_softc {scalar_t__ initialized; int /*<<< orphan*/ * event_thread; int /*<<< orphan*/  mtx; int /*<<< orphan*/  cv; scalar_t__ running; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  APM_DPRINT (char*) ; 
 int /*<<< orphan*/  PWAIT ; 
 struct apm_softc apm_softc ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
apm_event_disable(void)
{
	struct apm_softc *sc = &apm_softc;

	APM_DPRINT("called apm_event_disable()\n");

	if (sc == NULL || sc->initialized == 0)
		return;

	mtx_lock(&sc->mtx);
	sc->active = 0;
	while (sc->running) {
		cv_broadcast(&sc->cv);
		msleep(sc->event_thread, &sc->mtx, PWAIT, "apmdie", 0);
	}
	mtx_unlock(&sc->mtx);
	sc->event_thread = NULL;
	return;
}