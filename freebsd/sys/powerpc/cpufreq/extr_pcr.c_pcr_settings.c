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
struct pcr_softc {int nmodes; } ;
struct cf_setting {int freq; void* dev; } ;
typedef  void* device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int E2BIG ; 
 int EINVAL ; 
 struct pcr_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  memset (struct cf_setting*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pcr_settings(device_t dev, struct cf_setting *sets, int *count)
{
	struct pcr_softc *sc;

	sc = device_get_softc(dev);
	if (sets == NULL || count == NULL)
		return (EINVAL);
	if (*count < sc->nmodes)
		return (E2BIG);

	/* Return a list of valid settings for this driver. */
	memset(sets, CPUFREQ_VAL_UNKNOWN, sizeof(*sets) * sc->nmodes);

	sets[0].freq = 10000; sets[0].dev = dev;
	sets[1].freq = 5000; sets[1].dev = dev;
	if (sc->nmodes > 2) {
		sets[2].freq = 2500;
		sets[2].dev = dev;
	}
	*count = sc->nmodes;

	return (0);
}