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
struct ofw_compat_data {scalar_t__ ocd_data; } ;
struct mpc85xx_jog_softc {int /*<<< orphan*/  low; int /*<<< orphan*/  min_freq; int /*<<< orphan*/  cpu; int /*<<< orphan*/  high; int /*<<< orphan*/  dev; } ;
struct mpc85xx_constraints {int /*<<< orphan*/  min_mult; int /*<<< orphan*/  threshold; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GUTS_PORPLLSR ; 
 int /*<<< orphan*/  OF_getencprop (scalar_t__,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PMJCR_GET_CORE_MULT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccsr_read4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct mpc85xx_jog_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct ofw_compat_data* mpc85xx_jog_devcompat () ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpc85xx_jog_attach(device_t dev)
{
	struct ofw_compat_data *compat;
	struct mpc85xx_jog_softc *sc;
	struct mpc85xx_constraints *constraints;
	phandle_t cpu;
	uint32_t reg;

	sc = device_get_softc(dev);
	sc->dev = dev;

	compat = mpc85xx_jog_devcompat();
	constraints = (struct mpc85xx_constraints *)compat->ocd_data;
	cpu = ofw_bus_get_node(device_get_parent(dev));

	if (cpu <= 0) {
		device_printf(dev,"No CPU device tree node!\n");
		return (ENXIO);
	}

	OF_getencprop(cpu, "reg", &sc->cpu, sizeof(sc->cpu));

	reg = ccsr_read4(GUTS_PORPLLSR);
	
	/*
	 * Assume power-on PLL is the highest PLL config supported on the
	 * board.
	 */
	sc->high = PMJCR_GET_CORE_MULT(reg, sc->cpu);
	sc->min_freq = constraints->threshold;
	sc->low = constraints->min_mult;

	cpufreq_register(dev);
	return (0);
}