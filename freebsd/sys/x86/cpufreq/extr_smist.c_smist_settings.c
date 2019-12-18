#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smist_softc {TYPE_1__* sets; } ;
struct cf_setting {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {scalar_t__ freq; } ;

/* Variables and functions */
 scalar_t__ CPUFREQ_VAL_UNKNOWN ; 
 int E2BIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,struct cf_setting*,int) ; 
 struct smist_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smist_get (int /*<<< orphan*/ ,struct cf_setting*) ; 
 int /*<<< orphan*/  smist_set (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
smist_settings(device_t dev, struct cf_setting *sets, int *count)
{
	struct smist_softc *sc;
	struct cf_setting set;
	int first, i;

	if (sets == NULL || count == NULL)
		return (EINVAL);
	if (*count < 2) {
		*count = 2;
		return (E2BIG);
	}
	sc = device_get_softc(dev);

	/*
	 * Estimate frequencies for both levels, temporarily switching to
	 * the other one if we haven't calibrated it yet.
	 */
	for (i = 0; i < 2; i++) {
		if (sc->sets[i].freq == CPUFREQ_VAL_UNKNOWN) {
			first = (i == 0) ? 1 : 0;
			smist_set(dev, &sc->sets[i]);
			smist_get(dev, &set);
			smist_set(dev, &sc->sets[first]);
		}
	}

	bcopy(sc->sets, sets, sizeof(sc->sets));
	*count = 2;

	return (0);
}