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
struct TYPE_2__ {int /*<<< orphan*/  ich_arg; int /*<<< orphan*/  ich_func; } ;
struct a10hdmi_softc {TYPE_1__ mode_hook; int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk_hdmi; int /*<<< orphan*/  clk_lcd; int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  a10hdmi_hpd ; 
 int /*<<< orphan*/  a10hdmi_init (struct a10hdmi_softc*) ; 
 int /*<<< orphan*/  a10hdmi_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int config_intrhook_establish (TYPE_1__*) ; 
 struct a10hdmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
a10hdmi_attach(device_t dev)
{
	struct a10hdmi_softc *sc;
	int error;

	sc = device_get_softc(dev);

	if (bus_alloc_resources(dev, a10hdmi_spec, &sc->res)) {
		device_printf(dev, "cannot allocate resources for device\n");
		return (ENXIO);
	}

	/* Setup clocks */
	error = clk_get_by_ofw_name(dev, 0, "ahb", &sc->clk_ahb);
	if (error != 0) {
		device_printf(dev, "cannot find ahb clock\n");
		return (error);
	}
	error = clk_get_by_ofw_name(dev, 0, "hdmi", &sc->clk_hdmi);
	if (error != 0) {
		device_printf(dev, "cannot find hdmi clock\n");
		return (error);
	}
	error = clk_get_by_ofw_name(dev, 0, "lcd", &sc->clk_lcd);
	if (error != 0) {
		device_printf(dev, "cannot find lcd clock\n");
	}
	/* Enable HDMI clock */
	error = clk_enable(sc->clk_hdmi);
	if (error != 0) {
		device_printf(dev, "cannot enable hdmi clock\n");
		return (error);
	}
	/* Gating AHB clock for HDMI */
	error = clk_enable(sc->clk_ahb);
	if (error != 0) {
		device_printf(dev, "cannot enable ahb gate\n");
		return (error);
	}

	a10hdmi_init(sc);

	sc->mode_hook.ich_func = a10hdmi_hpd;
	sc->mode_hook.ich_arg = dev;

	error = config_intrhook_establish(&sc->mode_hook);
	if (error != 0)
		return (error);

	return (0);
}