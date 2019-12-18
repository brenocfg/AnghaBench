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
struct apm_softc {scalar_t__ initialized; scalar_t__ suspending; } ;

/* Variables and functions */
 size_t APM_HOOK_RESUME ; 
 int /*<<< orphan*/  DEVICE_RESUME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  apm_execute_hook (int /*<<< orphan*/ ) ; 
 struct apm_softc apm_softc ; 
 int /*<<< orphan*/ * hook ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_resume ; 
 int /*<<< orphan*/  root_bus ; 

__attribute__((used)) static void
apm_resume(void)
{
	struct apm_softc *sc = &apm_softc;

	if (sc == NULL || sc->initialized == 0 || sc->suspending == 0)
		return;

	sc->suspending = 0;
	apm_execute_hook(hook[APM_HOOK_RESUME]);
	mtx_lock(&Giant);
	DEVICE_RESUME(root_bus);
	mtx_unlock(&Giant);
	EVENTHANDLER_INVOKE(power_resume);
}