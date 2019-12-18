#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra124_cpufreq_softc {int nspeed_points; TYPE_1__* speed_points; } ;
struct cpu_speed_point {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  uvolt; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/ * cpu_freq_tbl ; 
 int /*<<< orphan*/  freq_to_voltage (struct tegra124_cpufreq_softc*,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
build_speed_points(struct tegra124_cpufreq_softc *sc) {
	int i;

	sc->nspeed_points = nitems(cpu_freq_tbl);
	sc->speed_points = malloc(sizeof(struct cpu_speed_point) *
	    sc->nspeed_points, M_DEVBUF, M_NOWAIT);
	for (i = 0; i < sc->nspeed_points; i++) {
		sc->speed_points[i].freq = cpu_freq_tbl[i];
		sc->speed_points[i].uvolt = freq_to_voltage(sc,
		    cpu_freq_tbl[i]);
	}
}