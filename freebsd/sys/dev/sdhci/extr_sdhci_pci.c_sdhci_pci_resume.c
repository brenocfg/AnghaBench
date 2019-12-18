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
struct sdhci_pci_softc {int num_slots; int quirks; int /*<<< orphan*/ * slots; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int SDHCI_QUIRK_LOWER_FREQUENCY ; 
 int bus_generic_resume (int /*<<< orphan*/ ) ; 
 struct sdhci_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_generic_resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdhci_lower_frequency (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sdhci_pci_resume(device_t dev)
{
	struct sdhci_pci_softc *sc = device_get_softc(dev);
	int i, err;

	for (i = 0; i < sc->num_slots; i++)
		sdhci_generic_resume(&sc->slots[i]);
	err = bus_generic_resume(dev);
	if (err)
		return (err);
	if (sc->quirks & SDHCI_QUIRK_LOWER_FREQUENCY)
		sdhci_lower_frequency(dev);
	return (0);
}