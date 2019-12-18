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
struct TYPE_5__ {int /*<<< orphan*/  data_width; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_width; } ;
struct stedma40_chan_cfg {TYPE_2__ dst_info; TYPE_1__ src_info; } ;
struct scatterlist {int dummy; } ;
struct TYPE_6__ {unsigned long flags; int /*<<< orphan*/  tx_submit; } ;
struct d40_desc {scalar_t__ lli_len; TYPE_3__ txd; scalar_t__ lli_current; } ;
struct d40_chan {int /*<<< orphan*/  chan; struct stedma40_chan_cfg dma_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan_err (struct d40_chan*,char*) ; 
 int /*<<< orphan*/  d40_desc_free (struct d40_chan*,struct d40_desc*) ; 
 struct d40_desc* d40_desc_get (struct d40_chan*) ; 
 int d40_pool_lli_alloc (struct d40_chan*,struct d40_desc*,scalar_t__) ; 
 scalar_t__ d40_sg_2_dmalen (struct scatterlist*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d40_tx_submit ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct d40_desc *
d40_prep_desc(struct d40_chan *chan, struct scatterlist *sg,
	      unsigned int sg_len, unsigned long dma_flags)
{
	struct stedma40_chan_cfg *cfg;
	struct d40_desc *desc;
	int ret;

	desc = d40_desc_get(chan);
	if (!desc)
		return NULL;

	cfg = &chan->dma_cfg;
	desc->lli_len = d40_sg_2_dmalen(sg, sg_len, cfg->src_info.data_width,
					cfg->dst_info.data_width);
	if (desc->lli_len < 0) {
		chan_err(chan, "Unaligned size\n");
		goto free_desc;
	}

	ret = d40_pool_lli_alloc(chan, desc, desc->lli_len);
	if (ret < 0) {
		chan_err(chan, "Could not allocate lli\n");
		goto free_desc;
	}

	desc->lli_current = 0;
	desc->txd.flags = dma_flags;
	desc->txd.tx_submit = d40_tx_submit;

	dma_async_tx_descriptor_init(&desc->txd, &chan->chan);

	return desc;
 free_desc:
	d40_desc_free(chan, desc);
	return NULL;
}