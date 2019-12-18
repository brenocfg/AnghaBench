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
struct ifnet {int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;
struct dc_softc {scalar_t__ dc_wdog_timer; int /*<<< orphan*/  dc_dev; struct ifnet* dc_ifp; int /*<<< orphan*/  dc_wdog_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOCK_ASSERT (struct dc_softc*) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct dc_softc*) ; 
 int /*<<< orphan*/  dc_init_locked (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dc_watchdog(void *xsc)
{
	struct dc_softc *sc = xsc;
	struct ifnet *ifp;

	DC_LOCK_ASSERT(sc);

	if (sc->dc_wdog_timer == 0 || --sc->dc_wdog_timer != 0) {
		callout_reset(&sc->dc_wdog_ch, hz, dc_watchdog, sc);
		return;
	}

	ifp = sc->dc_ifp;
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	device_printf(sc->dc_dev, "watchdog timeout\n");

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	dc_init_locked(sc);

	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		dc_start_locked(ifp);
}