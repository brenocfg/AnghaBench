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
struct bhnd_pci_softc {int quirks; } ;

/* Variables and functions */
 int BHND_PCIE_MDIODATA_ADDR (int,int) ; 
 int BHND_PCIE_MDIODATA_DATA_MASK ; 
 int BHND_PCIE_PHYADDR_SD ; 
 int BHND_PCIE_SD_ADDREXT ; 
 int /*<<< orphan*/  BHND_PCI_LOCK (struct bhnd_pci_softc*) ; 
 int BHND_PCI_QUIRK_SD_C22_EXTADDR ; 
 int /*<<< orphan*/  BHND_PCI_UNLOCK (struct bhnd_pci_softc*) ; 
 int MDIO_DEVADDR_NONE ; 
 int bhnd_pcie_mdio_cmd_write (struct bhnd_pci_softc*,int) ; 
 int /*<<< orphan*/  bhnd_pcie_mdio_disable (struct bhnd_pci_softc*) ; 
 int /*<<< orphan*/  bhnd_pcie_mdio_enable (struct bhnd_pci_softc*) ; 
 int bhnd_pcie_mdio_write (struct bhnd_pci_softc*,int,int,int) ; 

int
bhnd_pcie_mdio_write_ext(struct bhnd_pci_softc *sc, int phy, int devaddr,
    int reg, int val)
{	
	uint32_t	cmd;
	int		error;

	if (devaddr == MDIO_DEVADDR_NONE)
		return (bhnd_pcie_mdio_write(sc, phy, reg, val));

	/* Extended register access is only supported for the SerDes device,
	 * using the non-standard C22 extended address mechanism */
	if (!(sc->quirks & BHND_PCI_QUIRK_SD_C22_EXTADDR) ||
	    phy != BHND_PCIE_PHYADDR_SD)
	{
		return (~0U);	
	}

	/* Enable MDIO access */
	BHND_PCI_LOCK(sc);
	bhnd_pcie_mdio_enable(sc);

	/* Write the block address to the address extension register */
	cmd = BHND_PCIE_MDIODATA_ADDR(phy, BHND_PCIE_SD_ADDREXT) | devaddr;
	if ((error = bhnd_pcie_mdio_cmd_write(sc, cmd)))
		goto cleanup;

	/* Issue the write */
	cmd = BHND_PCIE_MDIODATA_ADDR(phy, reg) |
	    (val & BHND_PCIE_MDIODATA_DATA_MASK);
	error = bhnd_pcie_mdio_cmd_write(sc, cmd);

cleanup:
	bhnd_pcie_mdio_disable(sc);
	BHND_PCI_UNLOCK(sc);

	return (error);
}