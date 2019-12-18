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
struct msgdma_extended_desc {size_t len; int control; scalar_t__ burst_seq_num; int /*<<< orphan*/  stride; void* write_addr_hi; void* read_addr_hi; void* write_addr_lo; void* read_addr_lo; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int MSGDMA_DESC_CTL_END_ON_LEN ; 
 int MSGDMA_DESC_CTL_GO ; 
 int MSGDMA_DESC_CTL_TR_ERR_IRQ ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msgdma_desc_config(struct msgdma_extended_desc *desc,
			       dma_addr_t dst, dma_addr_t src, size_t len,
			       u32 stride)
{
	/* Set lower 32bits of src & dst addresses in the descriptor */
	desc->read_addr_lo = lower_32_bits(src);
	desc->write_addr_lo = lower_32_bits(dst);

	/* Set upper 32bits of src & dst addresses in the descriptor */
	desc->read_addr_hi = upper_32_bits(src);
	desc->write_addr_hi = upper_32_bits(dst);

	desc->len = len;
	desc->stride = stride;
	desc->burst_seq_num = 0;	/* 0 will result in max burst length */

	/*
	 * Don't set interrupt on xfer end yet, this will be done later
	 * for the "last" descriptor
	 */
	desc->control = MSGDMA_DESC_CTL_TR_ERR_IRQ | MSGDMA_DESC_CTL_GO |
		MSGDMA_DESC_CTL_END_ON_LEN;
}