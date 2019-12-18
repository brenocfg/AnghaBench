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
struct dma_channel {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 scalar_t__ CHCR ; 
 int CHCR_DE ; 
 scalar_t__ TCR ; 
 int __raw_readl (scalar_t__) ; 
 int calc_xmit_shift (struct dma_channel*) ; 
 scalar_t__ dma_base_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_dmac_get_dma_residue(struct dma_channel *chan)
{
	if (!(__raw_readl(dma_base_addr(chan->chan) + CHCR) & CHCR_DE))
		return 0;

	return __raw_readl(dma_base_addr(chan->chan) + TCR)
		 << calc_xmit_shift(chan);
}