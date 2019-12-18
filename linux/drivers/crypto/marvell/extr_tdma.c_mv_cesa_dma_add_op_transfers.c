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
typedef  int /*<<< orphan*/  u32 ;
struct mv_cesa_tdma_chain {int dummy; } ;
struct mv_cesa_sg_dma_iter {scalar_t__ dir; scalar_t__ op_offset; scalar_t__ offset; int /*<<< orphan*/  sg; } ;
struct mv_cesa_dma_iter {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ CESA_SA_DATA_SRAM_OFFSET ; 
 int /*<<< orphan*/  CESA_TDMA_DST_IN_SRAM ; 
 int /*<<< orphan*/  CESA_TDMA_SRC_IN_SRAM ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int mv_cesa_dma_add_data_transfer (struct mv_cesa_tdma_chain*,scalar_t__,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mv_cesa_req_dma_iter_next_transfer (struct mv_cesa_dma_iter*,struct mv_cesa_sg_dma_iter*,unsigned int) ; 
 unsigned int mv_cesa_req_dma_iter_transfer_len (struct mv_cesa_dma_iter*,struct mv_cesa_sg_dma_iter*) ; 
 scalar_t__ sg_dma_address (int /*<<< orphan*/ ) ; 

int mv_cesa_dma_add_op_transfers(struct mv_cesa_tdma_chain *chain,
				 struct mv_cesa_dma_iter *dma_iter,
				 struct mv_cesa_sg_dma_iter *sgiter,
				 gfp_t gfp_flags)
{
	u32 flags = sgiter->dir == DMA_TO_DEVICE ?
		    CESA_TDMA_DST_IN_SRAM : CESA_TDMA_SRC_IN_SRAM;
	unsigned int len;

	do {
		dma_addr_t dst, src;
		int ret;

		len = mv_cesa_req_dma_iter_transfer_len(dma_iter, sgiter);
		if (sgiter->dir == DMA_TO_DEVICE) {
			dst = CESA_SA_DATA_SRAM_OFFSET + sgiter->op_offset;
			src = sg_dma_address(sgiter->sg) + sgiter->offset;
		} else {
			dst = sg_dma_address(sgiter->sg) + sgiter->offset;
			src = CESA_SA_DATA_SRAM_OFFSET + sgiter->op_offset;
		}

		ret = mv_cesa_dma_add_data_transfer(chain, dst, src, len,
						    flags, gfp_flags);
		if (ret)
			return ret;

	} while (mv_cesa_req_dma_iter_next_transfer(dma_iter, sgiter, len));

	return 0;
}