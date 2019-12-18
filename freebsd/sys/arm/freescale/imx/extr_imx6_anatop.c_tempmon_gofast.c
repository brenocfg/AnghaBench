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
struct imx6_anatop_softc {scalar_t__ cpu_curmhz; scalar_t__ cpu_maxmhz; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_nearest_oppt (struct imx6_anatop_softc*,scalar_t__) ; 
 int /*<<< orphan*/  cpufreq_set_clock (struct imx6_anatop_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tempmon_gofast(struct imx6_anatop_softc *sc)
{

	if (sc->cpu_curmhz < sc->cpu_maxmhz) {
		cpufreq_set_clock(sc, cpufreq_nearest_oppt(sc, sc->cpu_maxmhz));
	}
}