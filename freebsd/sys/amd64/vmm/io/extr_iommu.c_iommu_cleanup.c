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

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOMMU_CLEANUP () ; 
 int /*<<< orphan*/  IOMMU_DESTROY_DOMAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOMMU_DISABLE () ; 
 int /*<<< orphan*/ * add_tag ; 
 int /*<<< orphan*/ * delete_tag ; 
 int /*<<< orphan*/  host_domain ; 
 int /*<<< orphan*/  pci_add_device ; 
 int /*<<< orphan*/  pci_delete_device ; 

void
iommu_cleanup(void)
{

	if (add_tag != NULL) {
		EVENTHANDLER_DEREGISTER(pci_add_device, add_tag);
		add_tag = NULL;
	}
	if (delete_tag != NULL) {
		EVENTHANDLER_DEREGISTER(pci_delete_device, delete_tag);
		delete_tag = NULL;
	}
	IOMMU_DISABLE();
	IOMMU_DESTROY_DOMAIN(host_domain);
	IOMMU_CLEANUP();
}