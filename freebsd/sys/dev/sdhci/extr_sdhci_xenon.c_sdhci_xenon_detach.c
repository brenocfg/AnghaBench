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
struct sdhci_xenon_softc {int /*<<< orphan*/ * slot; int /*<<< orphan*/  mem_res; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  intrhand; int /*<<< orphan*/ * gpio; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sdhci_xenon_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_cleanup_slot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdhci_fdt_gpio_teardown (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sdhci_xenon_detach(device_t dev)
{
	struct sdhci_xenon_softc *sc = device_get_softc(dev);

	if (sc->gpio != NULL)
		sdhci_fdt_gpio_teardown(sc->gpio);

	bus_generic_detach(dev);
	bus_teardown_intr(dev, sc->irq_res, sc->intrhand);
	bus_release_resource(dev, SYS_RES_IRQ, rman_get_rid(sc->irq_res),
	    sc->irq_res);
	sdhci_cleanup_slot(sc->slot);
	bus_release_resource(dev, SYS_RES_MEMORY, rman_get_rid(sc->mem_res),
	    sc->mem_res);
	free(sc->slot, M_DEVBUF);
	sc->slot = NULL;

	return (0);
}