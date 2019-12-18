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
struct pci_controller {struct device_node* dn; int /*<<< orphan*/  controller_ops; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ SPIDER_PCI_REG_BASE ; 
 int /*<<< orphan*/  cell_pci_controller_ops ; 
 int /*<<< orphan*/  iowa_register_bus (struct pci_controller*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_name_eq (struct device_node*,char*) ; 
 int rtas_setup_phb (struct pci_controller*) ; 
 int /*<<< orphan*/  spiderpci_iowa_init ; 
 int /*<<< orphan*/  spiderpci_ops ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int cell_setup_phb(struct pci_controller *phb)
{
	const char *model;
	struct device_node *np;

	int rc = rtas_setup_phb(phb);
	if (rc)
		return rc;

	phb->controller_ops = cell_pci_controller_ops;

	np = phb->dn;
	model = of_get_property(np, "model", NULL);
	if (model == NULL || !of_node_name_eq(np, "pci"))
		return 0;

	/* Setup workarounds for spider */
	if (strcmp(model, "Spider"))
		return 0;

	iowa_register_bus(phb, &spiderpci_ops, &spiderpci_iowa_init,
				  (void *)SPIDER_PCI_REG_BASE);
	return 0;
}