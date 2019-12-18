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
typedef  int uint32_t ;
struct mpc85xx_jog_softc {int high; int low; } ;
struct cf_setting {int freq; int* spec; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int E2BIG ; 
 int EINVAL ; 
 int MHZ ; 
 struct mpc85xx_jog_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cf_setting*,int /*<<< orphan*/ ,int) ; 
 int mpc85xx_get_system_clock () ; 

__attribute__((used)) static int
mpc85xx_jog_settings(device_t dev, struct cf_setting *sets, int *count)
{
	struct mpc85xx_jog_softc *sc;
	uint32_t sysclk;
	int i;

	sc = device_get_softc(dev);
	if (sets == NULL || count == NULL)
		return (EINVAL);
	if (*count < sc->high - 1)
		return (E2BIG);

	sysclk = mpc85xx_get_system_clock();
	/* Return a list of valid settings for this driver. */
	memset(sets, CPUFREQ_VAL_UNKNOWN, sizeof(*sets) * sc->high);

	for (i = sc->high; i >= sc->low; --i) {
		sets[sc->high - i].freq = sysclk * i / MHZ;
		sets[sc->high - i].dev = dev;
		sets[sc->high - i].spec[0] = i;
	}
	*count = sc->high - sc->low + 1;

	return (0);
}