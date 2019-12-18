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
struct ar71xx_wdog_softc {int reboot_from_watchdog; int /*<<< orphan*/  dev; scalar_t__ debug; scalar_t__ armed; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_RST_WDOG_CONTROL ; 
 int ATH_READ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_WRITE_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ar71xx_wdog_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RST_WDOG_ACTION_NOACTION ; 
 int RST_WDOG_LAST ; 
 int /*<<< orphan*/  ar71xx_wdog_sysctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar71xx_wdog_watchdog_fn ; 
 struct ar71xx_wdog_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  watchdog_list ; 

__attribute__((used)) static int
ar71xx_wdog_attach(device_t dev)
{
	struct ar71xx_wdog_softc *sc = device_get_softc(dev);
	
	/* Initialise */
	sc->reboot_from_watchdog = 0;
	sc->armed = 0;
	sc->debug = 0;

	if (ATH_READ_REG(AR71XX_RST_WDOG_CONTROL) & RST_WDOG_LAST) {
		device_printf (dev, 
		    "Previous reset was due to watchdog timeout\n");
		sc->reboot_from_watchdog = 1;
	}

	ATH_WRITE_REG(AR71XX_RST_WDOG_CONTROL, RST_WDOG_ACTION_NOACTION);

	sc->dev = dev;
	EVENTHANDLER_REGISTER(watchdog_list, ar71xx_wdog_watchdog_fn, sc, 0);
	ar71xx_wdog_sysctl(dev);

	return (0);
}