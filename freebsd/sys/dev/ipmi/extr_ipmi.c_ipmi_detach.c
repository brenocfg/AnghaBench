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
struct ipmi_softc {int ipmi_detaching; int /*<<< orphan*/  ipmi_requests_lock; int /*<<< orphan*/  ipmi_io_lock; scalar_t__ ipmi_irq; int /*<<< orphan*/  ipmi_irq_res; scalar_t__ ipmi_kthread; int /*<<< orphan*/  ipmi_request_added; scalar_t__ ipmi_power_cycle_tag; scalar_t__ ipmi_watchdog_tag; scalar_t__ ipmi_shutdown_tag; scalar_t__ ipmi_cdev; scalar_t__ ipmi_opened; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IPMI_LOCK (struct ipmi_softc*) ; 
 int /*<<< orphan*/  IPMI_UNLOCK (struct ipmi_softc*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (scalar_t__) ; 
 struct ipmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_release_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_set_watchdog (struct ipmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown_final ; 
 int /*<<< orphan*/  shutdown_pre_sync ; 
 int /*<<< orphan*/  watchdog_list ; 

int
ipmi_detach(device_t dev)
{
	struct ipmi_softc *sc;

	sc = device_get_softc(dev);

	/* Fail if there are any open handles. */
	IPMI_LOCK(sc);
	if (sc->ipmi_opened) {
		IPMI_UNLOCK(sc);
		return (EBUSY);
	}
	IPMI_UNLOCK(sc);
	if (sc->ipmi_cdev)
		destroy_dev(sc->ipmi_cdev);

	/* Detach from watchdog handling and turn off watchdog. */
	if (sc->ipmi_shutdown_tag)
		EVENTHANDLER_DEREGISTER(shutdown_pre_sync,
		sc->ipmi_shutdown_tag);
	if (sc->ipmi_watchdog_tag) {
		EVENTHANDLER_DEREGISTER(watchdog_list, sc->ipmi_watchdog_tag);
		ipmi_set_watchdog(sc, 0);
	}

	/* Detach from shutdown handling for power cycle reboot */
	if (sc->ipmi_power_cycle_tag)
		EVENTHANDLER_DEREGISTER(shutdown_final, sc->ipmi_power_cycle_tag);

	/* XXX: should use shutdown callout I think. */
	/* If the backend uses a kthread, shut it down. */
	IPMI_LOCK(sc);
	sc->ipmi_detaching = 1;
	if (sc->ipmi_kthread) {
		cv_broadcast(&sc->ipmi_request_added);
		msleep(sc->ipmi_kthread, &sc->ipmi_requests_lock, 0,
		    "ipmi_wait", 0);
	}
	IPMI_UNLOCK(sc);
	if (sc->ipmi_irq)
		bus_teardown_intr(dev, sc->ipmi_irq_res, sc->ipmi_irq);

	ipmi_release_resources(dev);
	mtx_destroy(&sc->ipmi_io_lock);
	mtx_destroy(&sc->ipmi_requests_lock);
	return (0);
}