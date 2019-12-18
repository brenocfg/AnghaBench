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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ dma_offset; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 scalar_t__ OF_BAD_ADDR ; 
 scalar_t__ cell_dma_nommu_offset ; 
 int /*<<< orphan*/  cell_get_iommu_table (struct device*) ; 
 scalar_t__ cell_iommu_enabled ; 
 scalar_t__ cell_iommu_get_fixed_address (struct device*) ; 
 scalar_t__ dma_iommu_fixed_base ; 
 int /*<<< orphan*/  set_iommu_table_base (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cell_dma_dev_setup(struct device *dev)
{
	if (cell_iommu_enabled) {
		u64 addr = cell_iommu_get_fixed_address(dev);

		if (addr != OF_BAD_ADDR)
			dev->archdata.dma_offset = addr + dma_iommu_fixed_base;
		set_iommu_table_base(dev, cell_get_iommu_table(dev));
	} else {
		dev->archdata.dma_offset = cell_dma_nommu_offset;
	}
}