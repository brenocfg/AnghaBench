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
struct mlx4_ib_mr {int /*<<< orphan*/  page_map_size; int /*<<< orphan*/  page_map; scalar_t__ npages; } ;
struct ib_mr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ib_sg_to_pages (struct ib_mr*,struct scatterlist*,int,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_set_page ; 
 struct mlx4_ib_mr* to_mmr (struct ib_mr*) ; 

int mlx4_ib_map_mr_sg(struct ib_mr *ibmr, struct scatterlist *sg, int sg_nents,
		      unsigned int *sg_offset)
{
	struct mlx4_ib_mr *mr = to_mmr(ibmr);
	int rc;

	mr->npages = 0;

	ib_dma_sync_single_for_cpu(ibmr->device, mr->page_map,
				   mr->page_map_size, DMA_TO_DEVICE);

	rc = ib_sg_to_pages(ibmr, sg, sg_nents, sg_offset, mlx4_set_page);

	ib_dma_sync_single_for_device(ibmr->device, mr->page_map,
				      mr->page_map_size, DMA_TO_DEVICE);

	return rc;
}