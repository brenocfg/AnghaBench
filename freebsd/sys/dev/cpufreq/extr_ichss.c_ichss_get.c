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
typedef  size_t uint8_t ;
typedef  int uint64_t ;
struct ichss_softc {struct cf_setting* sets; int /*<<< orphan*/  ctrl_reg; } ;
struct cf_setting {int freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CPUFREQ_VAL_UNKNOWN ; 
 int /*<<< orphan*/  DPRINT (char*,int) ; 
 size_t ICHSS_CTRL_BIT ; 
 size_t ICH_GET_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_est_clockrate (int /*<<< orphan*/ ,int*) ; 
 struct ichss_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ichss_get(device_t dev, struct cf_setting *set)
{
	struct ichss_softc *sc;
	uint64_t rate;
	uint8_t state;

	sc = device_get_softc(dev);
	state = ICH_GET_REG(sc->ctrl_reg) & ICHSS_CTRL_BIT;

	/* If we haven't changed settings yet, estimate the current value. */
	if (sc->sets[state].freq == CPUFREQ_VAL_UNKNOWN) {
		cpu_est_clockrate(0, &rate);
		sc->sets[state].freq = rate / 1000000;
		DPRINT("ichss: get calibrated new rate of %d\n",
		    sc->sets[state].freq);
	}
	*set = sc->sets[state];

	return (0);
}