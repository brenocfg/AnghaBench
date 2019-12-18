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
struct TYPE_2__ {int /*<<< orphan*/  nvidia_head; } ;
struct dc_softc {int /*<<< orphan*/  dev; TYPE_1__ tegra_crtc; int /*<<< orphan*/  clk_dc; int /*<<< orphan*/  clk_parent; int /*<<< orphan*/  hwreset_dc; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_fdt_resources(struct dc_softc *sc, phandle_t node)
{
	int rv;

	rv = hwreset_get_by_ofw_name(sc->dev, 0, "dc", &sc->hwreset_dc);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'dc' reset\n");
		return (rv);
	}
	rv = clk_get_by_ofw_name(sc->dev, 0, "parent", &sc->clk_parent);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'parent' clock\n");
		return (rv);
	}
	rv = clk_get_by_ofw_name(sc->dev, 0, "dc", &sc->clk_dc);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot get 'dc' clock\n");
		return (rv);
	}

	rv = OF_getencprop(node, "nvidia,head", &sc->tegra_crtc.nvidia_head,
	    sizeof(sc->tegra_crtc.nvidia_head));
	if (rv <= 0) {
		device_printf(sc->dev,
		    "Cannot get 'nvidia,head' property\n");
		return (rv);
	}
	return (0);
}