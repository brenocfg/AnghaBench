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
struct apm_softc {int running; int /*<<< orphan*/  mtx; int /*<<< orphan*/  cv; int /*<<< orphan*/  bios_busy; int /*<<< orphan*/  suspend_countdown; scalar_t__ suspends; int /*<<< orphan*/  standby_countdown; scalar_t__ standbys; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  apm_do_standby () ; 
 int /*<<< orphan*/  apm_do_suspend () ; 
 int /*<<< orphan*/  apm_lastreq_notify () ; 
 scalar_t__ apm_op_inprog ; 
 int /*<<< orphan*/  apm_processevent () ; 
 struct apm_softc apm_softc ; 
 int /*<<< orphan*/  cv_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int hz ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
apm_event_thread(void *arg)
{
	struct apm_softc *sc = &apm_softc;

	sc->running = 1;
	while (sc->active) {
		if (apm_op_inprog)
			apm_lastreq_notify();
		if (sc->standbys && sc->standby_countdown-- <= 0)
			apm_do_standby();
		if (sc->suspends && sc->suspend_countdown-- <= 0)
			apm_do_suspend();
		if (!sc->bios_busy)
			apm_processevent();
		mtx_lock(&sc->mtx);
		cv_timedwait(&sc->cv, &sc->mtx, 10 * hz / 9);
		mtx_unlock(&sc->mtx);
	}
	sc->running = 0;
	kproc_exit(0);
}