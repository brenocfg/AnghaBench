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
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
struct axi_dmac_desc {int cyclic; int /*<<< orphan*/  vdesc; int /*<<< orphan*/  sg; } ;
struct axi_dmac_chan {int direction; int /*<<< orphan*/  vchan; int /*<<< orphan*/  max_length; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (size_t,int /*<<< orphan*/ ) ; 
 struct axi_dmac_desc* axi_dmac_alloc_desc (unsigned int) ; 
 int /*<<< orphan*/  axi_dmac_check_addr (struct axi_dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axi_dmac_check_len (struct axi_dmac_chan*,size_t) ; 
 int /*<<< orphan*/  axi_dmac_fill_linear_sg (struct axi_dmac_chan*,int,int /*<<< orphan*/ ,unsigned int,size_t,int /*<<< orphan*/ ) ; 
 struct axi_dmac_chan* to_axi_dmac_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *axi_dmac_prep_dma_cyclic(
	struct dma_chan *c, dma_addr_t buf_addr, size_t buf_len,
	size_t period_len, enum dma_transfer_direction direction,
	unsigned long flags)
{
	struct axi_dmac_chan *chan = to_axi_dmac_chan(c);
	struct axi_dmac_desc *desc;
	unsigned int num_periods, num_segments;

	if (direction != chan->direction)
		return NULL;

	if (!axi_dmac_check_len(chan, buf_len) ||
	    !axi_dmac_check_addr(chan, buf_addr))
		return NULL;

	if (period_len == 0 || buf_len % period_len)
		return NULL;

	num_periods = buf_len / period_len;
	num_segments = DIV_ROUND_UP(period_len, chan->max_length);

	desc = axi_dmac_alloc_desc(num_periods * num_segments);
	if (!desc)
		return NULL;

	axi_dmac_fill_linear_sg(chan, direction, buf_addr, num_periods,
		period_len, desc->sg);

	desc->cyclic = true;

	return vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
}