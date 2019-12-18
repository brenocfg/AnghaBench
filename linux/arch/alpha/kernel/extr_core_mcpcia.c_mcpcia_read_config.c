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
typedef  unsigned long u32 ;
struct pci_controller {int dummy; } ;
struct pci_bus {struct pci_controller* sysdata; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 unsigned long __kernel_extbl (unsigned long,int) ; 
 unsigned long __kernel_extwl (unsigned long,int) ; 
 unsigned long conf_read (unsigned long,unsigned char,struct pci_controller*) ; 
 scalar_t__ mk_conf_addr (struct pci_bus*,unsigned int,int,struct pci_controller*,unsigned long*,unsigned char*) ; 

__attribute__((used)) static int
mcpcia_read_config(struct pci_bus *bus, unsigned int devfn, int where,
		   int size, u32 *value)
{
	struct pci_controller *hose = bus->sysdata;
	unsigned long addr, w;
	unsigned char type1;

	if (mk_conf_addr(bus, devfn, where, hose, &addr, &type1))
		return PCIBIOS_DEVICE_NOT_FOUND;

	addr |= (size - 1) * 8;
	w = conf_read(addr, type1, hose);
	switch (size) {
	case 1:
		*value = __kernel_extbl(w, where & 3);
		break;
	case 2:
		*value = __kernel_extwl(w, where & 3);
		break;
	case 4:
		*value = w;
		break;
	}
	return PCIBIOS_SUCCESSFUL;
}