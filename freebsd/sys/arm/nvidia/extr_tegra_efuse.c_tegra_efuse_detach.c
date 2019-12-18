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
struct tegra_efuse_softc {int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * reset; int /*<<< orphan*/ * clk; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dev_sc ; 
 struct tegra_efuse_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwreset_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tegra_efuse_detach(device_t dev)
{
	struct tegra_efuse_softc *sc;

	sc = device_get_softc(dev);
	dev_sc = NULL;
	if (sc->clk != NULL)
		clk_release(sc->clk);
	if (sc->reset != NULL)
		hwreset_release(sc->reset);
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);

	return (bus_generic_detach(dev));
}