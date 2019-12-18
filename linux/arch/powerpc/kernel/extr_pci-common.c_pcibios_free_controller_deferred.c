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
struct pci_host_bridge {scalar_t__ release_data; } ;
struct pci_controller {int /*<<< orphan*/  is_dynamic; int /*<<< orphan*/  global_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcibios_free_controller (struct pci_controller*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pcibios_free_controller_deferred(struct pci_host_bridge *bridge)
{
	struct pci_controller *phb = (struct pci_controller *)
					 bridge->release_data;

	pr_debug("domain %d, dynamic %d\n", phb->global_number, phb->is_dynamic);

	pcibios_free_controller(phb);
}