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
struct as3722_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int AS3722_RTC_ALARM_WAKEUP_EN ; 
 int AS3722_RTC_AM_PM_MODE ; 
 int /*<<< orphan*/  AS3722_RTC_CONTROL ; 
 int AS3722_RTC_ON ; 
 int ENXIO ; 
 int RM1 (struct as3722_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clock_register (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

int
as3722_rtc_attach(struct as3722_softc *sc, phandle_t node)
{
	int rv;

	/* Enable RTC, set 24 hours mode  and alarms */
	rv = RM1(sc, AS3722_RTC_CONTROL,
	    AS3722_RTC_ON | AS3722_RTC_ALARM_WAKEUP_EN | AS3722_RTC_AM_PM_MODE,
	    AS3722_RTC_ON | AS3722_RTC_ALARM_WAKEUP_EN);
	if (rv < 0) {
		device_printf(sc->dev, "Failed to initialize RTC controller\n");
		return (ENXIO);
	}
	clock_register(sc->dev, 1000000);

	return (0);
}