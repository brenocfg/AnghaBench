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
struct virt_dma_chan {int dummy; } ;
struct uniphier_mdmac_desc {unsigned int sg_len; int dir; int /*<<< orphan*/  vd; struct scatterlist* sgl; } ;
struct scatterlist {int dummy; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  is_slave_direction (int) ; 
 struct uniphier_mdmac_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct virt_dma_chan* to_virt_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (struct virt_dma_chan*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
uniphier_mdmac_prep_slave_sg(struct dma_chan *chan, struct scatterlist *sgl,
			     unsigned int sg_len,
			     enum dma_transfer_direction direction,
			     unsigned long flags, void *context)
{
	struct virt_dma_chan *vc = to_virt_chan(chan);
	struct uniphier_mdmac_desc *md;

	if (!is_slave_direction(direction))
		return NULL;

	md = kzalloc(sizeof(*md), GFP_NOWAIT);
	if (!md)
		return NULL;

	md->sgl = sgl;
	md->sg_len = sg_len;
	md->dir = direction;

	return vchan_tx_prep(vc, &md->vd, flags);
}