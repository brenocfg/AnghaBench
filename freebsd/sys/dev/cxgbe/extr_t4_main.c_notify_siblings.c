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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int PCI_FUNCMAX ; 
 int /*<<< orphan*/  T4_ATTACH_CHILD (int /*<<< orphan*/ *) ; 
 int T4_DETACH_CHILD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_is_attached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pci_find_dbsf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_get_domain (int /*<<< orphan*/ *) ; 
 int pci_get_function (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
notify_siblings(device_t dev, int detaching)
{
	device_t sibling;
	int error, i;

	error = 0;
	for (i = 0; i < PCI_FUNCMAX; i++) {
		if (i == pci_get_function(dev))
			continue;
		sibling = pci_find_dbsf(pci_get_domain(dev), pci_get_bus(dev),
		    pci_get_slot(dev), i);
		if (sibling == NULL || !device_is_attached(sibling))
			continue;
		if (detaching)
			error = T4_DETACH_CHILD(sibling);
		else
			(void)T4_ATTACH_CHILD(sibling);
		if (error)
			break;
	}
	return (error);
}