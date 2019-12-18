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
struct wb_softc {scalar_t__ ev_tag; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,scalar_t__) ; 
 struct wb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_list ; 
 int /*<<< orphan*/  wb_set_watchdog (struct wb_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wb_detach(device_t dev)
{
	struct wb_softc *sc;

	sc = device_get_softc(dev);

	/* Unregister and stop the watchdog if running. */
	if (sc->ev_tag)
		EVENTHANDLER_DEREGISTER(watchdog_list, sc->ev_tag);
	wb_set_watchdog(sc, 0);

	/* Bus subroutines take care of sysctls already. */

	return (0);
}