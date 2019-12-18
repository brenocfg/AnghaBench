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
struct tegra_rtc_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int RD4 (struct tegra_rtc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_BUSY ; 
 int RTC_BUSY_STATUS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
tegra_rtc_wait(struct tegra_rtc_softc *sc)
{
	int timeout;

	for (timeout = 500; timeout >0; timeout--) {
		if ((RD4(sc, RTC_BUSY) & RTC_BUSY_STATUS) == 0)
			break;
		DELAY(1);
	}
	if (timeout <= 0)
		device_printf(sc->dev, "Device busy timeouted\n");

}