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
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  dma_direct_sync_sg_for_cpu (struct device*,struct scatterlist*,int,int) ; 
 scalar_t__ dma_iommu_alloc_bypass (struct device*) ; 

extern void dma_iommu_sync_sg_for_cpu(struct device *dev,
		struct scatterlist *sgl, int nents, enum dma_data_direction dir)
{
	if (dma_iommu_alloc_bypass(dev))
		dma_direct_sync_sg_for_cpu(dev, sgl, nents, dir);
}