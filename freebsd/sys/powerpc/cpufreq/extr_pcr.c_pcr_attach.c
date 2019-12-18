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
typedef  int /*<<< orphan*/  uint32_t ;
struct pcr_softc {int nmodes; int /*<<< orphan*/ * pcr_vals; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  modes ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_getprop (scalar_t__,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ OF_getproplen (scalar_t__,char*) ; 
 int /*<<< orphan*/  OF_parent (scalar_t__) ; 
 size_t PCR_TO_FREQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct pcr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcr_attach(device_t dev)
{
	struct pcr_softc *sc;
	phandle_t cpu;
	uint32_t modes[3];
	int i;

	sc = device_get_softc(dev);
	sc->dev = dev;

	cpu = ofw_bus_get_node(device_get_parent(dev));

	if (cpu <= 0) {
		device_printf(dev,"No CPU device tree node!\n");
		return (ENXIO);
	}

	if (OF_getproplen(cpu, "power-mode-data") <= 0) {
		/* Use the first CPU's node */
		cpu = OF_child(OF_parent(cpu));
	}

	/*
	 * Collect the PCR values for each mode from the device tree.
	 * These include bus timing information, and so cannot be
	 * directly computed.
	 */
	sc->nmodes = OF_getproplen(cpu, "power-mode-data");
	if (sc->nmodes <= 0 || sc->nmodes > sizeof(sc->pcr_vals)) {
		device_printf(dev,"No power mode data in device tree!\n");
		return (ENXIO);
	}
	OF_getprop(cpu, "power-mode-data", modes, sc->nmodes);
	sc->nmodes /= sizeof(modes[0]);

	/* Sort the modes */
	for (i = 0; i < sc->nmodes; i++)
		sc->pcr_vals[PCR_TO_FREQ(modes[i])] = modes[i];

	cpufreq_register(dev);
	return (0);
}