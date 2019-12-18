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
typedef  int uint64_t ;
struct smist_softc {struct cf_setting* sets; } ;
struct cf_setting {int freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CPUFREQ_VAL_UNKNOWN ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GET_STATE ; 
 int /*<<< orphan*/  cpu_est_clockrate (int /*<<< orphan*/ ,int*) ; 
 struct smist_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int getset_state (struct smist_softc*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smist_get(device_t dev, struct cf_setting *set)
{
	struct smist_softc *sc;
	uint64_t rate;
	int state;
	int rv;

	sc = device_get_softc(dev);
	rv = getset_state(sc, &state, GET_STATE);
	if (rv != 0)
		return (rv);

	/* If we haven't changed settings yet, estimate the current value. */
	if (sc->sets[state].freq == CPUFREQ_VAL_UNKNOWN) {
		cpu_est_clockrate(0, &rate);
		sc->sets[state].freq = rate / 1000000;
		DPRINT(dev, "get calibrated new rate of %d\n",
		    sc->sets[state].freq);
	}
	*set = sc->sets[state];

	return (0);
}