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
struct pci_sys_data {unsigned char busnr; } ;

/* Variables and functions */
 unsigned int PCI_FUNC (unsigned int) ; 
 unsigned int PCI_SLOT (unsigned int) ; 

__attribute__((used)) static unsigned oxnas_pcie_cfg_to_offset(
	struct pci_sys_data *sys,
	unsigned char bus_number,
	unsigned int devfn,
	int where)
{
	unsigned int function = PCI_FUNC(devfn);
	unsigned int slot = PCI_SLOT(devfn);
	unsigned char bus_number_offset;

	bus_number_offset = bus_number - sys->busnr;

	/*
	 * We'll assume for now that the offset, function, slot, bus encoding
	 * should map onto linear, contiguous addresses in PCIe config space,
	 * albeit that the majority will be unused as only slot 0 is valid for
	 * any PCIe bus and most devices have only function 0
	 *
	 * Could be that PCIe in fact works by not encoding the slot number into
	 * the config space address as it's known that only slot 0 is valid.
	 * We'll have to experiment if/when we get a PCIe switch connected to
	 * the PCIe host
	 */
	return (bus_number_offset << 20) | (slot << 15) | (function << 12) |
		(where & ~3);
}