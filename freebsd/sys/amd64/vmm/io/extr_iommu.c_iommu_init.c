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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/ * devclass_t ;

/* Variables and functions */
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOMMU_CLEANUP () ; 
 int /*<<< orphan*/ * IOMMU_CREATE_DOMAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOMMU_ENABLE () ; 
 int IOMMU_INIT () ; 
 int PCI_BUSMAX ; 
 int PCI_FUNCMAX ; 
 int PCI_SLOTMAX ; 
 void* add_tag ; 
 void* delete_tag ; 
 int /*<<< orphan*/ * devclass_find (char*) ; 
 int /*<<< orphan*/ * device_get_devclass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * host_domain ; 
 int /*<<< orphan*/  iommu_add_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iommu_avail ; 
 int /*<<< orphan*/  iommu_create_mapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_enable ; 
 int /*<<< orphan*/  iommu_ops_amd ; 
 int /*<<< orphan*/  iommu_ops_intel ; 
 int /*<<< orphan*/  iommu_pci_add ; 
 int /*<<< orphan*/  iommu_pci_delete ; 
 int /*<<< orphan*/ * ops ; 
 int /*<<< orphan*/  pci_add_device ; 
 int /*<<< orphan*/  pci_delete_device ; 
 int /*<<< orphan*/ * pci_find_dbsf (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  pci_get_rid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ vmm_is_amd () ; 
 scalar_t__ vmm_is_intel () ; 
 int /*<<< orphan*/  vmm_mem_maxaddr () ; 

__attribute__((used)) static void
iommu_init(void)
{
	int error, bus, slot, func;
	vm_paddr_t maxaddr;
	devclass_t dc;
	device_t dev;

	if (!iommu_enable)
		return;

	if (vmm_is_intel())
		ops = &iommu_ops_intel;
	else if (vmm_is_amd())
		ops = &iommu_ops_amd;
	else
		ops = NULL;

	error = IOMMU_INIT();
	if (error)
		return;

	iommu_avail = 1;

	/*
	 * Create a domain for the devices owned by the host
	 */
	maxaddr = vmm_mem_maxaddr();
	host_domain = IOMMU_CREATE_DOMAIN(maxaddr);
	if (host_domain == NULL) {
		printf("iommu_init: unable to create a host domain");
		IOMMU_CLEANUP();
		ops = NULL;
		iommu_avail = 0;
		return;
	}

	/*
	 * Create 1:1 mappings from '0' to 'maxaddr' for devices assigned to
	 * the host
	 */
	iommu_create_mapping(host_domain, 0, 0, maxaddr);

	add_tag = EVENTHANDLER_REGISTER(pci_add_device, iommu_pci_add, NULL, 0);
	delete_tag = EVENTHANDLER_REGISTER(pci_delete_device, iommu_pci_delete,
	    NULL, 0);
	dc = devclass_find("ppt");
	for (bus = 0; bus <= PCI_BUSMAX; bus++) {
		for (slot = 0; slot <= PCI_SLOTMAX; slot++) {
			for (func = 0; func <= PCI_FUNCMAX; func++) {
				dev = pci_find_dbsf(0, bus, slot, func);
				if (dev == NULL)
					continue;

				/* Skip passthrough devices. */
				if (dc != NULL &&
				    device_get_devclass(dev) == dc)
					continue;

				/*
				 * Everything else belongs to the host
				 * domain.
				 */
				iommu_add_device(host_domain,
				    pci_get_rid(dev));
			}
		}
	}
	IOMMU_ENABLE();

}