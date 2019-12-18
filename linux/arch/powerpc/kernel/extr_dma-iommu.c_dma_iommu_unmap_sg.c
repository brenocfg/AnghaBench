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
 int /*<<< orphan*/  dma_direct_unmap_sg (struct device*,struct scatterlist*,int,int,unsigned long) ; 
 int /*<<< orphan*/  dma_iommu_map_bypass (struct device*,unsigned long) ; 
 int /*<<< orphan*/  get_iommu_table_base (struct device*) ; 
 int /*<<< orphan*/  ppc_iommu_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int,unsigned long) ; 

__attribute__((used)) static void dma_iommu_unmap_sg(struct device *dev, struct scatterlist *sglist,
		int nelems, enum dma_data_direction direction,
		unsigned long attrs)
{
	if (!dma_iommu_map_bypass(dev, attrs))
		ppc_iommu_unmap_sg(get_iommu_table_base(dev), sglist, nelems,
			   direction, attrs);
	else
		dma_direct_unmap_sg(dev, sglist, nelems, direction, attrs);
}