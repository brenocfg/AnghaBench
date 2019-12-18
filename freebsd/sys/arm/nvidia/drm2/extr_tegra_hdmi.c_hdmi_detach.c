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
struct hdmi_softc {int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * supply_vdd; int /*<<< orphan*/ * supply_pll; int /*<<< orphan*/ * supply_hdmi; int /*<<< orphan*/ * hwreset_hdmi; int /*<<< orphan*/ * clk_hdmi; int /*<<< orphan*/ * clk_parent; int /*<<< orphan*/ * irq_ih; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TEGRA_DRM_DEREGISTER_CLIENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct hdmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwreset_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hdmi_detach(device_t dev)
{
	struct hdmi_softc *sc;
	sc = device_get_softc(dev);

	TEGRA_DRM_DEREGISTER_CLIENT(device_get_parent(sc->dev), sc->dev);

	if (sc->irq_ih != NULL)
		bus_teardown_intr(dev, sc->irq_res, sc->irq_ih);
	if (sc->clk_parent != NULL)
		clk_release(sc->clk_parent);
	if (sc->clk_hdmi != NULL)
		clk_release(sc->clk_hdmi);
	if (sc->hwreset_hdmi != NULL)
		hwreset_release(sc->hwreset_hdmi);
	if (sc->supply_hdmi != NULL)
		regulator_release(sc->supply_hdmi);
	if (sc->supply_pll != NULL)
		regulator_release(sc->supply_pll);
	if (sc->supply_vdd != NULL)
		regulator_release(sc->supply_vdd);
	if (sc->irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq_res);
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);
	return (bus_generic_detach(dev));
}