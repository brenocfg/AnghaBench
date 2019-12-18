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
typedef  int u64 ;
struct iommu_table {scalar_t__ it_index; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 int H_NOT_ENOUGH_RESOURCES ; 
 int TCE_PCI_READ ; 
 int TCE_PCI_WRITE ; 
 int TCE_RPN_MASK ; 
 int TCE_RPN_SHIFT ; 
 int TCE_SHIFT ; 
 int __pa (unsigned long) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int plpar_tce_put (int,int,int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  tce_free_pSeriesLP (struct iommu_table*,long,long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tce_build_pSeriesLP(struct iommu_table *tbl, long tcenum,
				long npages, unsigned long uaddr,
				enum dma_data_direction direction,
				unsigned long attrs)
{
	u64 rc = 0;
	u64 proto_tce, tce;
	u64 rpn;
	int ret = 0;
	long tcenum_start = tcenum, npages_start = npages;

	rpn = __pa(uaddr) >> TCE_SHIFT;
	proto_tce = TCE_PCI_READ;
	if (direction != DMA_TO_DEVICE)
		proto_tce |= TCE_PCI_WRITE;

	while (npages--) {
		tce = proto_tce | (rpn & TCE_RPN_MASK) << TCE_RPN_SHIFT;
		rc = plpar_tce_put((u64)tbl->it_index, (u64)tcenum << 12, tce);

		if (unlikely(rc == H_NOT_ENOUGH_RESOURCES)) {
			ret = (int)rc;
			tce_free_pSeriesLP(tbl, tcenum_start,
			                   (npages_start - (npages + 1)));
			break;
		}

		if (rc && printk_ratelimit()) {
			printk("tce_build_pSeriesLP: plpar_tce_put failed. rc=%lld\n", rc);
			printk("\tindex   = 0x%llx\n", (u64)tbl->it_index);
			printk("\ttcenum  = 0x%llx\n", (u64)tcenum);
			printk("\ttce val = 0x%llx\n", tce );
			dump_stack();
		}

		tcenum++;
		rpn++;
	}
	return ret;
}