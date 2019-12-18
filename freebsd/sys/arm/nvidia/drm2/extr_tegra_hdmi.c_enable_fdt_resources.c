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
struct hdmi_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  hwreset_hdmi; int /*<<< orphan*/  clk_hdmi; int /*<<< orphan*/  supply_vdd; int /*<<< orphan*/  supply_pll; int /*<<< orphan*/  supply_hdmi; int /*<<< orphan*/  clk_parent; } ;

/* Variables and functions */
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_set_freq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int clk_set_parent_by_clk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enable_fdt_resources(struct hdmi_softc *sc)
{
	int rv;


	rv = clk_set_parent_by_clk(sc->clk_hdmi, sc->clk_parent);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot set parent for 'hdmi' clock\n");
		return (rv);
	}

	/* 594 MHz is arbitrarily selected value */
	rv = clk_set_freq(sc->clk_parent, 594000000, 0);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot set frequency for 'hdmi' parent clock\n");
		return (rv);
	}
	rv = clk_set_freq(sc->clk_hdmi, 594000000 / 4, 0);
	if (rv != 0) {
		device_printf(sc->dev,
		    "Cannot set frequency for 'hdmi' parent clock\n");
		return (rv);
	}

	rv = regulator_enable(sc->supply_hdmi);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable  'hdmi' regulator\n");
		return (rv);
	}
	rv = regulator_enable(sc->supply_pll);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable  'pll' regulator\n");
		return (rv);
	}
	rv = regulator_enable(sc->supply_vdd);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable  'vdd' regulator\n");
		return (rv);
	}

	rv = clk_enable(sc->clk_hdmi);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'hdmi' clock\n");
		return (rv);
	}

	rv = hwreset_deassert(sc->hwreset_hdmi);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot unreset  'hdmi' reset\n");
		return (rv);
	}
	return (0);
}