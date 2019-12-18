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
struct ofw_cpulist_softc {int sc_addr_cells; } ;
struct ofw_cpu_softc {int* sc_reg; int sc_reg_valid; int sc_nominal_mhz; int /*<<< orphan*/ * sc_cpu_pcpu; } ;
struct cpuref {scalar_t__ cr_hwref; int /*<<< orphan*/  cr_cpuid; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  clk_t ;
typedef  scalar_t__ cell_t ;
typedef  int /*<<< orphan*/  cell ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENXIO ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int OF_getencprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OF_prop_free (scalar_t__*) ; 
 scalar_t__ bootverbose ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int clk_get_freq (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int nitems (int*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 void* pcpu_find (int /*<<< orphan*/ ) ; 
 int platform_smp_first_cpu (struct cpuref*) ; 
 int platform_smp_next_cpu (struct cpuref*) ; 

__attribute__((used)) static int
ofw_cpu_attach(device_t dev)
{
	struct ofw_cpulist_softc *psc;
	struct ofw_cpu_softc *sc;
	phandle_t node;
	pcell_t cell;
	int rv;
#ifdef EXT_RESOURCES
	clk_t cpuclk;
	uint64_t freq;
#endif

	sc = device_get_softc(dev);
	psc = device_get_softc(device_get_parent(dev));

	if (nitems(sc->sc_reg) < psc->sc_addr_cells) {
		if (bootverbose)
			device_printf(dev, "Too many address cells\n");
		return (EINVAL);
	}

	node = ofw_bus_get_node(dev);

	/* Read and validate the reg property for use later */
	sc->sc_reg_valid = false;
	rv = OF_getencprop(node, "reg", sc->sc_reg, sizeof(sc->sc_reg));
	if (rv < 0)
		device_printf(dev, "missing 'reg' property\n");
	else if ((rv % 4) != 0) {
		if (bootverbose)
			device_printf(dev, "Malformed reg property\n");
	} else if ((rv / 4) != psc->sc_addr_cells) {
		if (bootverbose)
			device_printf(dev, "Invalid reg size %u\n", rv);
	} else
		sc->sc_reg_valid = true;

#ifdef __powerpc__
	/*
	 * On powerpc, "interrupt-servers" denotes a SMT CPU.  Look for any
	 * thread on this CPU, and assign that.
	 */
	if (OF_hasprop(node, "ibm,ppc-interrupt-server#s")) {
		struct cpuref cpuref;
		cell_t *servers;
		int i, nservers, rv;
		
		if ((nservers = OF_getencprop_alloc(node, 
		    "ibm,ppc-interrupt-server#s", (void **)&servers)) < 0)
			return (ENXIO);
		nservers /= sizeof(cell_t);
		for (i = 0; i < nservers; i++) {
			for (rv = platform_smp_first_cpu(&cpuref); rv == 0;
			    rv = platform_smp_next_cpu(&cpuref)) {
				if (cpuref.cr_hwref == servers[i]) {
					sc->sc_cpu_pcpu =
					    pcpu_find(cpuref.cr_cpuid);
					if (sc->sc_cpu_pcpu == NULL) {
						OF_prop_free(servers);
						return (ENXIO);
					}
					break;
				}
			}
			if (rv != ENOENT)
				break;
		}
		OF_prop_free(servers);
		if (sc->sc_cpu_pcpu == NULL) {
			device_printf(dev, "No CPU found for this device.\n");
			return (ENXIO);
		}
	} else
#endif
	sc->sc_cpu_pcpu = pcpu_find(device_get_unit(dev));

	if (OF_getencprop(node, "clock-frequency", &cell, sizeof(cell)) < 0) {
#ifdef EXT_RESOURCES
		rv = clk_get_by_ofw_index(dev, 0, 0, &cpuclk);
		if (rv == 0) {
			rv = clk_get_freq(cpuclk, &freq);
			if (rv != 0 && bootverbose)
				device_printf(dev,
				    "Cannot get freq of property clocks\n");
			else
				sc->sc_nominal_mhz = freq / 1000000;
		} else
#endif
		{
			if (bootverbose)
				device_printf(dev,
				    "missing 'clock-frequency' property\n");
		}
	} else
		sc->sc_nominal_mhz = cell / 1000000; /* convert to MHz */

	if (sc->sc_nominal_mhz != 0 && bootverbose)
		device_printf(dev, "Nominal frequency %dMhz\n",
		    sc->sc_nominal_mhz);
	bus_generic_probe(dev);
	return (bus_generic_attach(dev));
}