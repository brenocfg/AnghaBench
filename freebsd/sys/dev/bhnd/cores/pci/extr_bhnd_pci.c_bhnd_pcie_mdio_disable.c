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
struct bhnd_pci_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ bhnd_pcie_mdio_ioctl (struct bhnd_pci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
bhnd_pcie_mdio_disable(struct bhnd_pci_softc *sc)
{
	if (bhnd_pcie_mdio_ioctl(sc, 0))
		device_printf(sc->dev, "failed to disable MDIO clock\n");
}