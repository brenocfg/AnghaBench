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
struct iommu_ops {int dummy; } ;
struct TYPE_2__ {int dma_coherent; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CPU_V7M ; 
 int CR_M ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_nommu_dma_ops ; 
 scalar_t__ cacheid ; 
 int get_cr () ; 
 int /*<<< orphan*/  set_dma_ops (struct device*,int /*<<< orphan*/ *) ; 

void arch_setup_dma_ops(struct device *dev, u64 dma_base, u64 size,
			const struct iommu_ops *iommu, bool coherent)
{
	if (IS_ENABLED(CONFIG_CPU_V7M)) {
		/*
		 * Cache support for v7m is optional, so can be treated as
		 * coherent if no cache has been detected. Note that it is not
		 * enough to check if MPU is in use or not since in absense of
		 * MPU system memory map is used.
		 */
		dev->archdata.dma_coherent = (cacheid) ? coherent : true;
	} else {
		/*
		 * Assume coherent DMA in case MMU/MPU has not been set up.
		 */
		dev->archdata.dma_coherent = (get_cr() & CR_M) ? coherent : true;
	}

	if (!dev->archdata.dma_coherent)
		set_dma_ops(dev, &arm_nommu_dma_ops);
}