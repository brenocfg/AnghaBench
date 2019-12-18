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
 int /*<<< orphan*/  BHND_PCIE_ASSERT (struct bhnd_pci_softc*) ; 
 int /*<<< orphan*/  BHND_PCIE_IND_ADDR ; 
 int /*<<< orphan*/  BHND_PCIE_IND_DATA ; 
 int /*<<< orphan*/  BHND_PCI_LOCK (struct bhnd_pci_softc*) ; 
 int /*<<< orphan*/  BHND_PCI_READ_4 (struct bhnd_pci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PCI_UNLOCK (struct bhnd_pci_softc*) ; 
 int /*<<< orphan*/  BHND_PCI_WRITE_4 (struct bhnd_pci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t
bhnd_pcie_read_proto_reg(struct bhnd_pci_softc *sc, uint32_t addr)
{
	uint32_t val;

	BHND_PCIE_ASSERT(sc);

	BHND_PCI_LOCK(sc);
	BHND_PCI_WRITE_4(sc, BHND_PCIE_IND_ADDR, addr);
	val = BHND_PCI_READ_4(sc, BHND_PCIE_IND_DATA);
	BHND_PCI_UNLOCK(sc);

	return (val);
}