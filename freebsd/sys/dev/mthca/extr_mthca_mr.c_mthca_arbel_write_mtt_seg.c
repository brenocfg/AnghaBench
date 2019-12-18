#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct mthca_mtt {scalar_t__ first_seg; } ;
struct TYPE_5__ {int mtt_seg_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtt_table; } ;
struct mthca_dev {TYPE_3__* pdev; TYPE_2__ limits; TYPE_1__ mr_table; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int MTHCA_MTT_FLAG_PRESENT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mthca_table_find (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mthca_arbel_write_mtt_seg(struct mthca_dev *dev,
				      struct mthca_mtt *mtt, int start_index,
				      u64 *buffer_list, int list_len)
{
	__be64 *mtts;
	dma_addr_t dma_handle;
	int i;
	int s = start_index * sizeof (u64);

	/* For Arbel, all MTTs must fit in the same page. */
	BUG_ON(s / PAGE_SIZE != (s + list_len * sizeof(u64) - 1) / PAGE_SIZE);
	/* Require full segments */
	BUG_ON(s % dev->limits.mtt_seg_size);

	mtts = mthca_table_find(dev->mr_table.mtt_table, mtt->first_seg +
				s / dev->limits.mtt_seg_size, &dma_handle);

	BUG_ON(!mtts);

	dma_sync_single_for_cpu(&dev->pdev->dev, dma_handle,
				list_len * sizeof (u64), DMA_TO_DEVICE);

	for (i = 0; i < list_len; ++i)
		mtts[i] = cpu_to_be64(buffer_list[i] | MTHCA_MTT_FLAG_PRESENT);

	dma_sync_single_for_device(&dev->pdev->dev, dma_handle,
				   list_len * sizeof (u64), DMA_TO_DEVICE);
}