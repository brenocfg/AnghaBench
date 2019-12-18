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
struct cf_setting {int /*<<< orphan*/ * dev; int /*<<< orphan*/  lat; void* power; void* volts; int /*<<< orphan*/  freq; } ;
struct bcm2835_cpufreq_softc {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_MBOX_CLOCK_ID_ARM ; 
 void* CPUFREQ_VAL_UNKNOWN ; 
 int EINVAL ; 
 int /*<<< orphan*/  HZ2MHZ (int) ; 
 int /*<<< orphan*/  TRANSITION_LATENCY ; 
 int /*<<< orphan*/  VC_LOCK (struct bcm2835_cpufreq_softc*) ; 
 int /*<<< orphan*/  VC_UNLOCK (struct bcm2835_cpufreq_softc*) ; 
 int bcm2835_cpufreq_get_clock_rate (struct bcm2835_cpufreq_softc*,int /*<<< orphan*/ ) ; 
 struct bcm2835_cpufreq_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (struct cf_setting*,void*,int) ; 

__attribute__((used)) static int
bcm2835_cpufreq_get(device_t dev, struct cf_setting *cf)
{
	struct bcm2835_cpufreq_softc *sc;
	int arm_freq;

	if (cf == NULL)
		return (EINVAL);

	sc = device_get_softc(dev);
	memset(cf, CPUFREQ_VAL_UNKNOWN, sizeof(*cf));
	cf->dev = NULL;

	/* get cuurent value */
	VC_LOCK(sc);
	arm_freq = bcm2835_cpufreq_get_clock_rate(sc,
	    BCM2835_MBOX_CLOCK_ID_ARM);
	VC_UNLOCK(sc);
	if (arm_freq < 0) {
		device_printf(dev, "can't get clock\n");
		return (EINVAL);
	}

	/* CPU clock in MHz or 100ths of a percent. */
	cf->freq = HZ2MHZ(arm_freq);
	/* Voltage in mV. */
	cf->volts = CPUFREQ_VAL_UNKNOWN;
	/* Power consumed in mW. */
	cf->power = CPUFREQ_VAL_UNKNOWN;
	/* Transition latency in us. */
	cf->lat = TRANSITION_LATENCY;
	/* Driver providing this setting. */
	cf->dev = dev;

	return (0);
}