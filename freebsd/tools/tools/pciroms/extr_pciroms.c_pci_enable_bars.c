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
typedef  scalar_t__ uint16_t ;
struct pci_io {int pi_width; int pi_data; int /*<<< orphan*/  pi_reg; int /*<<< orphan*/  pi_sel; } ;
struct pci_conf {int pc_hdr; int /*<<< orphan*/  pc_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIOCREAD ; 
 int /*<<< orphan*/  PCIOCWRITE ; 
 int /*<<< orphan*/  PCI_CFG_CMD ; 
 int /*<<< orphan*/  PCI_CFG_ROM_BAR ; 
 int PCI_CMD_MEM_SPACE ; 
 int PCI_ROM_ACTIVATE ; 
 int base_addr ; 
 int ioctl (int,int /*<<< orphan*/ ,struct pci_io*) ; 

__attribute__((used)) static int
pci_enable_bars(int pci_fd, struct pci_conf *dev, uint16_t *oldcmd)
{
	struct pci_io io;

	/* Don't grok bridges. */
	if (dev->pc_hdr != 0x00)
		return -1;

	/* Save command register. */
	io.pi_sel = dev->pc_sel;
	io.pi_reg = PCI_CFG_CMD;
	io.pi_width = 2;
	if (ioctl(pci_fd, PCIOCREAD, &io) == -1)
		return -1;
	*oldcmd = (uint16_t)io.pi_data;

	io.pi_data |= PCI_CMD_MEM_SPACE;
	if (ioctl(pci_fd, PCIOCWRITE, &io) == -1)
		return -1;

	/*
	 * Activate ROM BAR and map at the specified base address.
	 */
	io.pi_sel = dev->pc_sel;
	io.pi_reg = PCI_CFG_ROM_BAR;
	io.pi_width = 4;
	io.pi_data = (base_addr | PCI_ROM_ACTIVATE);
	if (ioctl(pci_fd, PCIOCWRITE, &io) == -1)
		return -1;

	return 0;
}