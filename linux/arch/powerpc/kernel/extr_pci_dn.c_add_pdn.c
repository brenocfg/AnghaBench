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
struct pci_dn {int dummy; } ;
struct pci_controller {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct pci_dn* pci_add_device_node_info (struct pci_controller*,struct device_node*) ; 

__attribute__((used)) static void *add_pdn(struct device_node *dn, void *data)
{
	struct pci_controller *hose = data;
	struct pci_dn *pdn;

	pdn = pci_add_device_node_info(hose, dn);
	if (!pdn)
		return ERR_PTR(-ENOMEM);

	return NULL;
}