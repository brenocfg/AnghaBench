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
struct pmufreq_softc {int /*<<< orphan*/  minfreq; int /*<<< orphan*/  maxfreq; } ;
struct cf_setting {void* lat; void* dev; int /*<<< orphan*/  freq; } ;
typedef  void* device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int E2BIG ; 
 int EINVAL ; 
 void* INT_MAX ; 
 struct pmufreq_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  memset (struct cf_setting*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pmufreq_settings(device_t dev, struct cf_setting *sets, int *count)
{
	struct pmufreq_softc *sc;

	sc = device_get_softc(dev);
	if (sets == NULL || count == NULL)
		return (EINVAL);
	if (*count < 2)
		return (E2BIG);

	/* Return a list of valid settings for this driver. */
	memset(sets, CPUFREQ_VAL_UNKNOWN, sizeof(*sets) * 2);

	sets[0].freq = sc->maxfreq; sets[0].dev = dev;
	sets[1].freq = sc->minfreq; sets[1].dev = dev;
	/* Set high latency for CPU frequency changes, it's a tedious process. */
	sets[0].lat = INT_MAX;
	sets[1].lat = INT_MAX;
	*count = 2;

	return (0);
}