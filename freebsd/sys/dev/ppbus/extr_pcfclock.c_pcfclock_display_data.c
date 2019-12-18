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
struct pcfclock_data {int /*<<< orphan*/  dev; } ;
struct cdev {struct pcfclock_data* si_drv1; } ;

/* Variables and functions */
 int NR (char*,int) ; 
 scalar_t__ PCFCLOCK_BATTERY_STATUS_LOW (char*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
pcfclock_display_data(struct cdev *dev, char buf[18])
{
	struct pcfclock_data *sc = dev->si_drv1;
#ifdef PCFCLOCK_VERBOSE
	int year;

	year = NR(buf, 14);
	if (year < 70)
		year += 100;

	device_printf(sc->dev, "%02d.%02d.%4d %02d:%02d:%02d, "
			"battery status: %s\n",
			NR(buf, 10), NR(buf, 12), 1900 + year,
			NR(buf, 6), NR(buf, 4), NR(buf, 2),
			PCFCLOCK_BATTERY_STATUS_LOW(buf) ? "LOW" : "ok");
#else
	if (PCFCLOCK_BATTERY_STATUS_LOW(buf))
		device_printf(sc->dev, "BATTERY STATUS LOW ON\n");
#endif
}