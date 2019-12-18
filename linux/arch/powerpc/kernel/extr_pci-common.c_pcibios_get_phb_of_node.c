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
struct pci_controller {int /*<<< orphan*/  dn; } ;
struct pci_bus {struct pci_controller* sysdata; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 

struct device_node *pcibios_get_phb_of_node(struct pci_bus *bus)
{
	struct pci_controller *hose = bus->sysdata;

	return of_node_get(hose->dn);
}