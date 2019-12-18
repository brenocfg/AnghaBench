#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zx_dma_desc_sw {size_t size; int /*<<< orphan*/  vd; int /*<<< orphan*/  desc_hw_lli; TYPE_2__* desc_hw; } ;
struct zx_dma_chan {int cyclic; size_t dev_addr; int ccfg; int /*<<< orphan*/  vc; } ;
struct dma_chan {TYPE_1__* device; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  size_t dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  lli; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMA_DEV_TO_MEM ; 
 size_t DMA_MAX_SIZE ; 
 int DMA_MEM_TO_DEV ; 
 int ZX_IRQ_ENABLE_ALL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct zx_dma_chan* to_zx_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 struct zx_dma_desc_sw* zx_alloc_desc_resource (int,struct dma_chan*) ; 
 int /*<<< orphan*/  zx_dma_fill_desc (struct zx_dma_desc_sw*,size_t,size_t,size_t,int /*<<< orphan*/ ,int) ; 
 scalar_t__ zx_pre_config (struct zx_dma_chan*,int) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *zx_dma_prep_dma_cyclic(
		struct dma_chan *chan, dma_addr_t dma_addr, size_t buf_len,
		size_t period_len, enum dma_transfer_direction dir,
		unsigned long flags)
{
	struct zx_dma_chan *c = to_zx_chan(chan);
	struct zx_dma_desc_sw *ds;
	dma_addr_t src = 0, dst = 0;
	int num_periods = buf_len / period_len;
	int buf = 0, num = 0;

	if (period_len > DMA_MAX_SIZE) {
		dev_err(chan->device->dev, "maximum period size exceeded\n");
		return NULL;
	}

	if (zx_pre_config(c, dir))
		return NULL;

	ds = zx_alloc_desc_resource(num_periods, chan);
	if (!ds)
		return NULL;
	c->cyclic = 1;

	while (buf < buf_len) {
		if (dir == DMA_MEM_TO_DEV) {
			src = dma_addr;
			dst = c->dev_addr;
		} else if (dir == DMA_DEV_TO_MEM) {
			src = c->dev_addr;
			dst = dma_addr;
		}
		zx_dma_fill_desc(ds, dst, src, period_len, num++,
				 c->ccfg | ZX_IRQ_ENABLE_ALL);
		dma_addr += period_len;
		buf += period_len;
	}

	ds->desc_hw[num - 1].lli = ds->desc_hw_lli;
	ds->size = buf_len;
	return vchan_tx_prep(&c->vc, &ds->vd, flags);
}