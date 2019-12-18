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
struct dma_channel {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PVR2_DMA_LMMODE0 ; 
 int /*<<< orphan*/  PVR2_DMA_MODE ; 
 scalar_t__ __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_request_dma(struct dma_channel *chan)
{
	if (__raw_readl(PVR2_DMA_MODE) != 0)
		return -EBUSY;

	__raw_writel(0, PVR2_DMA_LMMODE0);

	return 0;
}