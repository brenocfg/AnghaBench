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
typedef  int /*<<< orphan*/  u64 ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {scalar_t__ (* iommu_bypass_supported ) (struct pci_dev*,int /*<<< orphan*/ ) ;} ;
struct pci_controller {TYPE_1__ controller_ops; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static bool dma_iommu_bypass_supported(struct device *dev, u64 mask)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct pci_controller *phb = pci_bus_to_host(pdev->bus);

	return phb->controller_ops.iommu_bypass_supported &&
		phb->controller_ops.iommu_bypass_supported(pdev, mask);
}