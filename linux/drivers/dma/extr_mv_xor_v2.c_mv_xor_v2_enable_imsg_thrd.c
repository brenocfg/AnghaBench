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
struct mv_xor_v2_device {scalar_t__ dma_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV_XOR_V2_DMA_IMSG_THRD_MASK ; 
 scalar_t__ MV_XOR_V2_DMA_IMSG_THRD_OFF ; 
 int /*<<< orphan*/  MV_XOR_V2_DMA_IMSG_TIMER_EN ; 
 int /*<<< orphan*/  MV_XOR_V2_DMA_IMSG_TIMER_THRD_MASK ; 
 scalar_t__ MV_XOR_V2_DMA_IMSG_TMOT ; 
 int /*<<< orphan*/  MV_XOR_V2_DONE_IMSG_THRD ; 
 int /*<<< orphan*/  MV_XOR_V2_TIMER_THRD ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline
void mv_xor_v2_enable_imsg_thrd(struct mv_xor_v2_device *xor_dev)
{
	u32 reg;

	/* Configure threshold of number of descriptors, and enable timer */
	reg = readl(xor_dev->dma_base + MV_XOR_V2_DMA_IMSG_THRD_OFF);
	reg &= ~MV_XOR_V2_DMA_IMSG_THRD_MASK;
	reg |= MV_XOR_V2_DONE_IMSG_THRD;
	reg |= MV_XOR_V2_DMA_IMSG_TIMER_EN;
	writel(reg, xor_dev->dma_base + MV_XOR_V2_DMA_IMSG_THRD_OFF);

	/* Configure Timer Threshold */
	reg = readl(xor_dev->dma_base + MV_XOR_V2_DMA_IMSG_TMOT);
	reg &= ~MV_XOR_V2_DMA_IMSG_TIMER_THRD_MASK;
	reg |= MV_XOR_V2_TIMER_THRD;
	writel(reg, xor_dev->dma_base + MV_XOR_V2_DMA_IMSG_TMOT);
}