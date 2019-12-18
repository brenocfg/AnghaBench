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
struct sdhci_pci_softc {int num_slots; int quirks; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * slots; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  intrhand; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int SDHCI_QUIRK_LOWER_FREQUENCY ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sdhci_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_cleanup_slot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdhci_restore_frequency (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sdhci_pci_detach(device_t dev)
{
	struct sdhci_pci_softc *sc = device_get_softc(dev);
	int i;

	bus_teardown_intr(dev, sc->irq_res, sc->intrhand);
	bus_release_resource(dev, SYS_RES_IRQ,
	    rman_get_rid(sc->irq_res), sc->irq_res);
	pci_release_msi(dev);

	for (i = 0; i < sc->num_slots; i++) {
		sdhci_cleanup_slot(&sc->slots[i]);
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(sc->mem_res[i]), sc->mem_res[i]);
	}
	if (sc->quirks & SDHCI_QUIRK_LOWER_FREQUENCY)
		sdhci_restore_frequency(dev);
	return (0);
}