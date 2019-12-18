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
struct hisi_acc_hw_sgl {scalar_t__ entry_length_in_sgl; scalar_t__ entry_sum_in_sgl; scalar_t__ entry_sum_in_chain; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_nents (struct scatterlist*) ; 

void hisi_acc_sg_buf_unmap(struct device *dev, struct scatterlist *sgl,
			   struct hisi_acc_hw_sgl *hw_sgl)
{
	dma_unmap_sg(dev, sgl, sg_nents(sgl), DMA_BIDIRECTIONAL);

	hw_sgl->entry_sum_in_chain = 0;
	hw_sgl->entry_sum_in_sgl = 0;
	hw_sgl->entry_length_in_sgl = 0;
}