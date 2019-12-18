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
struct cyapa_softc {int /*<<< orphan*/  intr_hook; } ;
typedef  void* device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_POWER_MODE_IDLE ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cyapa_poll_thread ; 
 int /*<<< orphan*/  cyapa_set_power_mode (struct cyapa_softc*,int /*<<< orphan*/ ) ; 
 struct cyapa_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  kthread_add (int /*<<< orphan*/ ,struct cyapa_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
cyapa_start(void *xdev)
{
	struct cyapa_softc *sc;
	device_t dev = xdev;

	sc = device_get_softc(dev);

	config_intrhook_disestablish(&sc->intr_hook);

	/* Setup input event tracking */
	cyapa_set_power_mode(sc, CMD_POWER_MODE_IDLE);

	/* Start the polling thread */
	kthread_add(cyapa_poll_thread, sc, NULL, NULL,
	    0, 0, "cyapa-poll");
}