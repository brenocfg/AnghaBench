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
struct xilinx_dma_chan {scalar_t__ ext_addr; } ;
struct xilinx_axidma_desc_hw {scalar_t__ buf_addr; int /*<<< orphan*/  buf_addr_msb; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static inline void xilinx_axidma_buf(struct xilinx_dma_chan *chan,
				     struct xilinx_axidma_desc_hw *hw,
				     dma_addr_t buf_addr, size_t sg_used,
				     size_t period_len)
{
	if (chan->ext_addr) {
		hw->buf_addr = lower_32_bits(buf_addr + sg_used + period_len);
		hw->buf_addr_msb = upper_32_bits(buf_addr + sg_used +
						 period_len);
	} else {
		hw->buf_addr = buf_addr + sg_used + period_len;
	}
}