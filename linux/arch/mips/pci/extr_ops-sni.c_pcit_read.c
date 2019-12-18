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
typedef  int u32 ;
struct pci_bus {scalar_t__ number; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIMT_CONFIG_DATA ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inl (int) ; 
 int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int) ; 
 int pcit_set_config_address (scalar_t__,unsigned int,int) ; 

__attribute__((used)) static int pcit_read(struct pci_bus *bus, unsigned int devfn, int reg,
		      int size, u32 * val)
{
	int res;

	/*
	 * on bus 0 we need to check, whether there is a device answering
	 * for the devfn by doing a config write and checking the result. If
	 * we don't do it, we will get a data bus error
	 */
	if (bus->number == 0) {
		pcit_set_config_address(0, 0, 0x68);
		outl(inl(0xcfc) | 0xc0000000, 0xcfc);
		if ((res = pcit_set_config_address(0, devfn, 0)))
			return res;
		outl(0xffffffff, 0xcfc);
		pcit_set_config_address(0, 0, 0x68);
		if (inl(0xcfc) & 0x100000)
			return PCIBIOS_DEVICE_NOT_FOUND;
	}
	if ((res = pcit_set_config_address(bus->number, devfn, reg)))
		return res;

	switch (size) {
	case 1:
		*val = inb(PCIMT_CONFIG_DATA + (reg & 3));
		break;
	case 2:
		*val = inw(PCIMT_CONFIG_DATA + (reg & 2));
		break;
	case 4:
		*val = inl(PCIMT_CONFIG_DATA);
		break;
	}
	return 0;
}