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
typedef  int uint16_t ;
struct bhnd_pci_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PCIE_MDIODATA_ADDR (int,int) ; 
 int /*<<< orphan*/  BHND_PCI_LOCK (struct bhnd_pci_softc*) ; 
 int /*<<< orphan*/  BHND_PCI_UNLOCK (struct bhnd_pci_softc*) ; 
 int bhnd_pcie_mdio_cmd_read (struct bhnd_pci_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bhnd_pcie_mdio_disable (struct bhnd_pci_softc*) ; 
 int /*<<< orphan*/  bhnd_pcie_mdio_enable (struct bhnd_pci_softc*) ; 

int
bhnd_pcie_mdio_read(struct bhnd_pci_softc *sc, int phy, int reg)
{
	uint32_t	cmd;
	uint16_t	val;
	int		error;

	/* Enable MDIO access */
	BHND_PCI_LOCK(sc);
	bhnd_pcie_mdio_enable(sc);

	/* Issue the read */
	cmd = BHND_PCIE_MDIODATA_ADDR(phy, reg);
	error = bhnd_pcie_mdio_cmd_read(sc, cmd, &val);

	/* Disable MDIO access */
	bhnd_pcie_mdio_disable(sc);
	BHND_PCI_UNLOCK(sc);

	if (error)
		return (~0U);

	return (val);
}