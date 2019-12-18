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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int PCI_ROM_RESOURCE ; 
 int pci_create_attr (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_remove_resource_files (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int) ; 

int pci_create_resource_files(struct pci_dev *pdev)
{
	int i;
	int retval;

	/* Expose the PCI resources from this device as files */
	for (i = 0; i < PCI_ROM_RESOURCE; i++) {

		/* skip empty resources */
		if (!pci_resource_len(pdev, i))
			continue;

		retval = pci_create_attr(pdev, i);
		if (retval) {
			pci_remove_resource_files(pdev);
			return retval;
		}
	}
	return 0;
}