#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pci_pbm_info {int /*<<< orphan*/  devhandle; } ;
struct iommu_map_table {unsigned long table_map_base; } ;
struct iommu {struct iommu_map_table tbl; struct atu* atu; } ;
struct TYPE_3__ {struct pci_pbm_info* host_controller; struct iommu* iommu; } ;
struct device {TYPE_1__ archdata; } ;
struct atu {TYPE_2__* iotsb; struct iommu_map_table tbl; } ;
typedef  unsigned long dma_addr_t ;
struct TYPE_4__ {unsigned long iotsb_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_ERROR_CODE ; 
 unsigned long IO_PAGE_ALIGN (size_t) ; 
 unsigned long IO_PAGE_SHIFT ; 
 int /*<<< orphan*/  dma_4v_iommu_demap (struct device*,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned long) ; 
 unsigned long get_order (size_t) ; 
 int /*<<< orphan*/  iommu_tbl_range_free (struct iommu_map_table*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_use_atu (struct iommu*,unsigned long) ; 

__attribute__((used)) static void dma_4v_free_coherent(struct device *dev, size_t size, void *cpu,
				 dma_addr_t dvma, unsigned long attrs)
{
	struct pci_pbm_info *pbm;
	struct iommu *iommu;
	struct atu *atu;
	struct iommu_map_table *tbl;
	unsigned long order, npages, entry;
	unsigned long iotsb_num;
	u32 devhandle;

	npages = IO_PAGE_ALIGN(size) >> IO_PAGE_SHIFT;
	iommu = dev->archdata.iommu;
	pbm = dev->archdata.host_controller;
	atu = iommu->atu;
	devhandle = pbm->devhandle;

	if (!iommu_use_atu(iommu, dvma)) {
		tbl = &iommu->tbl;
		iotsb_num = 0; /* we don't care for legacy iommu */
	} else {
		tbl = &atu->tbl;
		iotsb_num = atu->iotsb->iotsb_num;
	}
	entry = ((dvma - tbl->table_map_base) >> IO_PAGE_SHIFT);
	dma_4v_iommu_demap(dev, devhandle, dvma, iotsb_num, entry, npages);
	iommu_tbl_range_free(tbl, dvma, npages, IOMMU_ERROR_CODE);
	order = get_order(size);
	if (order < 10)
		free_pages((unsigned long)cpu, order);
}