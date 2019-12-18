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
struct TYPE_2__ {scalar_t__ nvidia_head; } ;
struct dc_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  hwreset_dc; int /*<<< orphan*/  clk_dc; TYPE_1__ tegra_crtc; int /*<<< orphan*/  clk_parent; } ;

/* Variables and functions */
 int TEGRA_POWERGATE_DIS ; 
 int TEGRA_POWERGATE_DISB ; 
 int clk_set_parent_by_clk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int tegra_powergate_sequence_power_up (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enable_fdt_resources(struct dc_softc *sc)
{
	int id, rv;

	rv = clk_set_parent_by_clk(sc->clk_dc, sc->clk_parent);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot set parent for 'dc' clock\n");
		return (rv);
	}

	id = (sc->tegra_crtc.nvidia_head == 0) ?
	    TEGRA_POWERGATE_DIS: TEGRA_POWERGATE_DISB;
	rv = tegra_powergate_sequence_power_up(id, sc->clk_dc, sc->hwreset_dc);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot enable 'DIS' powergate\n");
		return (rv);
	}

	return (0);
}