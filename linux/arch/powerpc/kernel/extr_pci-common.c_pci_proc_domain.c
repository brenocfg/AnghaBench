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
struct pci_controller {scalar_t__ global_number; } ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_COMPAT_DOMAIN_0 ; 
 int /*<<< orphan*/  PCI_ENABLE_PROC_DOMAINS ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 scalar_t__ pci_has_flag (int /*<<< orphan*/ ) ; 

int pci_proc_domain(struct pci_bus *bus)
{
	struct pci_controller *hose = pci_bus_to_host(bus);

	if (!pci_has_flag(PCI_ENABLE_PROC_DOMAINS))
		return 0;
	if (pci_has_flag(PCI_COMPAT_DOMAIN_0))
		return hose->global_number != 0;
	return 1;
}