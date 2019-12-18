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
struct TYPE_2__ {int freq; } ;
struct cf_level {TYPE_1__ total_set; } ;
struct acpi_tz_softc {int tz_cooling_saved_freq; scalar_t__ tz_cooling_updated; int /*<<< orphan*/  tz_temperature; int /*<<< orphan*/  tz_dev; void* tz_cooling_active; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_VPRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int,int) ; 
 int CPUFREQ_GET (int /*<<< orphan*/ *,struct cf_level*) ; 
 int CPUFREQ_LEVELS (int /*<<< orphan*/ *,struct cf_level*,int*) ; 
 int CPUFREQ_MAX_LEVELS ; 
 int /*<<< orphan*/  CPUFREQ_PRIO_KERN ; 
 int CPUFREQ_SET (int /*<<< orphan*/ *,struct cf_level*,int /*<<< orphan*/ ) ; 
 int E2BIG ; 
 int ENOMEM ; 
 int ENXIO ; 
 void* FALSE ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TZ_KELVTOC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_device_get_parent_softc (int /*<<< orphan*/ ) ; 
 int acpi_tz_cpufreq_restore (struct acpi_tz_softc*) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cf_level*,int /*<<< orphan*/ ) ; 
 struct cf_level* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
acpi_tz_cpufreq_update(struct acpi_tz_softc *sc, int req)
{
    device_t dev;
    struct cf_level *levels;
    int num_levels, error, freq, desired_freq, perf, i;

    levels = malloc(CPUFREQ_MAX_LEVELS * sizeof(*levels), M_TEMP, M_NOWAIT);
    if (levels == NULL)
	return (ENOMEM);

    /*
     * Find the main device, cpufreq0.  We don't yet support independent
     * CPU frequency control on SMP.
     */
    if ((dev = devclass_get_device(devclass_find("cpufreq"), 0)) == NULL) {
	error = ENXIO;
	goto out;
    }

    /* Get the current frequency. */
    error = CPUFREQ_GET(dev, &levels[0]);
    if (error)
	goto out;
    freq = levels[0].total_set.freq;

    /* Get the current available frequency levels. */
    num_levels = CPUFREQ_MAX_LEVELS;
    error = CPUFREQ_LEVELS(dev, levels, &num_levels);
    if (error) {
	if (error == E2BIG)
	    printf("cpufreq: need to increase CPUFREQ_MAX_LEVELS\n");
	goto out;
    }

    /* Calculate the desired frequency as a percent of the max frequency. */
    perf = 100 * freq / levels[0].total_set.freq - req;
    if (perf < 0)
	perf = 0;
    else if (perf > 100)
	perf = 100;
    desired_freq = levels[0].total_set.freq * perf / 100;

    if (desired_freq < freq) {
	/* Find the closest available frequency, rounding down. */
	for (i = 0; i < num_levels; i++)
	    if (levels[i].total_set.freq <= desired_freq)
		break;

	/* If we didn't find a relevant setting, use the lowest. */
	if (i == num_levels)
	    i--;
    } else {
	/* If we didn't decrease frequency yet, don't increase it. */
	if (!sc->tz_cooling_updated) {
	    sc->tz_cooling_active = FALSE;
	    goto out;
	}

	/* Use saved cpu frequency as maximum value. */
	if (desired_freq > sc->tz_cooling_saved_freq)
	    desired_freq = sc->tz_cooling_saved_freq;

	/* Find the closest available frequency, rounding up. */
	for (i = num_levels - 1; i >= 0; i--)
	    if (levels[i].total_set.freq >= desired_freq)
		break;

	/* If we didn't find a relevant setting, use the highest. */
	if (i == -1)
	    i++;

	/* If we're going to the highest frequency, restore the old setting. */
	if (i == 0 || desired_freq == sc->tz_cooling_saved_freq) {
	    error = acpi_tz_cpufreq_restore(sc);
	    if (error == 0)
		sc->tz_cooling_active = FALSE;
	    goto out;
	}
    }

    /* If we are going to a new frequency, activate it. */
    if (levels[i].total_set.freq != freq) {
	ACPI_VPRINT(sc->tz_dev, acpi_device_get_parent_softc(sc->tz_dev),
	    "temperature %d.%dC: %screasing clock speed "
	    "from %d MHz to %d MHz\n",
	    TZ_KELVTOC(sc->tz_temperature),
	    (freq > levels[i].total_set.freq) ? "de" : "in",
	    freq, levels[i].total_set.freq);
	error = CPUFREQ_SET(dev, &levels[i], CPUFREQ_PRIO_KERN);
	if (error == 0 && !sc->tz_cooling_updated) {
	    sc->tz_cooling_saved_freq = freq;
	    sc->tz_cooling_updated = TRUE;
	}
    }

out:
    if (levels)
	free(levels, M_TEMP);
    return (error);
}