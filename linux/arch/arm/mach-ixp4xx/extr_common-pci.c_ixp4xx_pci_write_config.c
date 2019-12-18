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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int NP_CMD_CONFIGWRITE ; 
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_FUNC (unsigned int) ; 
 int /*<<< orphan*/  PCI_SLOT (unsigned int) ; 
 int byte_lane_enable_bits (int,int) ; 
 int ixp4xx_config_addr (int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ ixp4xx_pci_write (int,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixp4xx_pci_write_config(struct pci_bus *bus,  unsigned int devfn, int where, int size, u32 value)
{
	u32 n, byte_enables, addr, data;
	u8 bus_num = bus->number;

	pr_debug("write_config_byte %#x to %d size %d dev %d:%d:%d\n", value, where,
		size, bus_num, PCI_SLOT(devfn), PCI_FUNC(devfn));

	n = where % 4;
	byte_enables = byte_lane_enable_bits(n, size);
	if (byte_enables == 0xffffffff)
		return PCIBIOS_BAD_REGISTER_NUMBER;

	addr = ixp4xx_config_addr(bus_num, devfn, where);
	data = value << (8*n);
	if (ixp4xx_pci_write(addr, byte_enables | NP_CMD_CONFIGWRITE, data))
		return PCIBIOS_DEVICE_NOT_FOUND;

	return PCIBIOS_SUCCESSFUL;
}