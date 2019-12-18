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
struct bhndb_pci_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bhnd_clock ;

/* Variables and functions */
 scalar_t__ BHND_CLOCK_HT ; 
 int ENODEV ; 
 int ENXIO ; 
 int bhndb_enable_pci_clocks (int /*<<< orphan*/ ) ; 
 scalar_t__ bhndb_is_pcie_attached (int /*<<< orphan*/ ) ; 
 struct bhndb_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhndb_pci_pwrctl_ungate_clock(device_t dev, device_t child,
	bhnd_clock clock)
{
	struct bhndb_pci_softc *sc = device_get_softc(dev);

	/* Only supported on PCI devices */
	if (bhndb_is_pcie_attached(sc->dev))
		return (ENODEV);

	/* Only HT is supported */
	if (clock != BHND_CLOCK_HT)
		return (ENXIO);

	return (bhndb_enable_pci_clocks(sc->dev));
}