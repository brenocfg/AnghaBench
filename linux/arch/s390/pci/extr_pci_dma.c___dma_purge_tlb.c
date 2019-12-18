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
struct zpci_dev {int /*<<< orphan*/  iommu_bitmap_lock; int /*<<< orphan*/  iommu_pages; int /*<<< orphan*/  lazy_bitmap; int /*<<< orphan*/  iommu_bitmap; scalar_t__ fh; int /*<<< orphan*/  tlb_refresh; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_ALIGN (size_t) ; 
 int ZPCI_PTE_VALID ; 
 int ZPCI_PTE_VALID_MASK ; 
 int /*<<< orphan*/  bitmap_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_iommu_strict ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ zpci_refresh_global (struct zpci_dev*) ; 
 int zpci_refresh_trans (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __dma_purge_tlb(struct zpci_dev *zdev, dma_addr_t dma_addr,
			   size_t size, int flags)
{
	unsigned long irqflags;
	int ret;

	/*
	 * With zdev->tlb_refresh == 0, rpcit is not required to establish new
	 * translations when previously invalid translation-table entries are
	 * validated. With lazy unmap, rpcit is skipped for previously valid
	 * entries, but a global rpcit is then required before any address can
	 * be re-used, i.e. after each iommu bitmap wrap-around.
	 */
	if ((flags & ZPCI_PTE_VALID_MASK) == ZPCI_PTE_VALID) {
		if (!zdev->tlb_refresh)
			return 0;
	} else {
		if (!s390_iommu_strict)
			return 0;
	}

	ret = zpci_refresh_trans((u64) zdev->fh << 32, dma_addr,
				 PAGE_ALIGN(size));
	if (ret == -ENOMEM && !s390_iommu_strict) {
		/* enable the hypervisor to free some resources */
		if (zpci_refresh_global(zdev))
			goto out;

		spin_lock_irqsave(&zdev->iommu_bitmap_lock, irqflags);
		bitmap_andnot(zdev->iommu_bitmap, zdev->iommu_bitmap,
			      zdev->lazy_bitmap, zdev->iommu_pages);
		bitmap_zero(zdev->lazy_bitmap, zdev->iommu_pages);
		spin_unlock_irqrestore(&zdev->iommu_bitmap_lock, irqflags);
		ret = 0;
	}
out:
	return ret;
}