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
typedef  size_t u32 ;
struct stm32_dma_sg_req {size_t len; } ;
struct stm32_dma_desc {int num_sgs; TYPE_2__* sg_req; } ;
struct stm32_dma_chan {size_t next_sg; size_t mem_burst; size_t mem_width; TYPE_1__* desc; } ;
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_3__ {size_t num_sgs; int /*<<< orphan*/  cyclic; struct stm32_dma_sg_req* sg_req; } ;

/* Variables and functions */
 size_t stm32_dma_get_remaining_bytes (struct stm32_dma_chan*) ; 
 int /*<<< orphan*/  stm32_dma_is_current_sg (struct stm32_dma_chan*) ; 

__attribute__((used)) static size_t stm32_dma_desc_residue(struct stm32_dma_chan *chan,
				     struct stm32_dma_desc *desc,
				     u32 next_sg)
{
	u32 modulo, burst_size;
	u32 residue;
	u32 n_sg = next_sg;
	struct stm32_dma_sg_req *sg_req = &chan->desc->sg_req[chan->next_sg];
	int i;

	/*
	 * Calculate the residue means compute the descriptors
	 * information:
	 * - the sg_req currently transferred
	 * - the Hardware remaining position in this sg (NDTR bits field).
	 *
	 * A race condition may occur if DMA is running in cyclic or double
	 * buffer mode, since the DMA register are automatically reloaded at end
	 * of period transfer. The hardware may have switched to the next
	 * transfer (CT bit updated) just before the position (SxNDTR reg) is
	 * read.
	 * In this case the SxNDTR reg could (or not) correspond to the new
	 * transfer position, and not the expected one.
	 * The strategy implemented in the stm32 driver is to:
	 *  - read the SxNDTR register
	 *  - crosscheck that hardware is still in current transfer.
	 * In case of switch, we can assume that the DMA is at the beginning of
	 * the next transfer. So we approximate the residue in consequence, by
	 * pointing on the beginning of next transfer.
	 *
	 * This race condition doesn't apply for none cyclic mode, as double
	 * buffer is not used. In such situation registers are updated by the
	 * software.
	 */

	residue = stm32_dma_get_remaining_bytes(chan);

	if (!stm32_dma_is_current_sg(chan)) {
		n_sg++;
		if (n_sg == chan->desc->num_sgs)
			n_sg = 0;
		residue = sg_req->len;
	}

	/*
	 * In cyclic mode, for the last period, residue = remaining bytes
	 * from NDTR,
	 * else for all other periods in cyclic mode, and in sg mode,
	 * residue = remaining bytes from NDTR + remaining
	 * periods/sg to be transferred
	 */
	if (!chan->desc->cyclic || n_sg != 0)
		for (i = n_sg; i < desc->num_sgs; i++)
			residue += desc->sg_req[i].len;

	if (!chan->mem_burst)
		return residue;

	burst_size = chan->mem_burst * chan->mem_width;
	modulo = residue % burst_size;
	if (modulo)
		residue = residue - modulo + burst_size;

	return residue;
}