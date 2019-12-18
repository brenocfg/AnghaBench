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
typedef  int u32 ;
struct zynqmp_dma_chan {scalar_t__ regs; } ;

/* Variables and functions */
 int ZYNQMP_DMA_BYTE_CNT_OVRFL ; 
 scalar_t__ ZYNQMP_DMA_IRQ_DST_ACCT ; 
 int ZYNQMP_DMA_IRQ_DST_ACCT_ERR ; 
 scalar_t__ ZYNQMP_DMA_IRQ_SRC_ACCT ; 
 int ZYNQMP_DMA_IRQ_SRC_ACCT_ERR ; 
 scalar_t__ ZYNQMP_DMA_TOTAL_BYTE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void zynqmp_dma_handle_ovfl_int(struct zynqmp_dma_chan *chan, u32 status)
{
	if (status & ZYNQMP_DMA_BYTE_CNT_OVRFL)
		writel(0, chan->regs + ZYNQMP_DMA_TOTAL_BYTE);
	if (status & ZYNQMP_DMA_IRQ_DST_ACCT_ERR)
		readl(chan->regs + ZYNQMP_DMA_IRQ_DST_ACCT);
	if (status & ZYNQMP_DMA_IRQ_SRC_ACCT_ERR)
		readl(chan->regs + ZYNQMP_DMA_IRQ_SRC_ACCT);
}