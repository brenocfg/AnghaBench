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
struct p4tcc_softc {int set_count; } ;
struct cf_setting {int /*<<< orphan*/  dev; int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int E2BIG ; 
 int EINVAL ; 
 int TCC_NUM_SETTINGS ; 
 int /*<<< orphan*/  TCC_SPEED_PERCENT (int) ; 
 struct p4tcc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cf_setting*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
p4tcc_settings(device_t dev, struct cf_setting *sets, int *count)
{
	struct p4tcc_softc *sc;
	int i, val;

	sc = device_get_softc(dev);
	if (sets == NULL || count == NULL)
		return (EINVAL);
	if (*count < sc->set_count)
		return (E2BIG);

	/* Return a list of valid settings for this driver. */
	memset(sets, CPUFREQ_VAL_UNKNOWN, sizeof(*sets) * sc->set_count);
	val = TCC_NUM_SETTINGS;
	for (i = 0; i < sc->set_count; i++, val--) {
		sets[i].freq = TCC_SPEED_PERCENT(val);
		sets[i].dev = dev;
	}
	*count = sc->set_count;

	return (0);
}