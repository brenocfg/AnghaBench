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
typedef  int uint32_t ;
struct cpufreq_dt_softc {int nopp; TYPE_1__* opp; int /*<<< orphan*/  dev; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  lat ;
struct TYPE_2__ {int freq; int uvolt_min; int uvolt_max; int uvolt_target; int clk_latency; } ;

/* Variables and functions */
 int CPUFREQ_VAL_UNKNOWN ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_OFWPROP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  free (int*,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpufreq_dt_oppv1_parse(struct cpufreq_dt_softc *sc, phandle_t node)
{
	uint32_t *opp, lat;
	ssize_t n;

	sc->nopp = OF_getencprop_alloc_multi(node, "operating-points",
	    sizeof(uint32_t) * 2, (void **)&opp);
	if (sc->nopp == -1)
		return (ENXIO);

	if (OF_getencprop(node, "clock-latency", &lat, sizeof(lat)) == -1)
		lat = CPUFREQ_VAL_UNKNOWN;

	sc->opp = malloc(sizeof(*sc->opp) * sc->nopp, M_DEVBUF, M_WAITOK);

	for (n = 0; n < sc->nopp; n++) {
		sc->opp[n].freq = opp[n * 2 + 0] * 1000;
		sc->opp[n].uvolt_min = opp[n * 2 + 1];
		sc->opp[n].uvolt_max = sc->opp[n].uvolt_min;
		sc->opp[n].uvolt_target = sc->opp[n].uvolt_min;
		sc->opp[n].clk_latency = lat;

		if (bootverbose)
			device_printf(sc->dev, "%ju.%03ju MHz, %u uV\n",
			    sc->opp[n].freq / 1000000,
			    sc->opp[n].freq % 1000000,
			    sc->opp[n].uvolt_target);
	}
	free(opp, M_OFWPROP);

	return (0);
}