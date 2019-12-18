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
struct apm_softc {scalar_t__ initialized; int active; int /*<<< orphan*/  event_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  APM_DPRINT (char*) ; 
 int /*<<< orphan*/  apm_event_thread ; 
 struct apm_softc apm_softc ; 
 scalar_t__ kproc_create (int /*<<< orphan*/ ,struct apm_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
apm_event_enable(void)
{
	struct apm_softc *sc = &apm_softc;

	APM_DPRINT("called apm_event_enable()\n");

	if (sc == NULL || sc->initialized == 0)
		return;

	/* Start the thread */
	sc->active = 1;
	if (kproc_create(apm_event_thread, sc, &sc->event_thread, 0, 0,
	    "apm worker"))
		panic("Cannot create apm worker thread");

	return;
}