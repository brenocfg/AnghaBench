#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tc1; int tc2; int tsp; int psv; } ;
struct acpi_tz_softc {TYPE_1__ tz_zone; } ;

/* Variables and functions */

__attribute__((used)) static int
acpi_tz_cooling_is_available(struct acpi_tz_softc *sc)
{
    return (sc->tz_zone.tc1 != -1 && sc->tz_zone.tc2 != -1 &&
	sc->tz_zone.tsp != -1 && sc->tz_zone.tsp != 0 &&
	sc->tz_zone.psv != -1);
}