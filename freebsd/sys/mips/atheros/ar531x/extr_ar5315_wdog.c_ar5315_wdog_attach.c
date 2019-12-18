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
struct ar5315_wdog_softc {int /*<<< orphan*/  dev; scalar_t__ debug; scalar_t__ armed; scalar_t__ reboot_from_watchdog; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR5315_WDOG_CTL_IGNORE ; 
 int /*<<< orphan*/  ATH_WRITE_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ar5315_wdog_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5315_wdog_sysctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5315_wdog_watchdog_fn ; 
 int /*<<< orphan*/  ar531x_wdog_ctl () ; 
 struct ar5315_wdog_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_list ; 

__attribute__((used)) static int
ar5315_wdog_attach(device_t dev)
{
	struct ar5315_wdog_softc *sc = device_get_softc(dev);
	
	/* Initialise */
	sc->reboot_from_watchdog = 0;
	sc->armed = 0;
	sc->debug = 0;
	ATH_WRITE_REG(ar531x_wdog_ctl(), AR5315_WDOG_CTL_IGNORE);

	sc->dev = dev;
	EVENTHANDLER_REGISTER(watchdog_list, ar5315_wdog_watchdog_fn, sc, 0);
	ar5315_wdog_sysctl(dev);

	return (0);
}