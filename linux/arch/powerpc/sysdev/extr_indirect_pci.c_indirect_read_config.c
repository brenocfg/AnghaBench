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
typedef  int /*<<< orphan*/  u32 ;
struct pci_controller {int dummy; } ;
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int __indirect_read_config (struct pci_controller*,int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ *) ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 

int indirect_read_config(struct pci_bus *bus, unsigned int devfn,
			 int offset, int len, u32 *val)
{
	struct pci_controller *hose = pci_bus_to_host(bus);

	return __indirect_read_config(hose, bus->number, devfn, offset, len,
				      val);
}