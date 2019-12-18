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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct pci_dev {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct pci_dev* get_pci_dev (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct pci_dev *pnv_pci_get_gpu_dev(struct pci_dev *npdev)
{
	struct device_node *dn;
	struct pci_dev *gpdev;

	if (WARN_ON(!npdev))
		return NULL;

	if (WARN_ON(!npdev->dev.of_node))
		return NULL;

	/* Get assoicated PCI device */
	dn = of_parse_phandle(npdev->dev.of_node, "ibm,gpu", 0);
	if (!dn)
		return NULL;

	gpdev = get_pci_dev(dn);
	of_node_put(dn);

	return gpdev;
}