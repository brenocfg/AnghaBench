#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_bus {TYPE_1__** resource; scalar_t__ self; } ;
struct TYPE_2__ {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ _IO_BASE ; 
 int /*<<< orphan*/  pci_bus_to_host (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_name (scalar_t__) ; 
 int pcibios_map_phb_io_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,...) ; 

int pcibios_map_io_space(struct pci_bus *bus)
{
	WARN_ON(bus == NULL);

	/* If this not a PHB, nothing to do, page tables still exist and
	 * thus HPTEs will be faulted in when needed
	 */
	if (bus->self) {
		pr_debug("IO mapping for PCI-PCI bridge %s\n",
			 pci_name(bus->self));
		pr_debug("  virt=0x%016llx...0x%016llx\n",
			 bus->resource[0]->start + _IO_BASE,
			 bus->resource[0]->end + _IO_BASE);
		return 0;
	}

	return pcibios_map_phb_io_space(pci_bus_to_host(bus));
}