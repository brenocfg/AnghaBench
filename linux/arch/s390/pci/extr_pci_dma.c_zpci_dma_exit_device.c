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
struct zpci_dev {scalar_t__ next_bit; int /*<<< orphan*/ * lazy_bitmap; int /*<<< orphan*/ * iommu_bitmap; int /*<<< orphan*/ * dma_table; int /*<<< orphan*/  s390_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cleanup_tables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 scalar_t__ zpci_unregister_ioat (struct zpci_dev*,int /*<<< orphan*/ ) ; 

void zpci_dma_exit_device(struct zpci_dev *zdev)
{
	/*
	 * At this point, if the device is part of an IOMMU domain, this would
	 * be a strong hint towards a bug in the IOMMU API (common) code and/or
	 * simultaneous access via IOMMU and DMA API. So let's issue a warning.
	 */
	WARN_ON(zdev->s390_domain);

	if (zpci_unregister_ioat(zdev, 0))
		return;

	dma_cleanup_tables(zdev->dma_table);
	zdev->dma_table = NULL;
	vfree(zdev->iommu_bitmap);
	zdev->iommu_bitmap = NULL;
	vfree(zdev->lazy_bitmap);
	zdev->lazy_bitmap = NULL;

	zdev->next_bit = 0;
}