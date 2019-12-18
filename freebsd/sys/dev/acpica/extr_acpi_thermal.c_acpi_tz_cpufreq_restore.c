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
struct acpi_tz_softc {scalar_t__ tz_cooling_updated; int /*<<< orphan*/  tz_cooling_saved_freq; int /*<<< orphan*/  tz_temperature; int /*<<< orphan*/  tz_dev; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_VPRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPUFREQ_PRIO_KERN ; 
 int CPUFREQ_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TZ_KELVTOC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_device_get_parent_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_tz_cpufreq_restore(struct acpi_tz_softc *sc)
{
    device_t dev;
    int error;

    if (!sc->tz_cooling_updated)
	return (0);
    if ((dev = devclass_get_device(devclass_find("cpufreq"), 0)) == NULL)
	return (ENXIO);
    ACPI_VPRINT(sc->tz_dev, acpi_device_get_parent_softc(sc->tz_dev),
	"temperature %d.%dC: resuming previous clock speed (%d MHz)\n",
	TZ_KELVTOC(sc->tz_temperature), sc->tz_cooling_saved_freq);
    error = CPUFREQ_SET(dev, NULL, CPUFREQ_PRIO_KERN);
    if (error == 0)
	sc->tz_cooling_updated = FALSE;
    return (error);
}