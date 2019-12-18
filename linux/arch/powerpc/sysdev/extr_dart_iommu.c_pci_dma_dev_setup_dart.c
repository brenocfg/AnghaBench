#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dma_offset; } ;
struct TYPE_5__ {TYPE_1__ archdata; } ;
struct pci_dev {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DART_U4_BYPASS_BASE ; 
 scalar_t__ dart_device_on_pcie (TYPE_2__*) ; 
 scalar_t__ dart_is_u4 ; 
 int /*<<< orphan*/  iommu_table_dart ; 
 int /*<<< orphan*/  set_iommu_table_base (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci_dma_dev_setup_dart(struct pci_dev *dev)
{
	if (dart_is_u4 && dart_device_on_pcie(&dev->dev))
		dev->dev.archdata.dma_offset = DART_U4_BYPASS_BASE;
	set_iommu_table_base(&dev->dev, &iommu_table_dart);
}