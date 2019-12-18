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
struct cf_setting {int freq; int volts; void* dev; void* lat; } ;
struct bcm2835_cpufreq_softc {int arm_max_freq; int arm_min_freq; scalar_t__ turbo_mode; int max_voltage_core; int min_voltage_core; } ;
typedef  void* device_t ;

/* Variables and functions */
 scalar_t__ BCM2835_MBOX_TURBO_ON ; 
 int MHZSTEP ; 
 void* TRANSITION_LATENCY ; 
 int cpufreq_lowest_freq ; 
 struct bcm2835_cpufreq_softc* device_get_softc (void*) ; 

__attribute__((used)) static int
bcm2835_cpufreq_make_freq_list(device_t dev, struct cf_setting *sets,
    int *count)
{
	struct bcm2835_cpufreq_softc *sc;
	int freq, min_freq, volts, rem;
	int idx;

	sc = device_get_softc(dev);
	freq = sc->arm_max_freq;
	min_freq = sc->arm_min_freq;

	/* adjust head freq to STEP */
	rem = freq % MHZSTEP;
	freq -= rem;
	if (freq < min_freq)
		freq = min_freq;

	/* if non-turbo, add extra low freq */
	if (sc->turbo_mode != BCM2835_MBOX_TURBO_ON)
		if (min_freq > cpufreq_lowest_freq)
			min_freq = cpufreq_lowest_freq;

#ifdef SOC_BCM2835
	/* from freq to min_freq */
	for (idx = 0; idx < *count && freq >= min_freq; idx++) {
		if (freq > sc->arm_min_freq)
			volts = sc->max_voltage_core;
		else
			volts = sc->min_voltage_core;
		sets[idx].freq = freq;
		sets[idx].volts = volts;
		sets[idx].lat = TRANSITION_LATENCY;
		sets[idx].dev = dev;
		freq -= MHZSTEP;
	}
#else
	/* XXX RPi2 have only 900/600MHz */
	idx = 0;
	volts = sc->min_voltage_core;
	sets[idx].freq = freq;
	sets[idx].volts = volts;
	sets[idx].lat = TRANSITION_LATENCY;
	sets[idx].dev = dev;
	idx++;
	if (freq != min_freq) {
		sets[idx].freq = min_freq;
		sets[idx].volts = volts;
		sets[idx].lat = TRANSITION_LATENCY;
		sets[idx].dev = dev;
		idx++;
	}
#endif
	*count = idx;

	return (0);
}