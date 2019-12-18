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
struct mic_dma_chan {scalar_t__ owner; scalar_t__ issued; int /*<<< orphan*/  last_tail; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 scalar_t__ MIC_DMA_CHAN_MIC ; 
 int /*<<< orphan*/  MIC_DMA_REG_DCHERRMSK ; 
 int /*<<< orphan*/  MIC_DMA_REG_DTPR ; 
 int /*<<< orphan*/  mic_dma_chan_mask_intr (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_chan_set_desc_ring (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_chan_set_owner (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_chan_unmask_intr (struct mic_dma_chan*) ; 
 int mic_dma_check_chan (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_disable_chan (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_enable_chan (struct mic_dma_chan*) ; 
 int /*<<< orphan*/  mic_dma_read_reg (struct mic_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mic_dma_write_reg (struct mic_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mic_dma_chan_setup(struct mic_dma_chan *ch)
{
	if (MIC_DMA_CHAN_MIC == ch->owner)
		mic_dma_chan_set_owner(ch);
	mic_dma_disable_chan(ch);
	mic_dma_chan_mask_intr(ch);
	mic_dma_write_reg(ch, MIC_DMA_REG_DCHERRMSK, 0);
	mic_dma_chan_set_desc_ring(ch);
	ch->last_tail = mic_dma_read_reg(ch, MIC_DMA_REG_DTPR);
	ch->head = ch->last_tail;
	ch->issued = 0;
	mic_dma_chan_unmask_intr(ch);
	mic_dma_enable_chan(ch);
	return mic_dma_check_chan(ch);
}