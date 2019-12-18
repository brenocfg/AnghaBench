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
typedef  int uint32_t ;
struct bhnd_pci_softc {int dummy; } ;

/* Variables and functions */
 int BHND_PCIE_MDIOCTL_DONE ; 
 int /*<<< orphan*/  BHND_PCIE_MDIO_CTL ; 
 int BHND_PCIE_MDIO_RETRY_COUNT ; 
 int /*<<< orphan*/  BHND_PCIE_MDIO_RETRY_DELAY ; 
 int BHND_PCI_READ_4 (struct bhnd_pci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 

__attribute__((used)) static int
bhnd_pcie_mdio_wait_idle(struct bhnd_pci_softc *sc)
{
	uint32_t ctl;

	/* Spin waiting for the BUSY flag to clear */
	for (int i = 0; i < BHND_PCIE_MDIO_RETRY_COUNT; i++) {
		ctl = BHND_PCI_READ_4(sc, BHND_PCIE_MDIO_CTL);
		if ((ctl & BHND_PCIE_MDIOCTL_DONE))
			return (0);

		DELAY(BHND_PCIE_MDIO_RETRY_DELAY);
	}

	return (ETIMEDOUT);
}