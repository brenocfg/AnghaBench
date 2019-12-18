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
struct sdhci_acpi_softc {scalar_t__ mem_res; int /*<<< orphan*/  slot; scalar_t__ irq_res; scalar_t__ intrhand; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct sdhci_acpi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (scalar_t__) ; 
 int /*<<< orphan*/  sdhci_cleanup_slot (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sdhci_acpi_detach(device_t dev)
{
	struct sdhci_acpi_softc *sc = device_get_softc(dev);

	if (sc->intrhand)
		bus_teardown_intr(dev, sc->irq_res, sc->intrhand);
	if (sc->irq_res)
		bus_release_resource(dev, SYS_RES_IRQ,
		    rman_get_rid(sc->irq_res), sc->irq_res);

	if (sc->mem_res) {
		sdhci_cleanup_slot(&sc->slot);
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(sc->mem_res), sc->mem_res);
	}

	return (0);
}