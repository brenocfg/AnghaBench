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
 int /*<<< orphan*/  BHND_PCIE_ASSERT (struct bhnd_pci_softc*) ; 
 int BHND_PCIE_MDIOCTL_DIVISOR_VAL ; 
 int BHND_PCIE_MDIOCTL_PREAM_EN ; 
 int bhnd_pcie_mdio_ioctl (struct bhnd_pci_softc*,int) ; 

__attribute__((used)) static int
bhnd_pcie_mdio_enable(struct bhnd_pci_softc *sc)
{
	uint32_t ctl;

	BHND_PCIE_ASSERT(sc);

	/* Enable MDIO clock and preamble mode */
	ctl = BHND_PCIE_MDIOCTL_PREAM_EN|BHND_PCIE_MDIOCTL_DIVISOR_VAL;
	return (bhnd_pcie_mdio_ioctl(sc, ctl));
}