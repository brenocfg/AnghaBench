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
struct hwpstate_softc {int cfnum; struct hwpstate_setting* hwpstate_settings; } ;
struct hwpstate_setting {int pstate_id; int /*<<< orphan*/  lat; int /*<<< orphan*/  power; int /*<<< orphan*/  volts; int /*<<< orphan*/  freq; } ;
struct cf_setting {int* spec; int /*<<< orphan*/  lat; int /*<<< orphan*/  power; int /*<<< orphan*/  volts; int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CPUFREQ_DRV_SETTINGS (int /*<<< orphan*/ ,struct cf_setting*,int*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  HWPSTATE_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int MAX_SETTINGS ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 struct hwpstate_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cf_setting*,int /*<<< orphan*/ ) ; 
 struct cf_setting* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hwpstate_get_info_from_acpi_perf(device_t dev, device_t perf_dev)
{
	struct hwpstate_softc *sc;
	struct cf_setting *perf_set;
	struct hwpstate_setting *hwpstate_set;
	int count, error, i;

	perf_set = malloc(MAX_SETTINGS * sizeof(*perf_set), M_TEMP, M_NOWAIT);
	if (perf_set == NULL) {
		HWPSTATE_DEBUG(dev, "nomem\n");
		return (ENOMEM);
	}
	/*
	 * Fetch settings from acpi_perf.
	 * Now it is attached, and has info only flag.
	 */
	count = MAX_SETTINGS;
	error = CPUFREQ_DRV_SETTINGS(perf_dev, perf_set, &count);
	if (error) {
		HWPSTATE_DEBUG(dev, "error: CPUFREQ_DRV_SETTINGS.\n");
		goto out;
	}
	sc = device_get_softc(dev);
	sc->cfnum = count;
	hwpstate_set = sc->hwpstate_settings;
	for (i = 0; i < count; i++) {
		if (i == perf_set[i].spec[0]) {
			hwpstate_set[i].pstate_id = i;
			hwpstate_set[i].freq = perf_set[i].freq;
			hwpstate_set[i].volts = perf_set[i].volts;
			hwpstate_set[i].power = perf_set[i].power;
			hwpstate_set[i].lat = perf_set[i].lat;
		} else {
			HWPSTATE_DEBUG(dev, "ACPI _PSS object mismatch.\n");
			error = ENXIO;
			goto out;
		}
	}
out:
	if (perf_set)
		free(perf_set, M_TEMP);
	return (error);
}