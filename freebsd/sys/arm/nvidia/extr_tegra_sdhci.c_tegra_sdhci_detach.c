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
struct sdhci_slot {int dummy; } ;
struct tegra_sdhci_softc {int /*<<< orphan*/  mem_res; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  intr_cookie; int /*<<< orphan*/  clk; int /*<<< orphan*/  gpio; struct sdhci_slot slot; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ ) ; 
 struct tegra_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_cleanup_slot (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_fdt_gpio_teardown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_sdhci_detach(device_t dev)
{
	struct tegra_sdhci_softc *sc = device_get_softc(dev);
	struct sdhci_slot *slot = &sc->slot;

	bus_generic_detach(dev);
	sdhci_fdt_gpio_teardown(sc->gpio);
	clk_release(sc->clk);
	bus_teardown_intr(dev, sc->irq_res, sc->intr_cookie);
	bus_release_resource(dev, SYS_RES_IRQ, rman_get_rid(sc->irq_res),
			     sc->irq_res);

	sdhci_cleanup_slot(slot);
	bus_release_resource(dev, SYS_RES_MEMORY,
			     rman_get_rid(sc->mem_res),
			     sc->mem_res);
	return (0);
}