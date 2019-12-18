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
struct acpi_tz_softc {int tz_insane_tmp_notified; int /*<<< orphan*/  tz_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TZ_KELVTOC (int) ; 
 int TZ_ZEROC ; 
 char* acpi_tz_tmp_name ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_tz_sanity(struct acpi_tz_softc *sc, int *val, char *what)
{
    if (*val != -1 && (*val < TZ_ZEROC || *val > TZ_ZEROC + 2000)) {
	/*
	 * If the value we are checking is _TMP, warn the user only
	 * once. This avoids spamming messages if, for instance, the
	 * sensor is broken and always returns an invalid temperature.
	 *
	 * This is only done for _TMP; other values always emit a
	 * warning.
	 */
	if (what != acpi_tz_tmp_name || !sc->tz_insane_tmp_notified) {
	    device_printf(sc->tz_dev, "%s value is absurd, ignored (%d.%dC)\n",
			  what, TZ_KELVTOC(*val));

	    /* Don't warn the user again if the read value doesn't improve. */
	    if (what == acpi_tz_tmp_name)
		sc->tz_insane_tmp_notified = 1;
	}
	*val = -1;
	return;
    }

    /* This value is correct. Warn if it's incorrect again. */
    if (what == acpi_tz_tmp_name)
	sc->tz_insane_tmp_notified = 0;
}