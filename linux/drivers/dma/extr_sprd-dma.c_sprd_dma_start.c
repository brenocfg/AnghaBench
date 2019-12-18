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
struct virt_dma_desc {int /*<<< orphan*/  node; } ;
struct sprd_dma_chn {scalar_t__ chn_mode; scalar_t__ dev_id; int /*<<< orphan*/  cur_desc; int /*<<< orphan*/  vc; } ;

/* Variables and functions */
 scalar_t__ SPRD_DMA_DST_CHN0 ; 
 scalar_t__ SPRD_DMA_DST_CHN1 ; 
 scalar_t__ SPRD_DMA_SOFTWARE_UID ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprd_dma_enable_chn (struct sprd_dma_chn*) ; 
 scalar_t__ sprd_dma_set_2stage_config (struct sprd_dma_chn*) ; 
 int /*<<< orphan*/  sprd_dma_set_chn_config (struct sprd_dma_chn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_dma_set_uid (struct sprd_dma_chn*) ; 
 int /*<<< orphan*/  sprd_dma_soft_request (struct sprd_dma_chn*) ; 
 int /*<<< orphan*/  to_sprd_dma_desc (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sprd_dma_start(struct sprd_dma_chn *schan)
{
	struct virt_dma_desc *vd = vchan_next_desc(&schan->vc);

	if (!vd)
		return;

	list_del(&vd->node);
	schan->cur_desc = to_sprd_dma_desc(vd);

	/*
	 * Set 2-stage configuration if the channel starts one 2-stage
	 * transfer.
	 */
	if (schan->chn_mode && sprd_dma_set_2stage_config(schan))
		return;

	/*
	 * Copy the DMA configuration from DMA descriptor to this hardware
	 * channel.
	 */
	sprd_dma_set_chn_config(schan, schan->cur_desc);
	sprd_dma_set_uid(schan);
	sprd_dma_enable_chn(schan);

	if (schan->dev_id == SPRD_DMA_SOFTWARE_UID &&
	    schan->chn_mode != SPRD_DMA_DST_CHN0 &&
	    schan->chn_mode != SPRD_DMA_DST_CHN1)
		sprd_dma_soft_request(schan);
}