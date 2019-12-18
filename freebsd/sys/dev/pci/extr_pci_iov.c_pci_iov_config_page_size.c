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
typedef  int uint32_t ;
struct pci_devinfo {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int IOV_READ (struct pci_devinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IOV_WRITE (struct pci_devinfo*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  PCIR_SRIOV_PAGE_CAP ; 
 int /*<<< orphan*/  PCIR_SRIOV_PAGE_SIZE ; 
 scalar_t__ PCI_SRIOV_BASE_PAGE_SHIFT ; 

__attribute__((used)) static int
pci_iov_config_page_size(struct pci_devinfo *dinfo)
{
	uint32_t page_cap, page_size;

	page_cap = IOV_READ(dinfo, PCIR_SRIOV_PAGE_CAP, 4);

	/*
	 * If the system page size is less than the smallest SR-IOV page size
	 * then round up to the smallest SR-IOV page size.
	 */
	if (PAGE_SHIFT < PCI_SRIOV_BASE_PAGE_SHIFT)
		page_size = (1 << 0);
	else
		page_size = (1 << (PAGE_SHIFT - PCI_SRIOV_BASE_PAGE_SHIFT));

	/* Check that the device supports the system page size. */
	if (!(page_size & page_cap))
		return (ENXIO);

	IOV_WRITE(dinfo, PCIR_SRIOV_PAGE_SIZE, page_size, 4);
	return (0);
}