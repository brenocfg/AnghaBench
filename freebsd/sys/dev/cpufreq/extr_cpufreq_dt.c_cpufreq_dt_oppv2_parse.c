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
typedef  scalar_t__ uint32_t ;
struct cpufreq_dt_softc {int nopp; TYPE_1__* opp; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ phandle_t ;
typedef  scalar_t__ pcell_t ;
typedef  int /*<<< orphan*/  opp_xref ;
typedef  int /*<<< orphan*/  lat ;
typedef  int /*<<< orphan*/  cell ;
struct TYPE_3__ {int freq; int clk_latency; int turbo_mode; int opp_suspend; scalar_t__ uvolt_target; scalar_t__ uvolt_max; scalar_t__ uvolt_min; } ;

/* Variables and functions */
 int CPUFREQ_VAL_UNKNOWN ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getencprop (scalar_t__,char*,scalar_t__*,int) ; 
 int OF_getencprop_alloc_multi (scalar_t__,char*,int,void**) ; 
 scalar_t__ OF_hasprop (scalar_t__,char*) ; 
 scalar_t__ OF_node_from_xref (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_prop_free (scalar_t__*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpufreq_dt_oppv2_parse(struct cpufreq_dt_softc *sc, phandle_t node)
{
	phandle_t opp, opp_table, opp_xref;
	pcell_t cell[2];
	uint32_t *volts, lat;
	int nvolt, i;

	if (OF_getencprop(node, "operating-points-v2", &opp_xref,
	    sizeof(opp_xref)) == -1) {
		device_printf(sc->dev, "Cannot get xref to oppv2 table\n");
		return (ENXIO);
	}

	opp_table = OF_node_from_xref(opp_xref);
	if (opp_table == opp_xref)
		return (ENXIO);

	if (!OF_hasprop(opp_table, "opp-shared")) {
		device_printf(sc->dev, "Only opp-shared is supported\n");
		return (ENXIO);
	}

	for (opp = OF_child(opp_table); opp > 0; opp = OF_peer(opp))
		sc->nopp += 1;

	sc->opp = malloc(sizeof(*sc->opp) * sc->nopp, M_DEVBUF, M_WAITOK);

	for (i = 0, opp_table = OF_child(opp_table); opp_table > 0;
	     opp_table = OF_peer(opp_table), i++) {
		/* opp-hz is a required property */
		if (OF_getencprop(opp_table, "opp-hz", cell,
		    sizeof(cell)) == -1)
			continue;

		sc->opp[i].freq = cell[0];
		sc->opp[i].freq <<= 32;
		sc->opp[i].freq |= cell[1];

		if (OF_getencprop(opp_table, "clock-latency", &lat,
		    sizeof(lat)) == -1)
			sc->opp[i].clk_latency = CPUFREQ_VAL_UNKNOWN;
		else
			sc->opp[i].clk_latency = (int)lat;

		if (OF_hasprop(opp_table, "turbo-mode"))
			sc->opp[i].turbo_mode = true;
		if (OF_hasprop(opp_table, "opp-suspend"))
			sc->opp[i].opp_suspend = true;

		nvolt = OF_getencprop_alloc_multi(opp_table, "opp-microvolt",
		  sizeof(*volts), (void **)&volts);
		if (nvolt == 1) {
			sc->opp[i].uvolt_target = volts[0];
			sc->opp[i].uvolt_min = volts[0];
			sc->opp[i].uvolt_max = volts[0];
		} else if (nvolt == 3) {
			sc->opp[i].uvolt_target = volts[0];
			sc->opp[i].uvolt_min = volts[1];
			sc->opp[i].uvolt_max = volts[2];
		} else {
			device_printf(sc->dev,
			    "Wrong count of opp-microvolt property\n");
			OF_prop_free(volts);
			free(sc->opp, M_DEVBUF);
			return (ENXIO);
		}
		OF_prop_free(volts);

		if (bootverbose)
			device_printf(sc->dev, "%ju.%03ju Mhz (%u uV)\n",
			    sc->opp[i].freq / 1000000,
			    sc->opp[i].freq % 1000000,
			    sc->opp[i].uvolt_target);
	}
	return (0);
}