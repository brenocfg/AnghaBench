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
typedef  int /*<<< orphan*/  uint32_t ;
struct bhnd_pci_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PCIE_MDIO_CTL ; 
 int /*<<< orphan*/  BHND_PCIE_MDIO_CTL_DELAY ; 
 int /*<<< orphan*/  BHND_PCI_LOCK_ASSERT (struct bhnd_pci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PCI_WRITE_4 (struct bhnd_pci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 

__attribute__((used)) static int
bhnd_pcie_mdio_ioctl(struct bhnd_pci_softc *sc, uint32_t cmd)
{
	BHND_PCI_LOCK_ASSERT(sc, MA_OWNED);

	BHND_PCI_WRITE_4(sc, BHND_PCIE_MDIO_CTL, cmd);
	DELAY(BHND_PCIE_MDIO_CTL_DELAY);
	return (0);
}