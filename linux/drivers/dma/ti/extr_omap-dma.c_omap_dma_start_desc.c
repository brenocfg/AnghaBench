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
struct virt_dma_desc {int /*<<< orphan*/  tx; int /*<<< orphan*/  node; } ;
struct omap_desc {int ccr; scalar_t__ dir; int dev_addr; int ei; int fi; int csdp; int clnk_ctrl; } ;
struct omap_chan {scalar_t__ sgidx; struct omap_desc* desc; int /*<<< orphan*/  vc; } ;

/* Variables and functions */
 unsigned int CCR ; 
 unsigned int CCR2 ; 
 unsigned int CDEI ; 
 unsigned int CDFI ; 
 unsigned int CDSA ; 
 unsigned int CLNK_CTRL ; 
 unsigned int CSDP ; 
 unsigned int CSEI ; 
 unsigned int CSFI ; 
 unsigned int CSSA ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_MEM ; 
 scalar_t__ dma_omap1 () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  omap_dma_chan_write (struct omap_chan*,unsigned int,int) ; 
 int /*<<< orphan*/  omap_dma_start_sg (struct omap_chan*,struct omap_desc*) ; 
 struct omap_desc* to_omap_dma_desc (int /*<<< orphan*/ *) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap_dma_start_desc(struct omap_chan *c)
{
	struct virt_dma_desc *vd = vchan_next_desc(&c->vc);
	struct omap_desc *d;
	unsigned cxsa, cxei, cxfi;

	if (!vd) {
		c->desc = NULL;
		return;
	}

	list_del(&vd->node);

	c->desc = d = to_omap_dma_desc(&vd->tx);
	c->sgidx = 0;

	/*
	 * This provides the necessary barrier to ensure data held in
	 * DMA coherent memory is visible to the DMA engine prior to
	 * the transfer starting.
	 */
	mb();

	omap_dma_chan_write(c, CCR, d->ccr);
	if (dma_omap1())
		omap_dma_chan_write(c, CCR2, d->ccr >> 16);

	if (d->dir == DMA_DEV_TO_MEM || d->dir == DMA_MEM_TO_MEM) {
		cxsa = CSSA;
		cxei = CSEI;
		cxfi = CSFI;
	} else {
		cxsa = CDSA;
		cxei = CDEI;
		cxfi = CDFI;
	}

	omap_dma_chan_write(c, cxsa, d->dev_addr);
	omap_dma_chan_write(c, cxei, d->ei);
	omap_dma_chan_write(c, cxfi, d->fi);
	omap_dma_chan_write(c, CSDP, d->csdp);
	omap_dma_chan_write(c, CLNK_CTRL, d->clnk_ctrl);

	omap_dma_start_sg(c, d);
}