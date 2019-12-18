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
struct imx6_anatop_softc {int cpu_init_done; int /*<<< orphan*/  cpu_curmv; int /*<<< orphan*/  cpu_curmhz; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PASS_CPU ; 
 int BUS_PASS_ORDER_MIDDLE ; 
 scalar_t__ bootverbose ; 
 int const bus_current_pass ; 
 int /*<<< orphan*/  bus_generic_new_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_initialize (struct imx6_anatop_softc*) ; 
 struct imx6_anatop_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_tempmon (struct imx6_anatop_softc*) ; 

__attribute__((used)) static void
imx6_anatop_new_pass(device_t dev)
{
	struct imx6_anatop_softc *sc;
	const int cpu_init_pass = BUS_PASS_CPU + BUS_PASS_ORDER_MIDDLE;

	/*
	 * We attach during BUS_PASS_BUS (because some day we will be a
	 * simplebus that has regulator devices as children), but some of our
	 * init work cannot be done until BUS_PASS_CPU (we rely on other devices
	 * that attach on the CPU pass).
	 */
	sc = device_get_softc(dev);
	if (!sc->cpu_init_done && bus_current_pass >= cpu_init_pass) {
		sc->cpu_init_done = true;
		cpufreq_initialize(sc);
		initialize_tempmon(sc);
		if (bootverbose) {
			device_printf(sc->dev, "CPU %uMHz @ %umV\n", 
			    sc->cpu_curmhz, sc->cpu_curmv);
		}
	}
	bus_generic_new_pass(dev);
}