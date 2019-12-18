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
typedef  int /*<<< orphan*/  u16 ;
struct pci_pbm_info {int dummy; } ;
struct pci_bus {unsigned char number; struct pci_pbm_info* sysdata; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  pci_config_read16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_config_read32 (int*,int*) ; 
 int /*<<< orphan*/  pci_config_read8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int* sun4u_config_mkaddr (struct pci_pbm_info*,unsigned char,unsigned int,int) ; 
 int sun4u_read_pci_cfg_host (struct pci_pbm_info*,unsigned char,unsigned int,int,int,int*) ; 

__attribute__((used)) static int sun4u_read_pci_cfg(struct pci_bus *bus_dev, unsigned int devfn,
			      int where, int size, u32 *value)
{
	struct pci_pbm_info *pbm = bus_dev->sysdata;
	unsigned char bus = bus_dev->number;
	u32 *addr;
	u16 tmp16;
	u8 tmp8;

	switch (size) {
	case 1:
		*value = 0xff;
		break;
	case 2:
		*value = 0xffff;
		break;
	case 4:
		*value = 0xffffffff;
		break;
	}

	if (!bus_dev->number && !PCI_SLOT(devfn))
		return sun4u_read_pci_cfg_host(pbm, bus, devfn, where,
					       size, value);

	addr = sun4u_config_mkaddr(pbm, bus, devfn, where);
	if (!addr)
		return PCIBIOS_SUCCESSFUL;

	switch (size) {
	case 1:
		pci_config_read8((u8 *)addr, &tmp8);
		*value = (u32) tmp8;
		break;

	case 2:
		if (where & 0x01) {
			printk("pci_read_config_word: misaligned reg [%x]\n",
			       where);
			return PCIBIOS_SUCCESSFUL;
		}
		pci_config_read16((u16 *)addr, &tmp16);
		*value = (u32) tmp16;
		break;

	case 4:
		if (where & 0x03) {
			printk("pci_read_config_dword: misaligned reg [%x]\n",
			       where);
			return PCIBIOS_SUCCESSFUL;
		}
		pci_config_read32(addr, value);
		break;
	}
	return PCIBIOS_SUCCESSFUL;
}