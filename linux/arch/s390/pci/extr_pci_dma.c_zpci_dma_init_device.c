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
typedef  int /*<<< orphan*/  u64 ;
struct zpci_dev {int iommu_size; int iommu_pages; int /*<<< orphan*/ * dma_table; int /*<<< orphan*/ * lazy_bitmap; int /*<<< orphan*/ * iommu_bitmap; scalar_t__ end_dma; scalar_t__ start_dma; int /*<<< orphan*/  dma_table_lock; int /*<<< orphan*/  iommu_bitmap_lock; int /*<<< orphan*/  s390_domain; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ PAGE_ALIGN (scalar_t__) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ ZPCI_TABLE_SIZE_RT ; 
 int /*<<< orphan*/ * dma_alloc_cpu_table () ; 
 int /*<<< orphan*/  dma_free_cpu_table (int /*<<< orphan*/ *) ; 
 scalar_t__ high_memory ; 
 int min3 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  s390_iommu_strict ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 void* vzalloc (int) ; 
 int zpci_register_ioat (struct zpci_dev*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

int zpci_dma_init_device(struct zpci_dev *zdev)
{
	int rc;

	/*
	 * At this point, if the device is part of an IOMMU domain, this would
	 * be a strong hint towards a bug in the IOMMU API (common) code and/or
	 * simultaneous access via IOMMU and DMA API. So let's issue a warning.
	 */
	WARN_ON(zdev->s390_domain);

	spin_lock_init(&zdev->iommu_bitmap_lock);
	spin_lock_init(&zdev->dma_table_lock);

	zdev->dma_table = dma_alloc_cpu_table();
	if (!zdev->dma_table) {
		rc = -ENOMEM;
		goto out;
	}

	/*
	 * Restrict the iommu bitmap size to the minimum of the following:
	 * - main memory size
	 * - 3-level pagetable address limit minus start_dma offset
	 * - DMA address range allowed by the hardware (clp query pci fn)
	 *
	 * Also set zdev->end_dma to the actual end address of the usable
	 * range, instead of the theoretical maximum as reported by hardware.
	 */
	zdev->start_dma = PAGE_ALIGN(zdev->start_dma);
	zdev->iommu_size = min3((u64) high_memory,
				ZPCI_TABLE_SIZE_RT - zdev->start_dma,
				zdev->end_dma - zdev->start_dma + 1);
	zdev->end_dma = zdev->start_dma + zdev->iommu_size - 1;
	zdev->iommu_pages = zdev->iommu_size >> PAGE_SHIFT;
	zdev->iommu_bitmap = vzalloc(zdev->iommu_pages / 8);
	if (!zdev->iommu_bitmap) {
		rc = -ENOMEM;
		goto free_dma_table;
	}
	if (!s390_iommu_strict) {
		zdev->lazy_bitmap = vzalloc(zdev->iommu_pages / 8);
		if (!zdev->lazy_bitmap) {
			rc = -ENOMEM;
			goto free_bitmap;
		}

	}
	rc = zpci_register_ioat(zdev, 0, zdev->start_dma, zdev->end_dma,
				(u64) zdev->dma_table);
	if (rc)
		goto free_bitmap;

	return 0;
free_bitmap:
	vfree(zdev->iommu_bitmap);
	zdev->iommu_bitmap = NULL;
	vfree(zdev->lazy_bitmap);
	zdev->lazy_bitmap = NULL;
free_dma_table:
	dma_free_cpu_table(zdev->dma_table);
	zdev->dma_table = NULL;
out:
	return rc;
}