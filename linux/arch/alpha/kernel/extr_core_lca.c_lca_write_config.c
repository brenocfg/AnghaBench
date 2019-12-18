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
struct pci_bus {int dummy; } ;

/* Variables and functions */
 unsigned long LCA_CONF ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  conf_write (unsigned long,int) ; 
 scalar_t__ mk_conf_addr (struct pci_bus*,unsigned int,int,unsigned long*) ; 

__attribute__((used)) static int 
lca_write_config(struct pci_bus *bus, unsigned int devfn, int where, int size,
		 u32 value)
{
	unsigned long addr, pci_addr;
	long mask;

	if (mk_conf_addr(bus, devfn, where, &pci_addr))
		return PCIBIOS_DEVICE_NOT_FOUND;

	mask = (size - 1) * 8;
	addr = (pci_addr << 5) + mask + LCA_CONF;
	conf_write(addr, value << ((where & 3) * 8));
	return PCIBIOS_SUCCESSFUL;
}