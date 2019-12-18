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
struct pci_io {int pi_width; int pi_data; int /*<<< orphan*/  pi_reg; int /*<<< orphan*/  pi_sel; } ;
struct pci_conf {int pc_hdr; int /*<<< orphan*/  pc_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIOCREAD ; 
 int /*<<< orphan*/  PCIOCWRITE ; 
 int /*<<< orphan*/  PCI_CFG_ROM_BAR ; 
 int PCI_ROM_ADDR_MASK ; 
 int ioctl (int,int /*<<< orphan*/ ,struct pci_io*) ; 

__attribute__((used)) static uint32_t
pci_testrombar(int pci_fd, struct pci_conf *dev)
{
	struct pci_io	 io;
	uint32_t	 romsize;

	romsize = 0;

	/*
	 * Only attempt to discover ROMs on Header Type 0x00 devices.
	 */
	if (dev->pc_hdr != 0x00)
		return romsize;

	/*
	 * Activate ROM BAR
	 */
	io.pi_sel = dev->pc_sel;
	io.pi_reg = PCI_CFG_ROM_BAR;
	io.pi_width = 4;
	io.pi_data = 0xFFFFFFFF;
	if (ioctl(pci_fd, PCIOCWRITE, &io) == -1)
		return romsize;

	/*
	 * Read back ROM BAR and compare with mask
	 */
	if (ioctl(pci_fd, PCIOCREAD, &io) == -1)
		return 0;

	/*
	 * Calculate ROM aperture if one was set.
	 */
	if (io.pi_data & PCI_ROM_ADDR_MASK)
		romsize = -(io.pi_data & PCI_ROM_ADDR_MASK);

	/*
	 * Disable the ROM BAR when done.
	 */
	io.pi_data = 0;
	if (ioctl(pci_fd, PCIOCWRITE, &io) == -1)
		return 0;

	return romsize;
}