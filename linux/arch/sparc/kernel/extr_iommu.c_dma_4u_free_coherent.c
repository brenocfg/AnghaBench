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
struct iommu {int /*<<< orphan*/  tbl; } ;
struct TYPE_2__ {struct iommu* iommu; } ;
struct device {TYPE_1__ archdata; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_ERROR_CODE ; 
 unsigned long IO_PAGE_ALIGN (size_t) ; 
 unsigned long IO_PAGE_SHIFT ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned long) ; 
 unsigned long get_order (size_t) ; 
 int /*<<< orphan*/  iommu_tbl_range_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_4u_free_coherent(struct device *dev, size_t size,
				 void *cpu, dma_addr_t dvma,
				 unsigned long attrs)
{
	struct iommu *iommu;
	unsigned long order, npages;

	npages = IO_PAGE_ALIGN(size) >> IO_PAGE_SHIFT;
	iommu = dev->archdata.iommu;

	iommu_tbl_range_free(&iommu->tbl, dvma, npages, IOMMU_ERROR_CODE);

	order = get_order(size);
	if (order < 10)
		free_pages((unsigned long)cpu, order);
}