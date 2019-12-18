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
struct apm_softc {scalar_t__ initialized; int suspending; scalar_t__ suspend_countdown; scalar_t__ suspends; } ;

/* Variables and functions */
 size_t APM_HOOK_RESUME ; 
 size_t APM_HOOK_SUSPEND ; 
 int /*<<< orphan*/  DEVICE_RESUME (int /*<<< orphan*/ ) ; 
 int DEVICE_SUSPEND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  PMST_SUSPEND ; 
 int /*<<< orphan*/  apm_execute_hook (int /*<<< orphan*/ ) ; 
 scalar_t__ apm_op_inprog ; 
 int /*<<< orphan*/  apm_processevent () ; 
 struct apm_softc apm_softc ; 
 scalar_t__ apm_suspend_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hook ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_resume ; 
 int /*<<< orphan*/  power_suspend ; 
 int /*<<< orphan*/  root_bus ; 

__attribute__((used)) static void
apm_do_suspend(void)
{
	struct apm_softc *sc = &apm_softc;
	int error;

	if (sc == NULL || sc->initialized == 0)
		return;

	apm_op_inprog = 0;
	sc->suspends = sc->suspend_countdown = 0;

	EVENTHANDLER_INVOKE(power_suspend);

	/*
	 * Be sure to hold Giant across DEVICE_SUSPEND/RESUME since
	 * non-MPSAFE drivers need this.
	 */
	mtx_lock(&Giant);
	error = DEVICE_SUSPEND(root_bus);
	if (error)
		goto backout;

	apm_execute_hook(hook[APM_HOOK_SUSPEND]);
	if (apm_suspend_system(PMST_SUSPEND) == 0) {
		sc->suspending = 1;
		apm_processevent();
		mtx_unlock(&Giant);
		return;
	}

	/* Failure, 'resume' the system again */
	apm_execute_hook(hook[APM_HOOK_RESUME]);
	DEVICE_RESUME(root_bus);
backout:
	mtx_unlock(&Giant);
	EVENTHANDLER_INVOKE(power_resume);
}