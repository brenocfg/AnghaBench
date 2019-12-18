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
struct TYPE_2__ {scalar_t__ iommu_bypass; } ;
struct device {int /*<<< orphan*/  coherent_dma_mask; TYPE_1__ archdata; } ;

/* Variables and functions */
 scalar_t__ dma_direct_supported (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_fixed_is_weak ; 

__attribute__((used)) static inline bool dma_iommu_alloc_bypass(struct device *dev)
{
	return dev->archdata.iommu_bypass && !iommu_fixed_is_weak &&
		dma_direct_supported(dev, dev->coherent_dma_mask);
}