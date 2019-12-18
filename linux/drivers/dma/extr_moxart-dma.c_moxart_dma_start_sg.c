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
struct moxart_sg {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct moxart_desc {scalar_t__ dma_dir; int /*<<< orphan*/  dev_addr; struct moxart_sg* sg; } ;
struct moxart_chan {struct moxart_desc* desc; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  moxart_dma_set_params (struct moxart_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moxart_set_transfer_params (struct moxart_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moxart_start_dma (struct moxart_chan*) ; 

__attribute__((used)) static void moxart_dma_start_sg(struct moxart_chan *ch, unsigned int idx)
{
	struct moxart_desc *d = ch->desc;
	struct moxart_sg *sg = ch->desc->sg + idx;

	if (ch->desc->dma_dir == DMA_MEM_TO_DEV)
		moxart_dma_set_params(ch, sg->addr, d->dev_addr);
	else if (ch->desc->dma_dir == DMA_DEV_TO_MEM)
		moxart_dma_set_params(ch, d->dev_addr, sg->addr);

	moxart_set_transfer_params(ch, sg->len);

	moxart_start_dma(ch);
}