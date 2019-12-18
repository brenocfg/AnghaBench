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
struct hdmi_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_hdmi; int /*<<< orphan*/  clk_parent; int /*<<< orphan*/  hwreset_hdmi; int /*<<< orphan*/  supply_vdd; int /*<<< orphan*/  supply_pll; int /*<<< orphan*/  supply_hdmi; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int ENXIO ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int regulator_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_fdt_resources(struct hdmi_softc *sc, phandle_t node)
{
	int rv;

	rv = regulator_get_by_ofw_property(sc->dev, 0, "hdmi-supply",
	    &sc->supply_hdmi);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'hdmi' regulator\n");
		return (ENXIO);
	}
	rv = regulator_get_by_ofw_property(sc->dev,0,  "pll-supply",
	    &sc->supply_pll);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'pll' regulator\n");
		return (ENXIO);
	}
	rv = regulator_get_by_ofw_property(sc->dev, 0, "vdd-supply",
	    &sc->supply_vdd);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'vdd' regulator\n");
		return (ENXIO);
	}

	rv = hwreset_get_by_ofw_name(sc->dev, 0, "hdmi", &sc->hwreset_hdmi);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'hdmi' reset\n");
		return (ENXIO);
	}
	rv = clk_get_by_ofw_name(sc->dev, 0, "parent", &sc->clk_parent);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'parent' clock\n");
		return (ENXIO);
	}
	rv = clk_get_by_ofw_name(sc->dev, 0, "hdmi", &sc->clk_hdmi);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'hdmi' clock\n");
		return (ENXIO);
	}

	return (0);
}