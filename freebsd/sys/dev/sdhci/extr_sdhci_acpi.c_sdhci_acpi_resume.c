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
struct sdhci_acpi_softc {int /*<<< orphan*/  slot; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_resume (int /*<<< orphan*/ ) ; 
 struct sdhci_acpi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_generic_resume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sdhci_acpi_resume(device_t dev)
{
	struct sdhci_acpi_softc *sc = device_get_softc(dev);
	int err;

	sdhci_generic_resume(&sc->slot);
	err = bus_generic_resume(dev);
	if (err)
		return (err);
	return (0);
}