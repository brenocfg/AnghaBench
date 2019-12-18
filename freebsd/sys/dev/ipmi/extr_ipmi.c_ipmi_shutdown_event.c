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
struct ipmi_softc {scalar_t__ ipmi_watchdog_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_SET_WD_ACTION_POWER_CYCLE ; 
 int /*<<< orphan*/  ipmi_reset_watchdog (struct ipmi_softc*) ; 
 int /*<<< orphan*/  ipmi_set_watchdog (struct ipmi_softc*,scalar_t__) ; 
 int /*<<< orphan*/  on ; 
 int wd_in_shutdown ; 
 scalar_t__ wd_shutdown_countdown ; 
 int /*<<< orphan*/  wd_timer_actions ; 

__attribute__((used)) static void
ipmi_shutdown_event(void *arg, unsigned int cmd, int *error)
{
	struct ipmi_softc *sc = arg;

	/* Ignore event if disabled. */
	if (!on)
		return;

	/*
	 * Positive wd_shutdown_countdown value will re-arm watchdog;
	 * Zero value in wd_shutdown_countdown will disable watchdog;
	 * Negative value in wd_shutdown_countdown will keep existing state;
	 *
	 * Revert to using a power cycle to ensure that the watchdog will
	 * do something useful here.  Having the watchdog send an NMI
	 * instead is useless during shutdown, and might be ignored if an
	 * NMI already triggered.
	 */

	wd_in_shutdown = true;
	if (wd_shutdown_countdown == 0) {
		/* disable watchdog */
		ipmi_set_watchdog(sc, 0);
		sc->ipmi_watchdog_active = 0;
	} else if (wd_shutdown_countdown > 0) {
		/* set desired action and time, and, reset watchdog */
		wd_timer_actions = IPMI_SET_WD_ACTION_POWER_CYCLE;
		ipmi_set_watchdog(sc, wd_shutdown_countdown);
		sc->ipmi_watchdog_active = wd_shutdown_countdown;
		ipmi_reset_watchdog(sc);
	}
}