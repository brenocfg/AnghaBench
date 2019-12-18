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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  host_domain ; 
 int /*<<< orphan*/  iommu_add_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_rid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iommu_pci_add(void *arg, device_t dev)
{

	/* Add new devices to the host domain. */
	iommu_add_device(host_domain, pci_get_rid(dev));
}