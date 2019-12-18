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
struct fsldma_chan {int feature; } ;

/* Variables and functions */
#define  FSL_DMA_IP_83XX 129 
#define  FSL_DMA_IP_85XX 128 
 int FSL_DMA_IP_MASK ; 
 int FSL_DMA_MR_BWC ; 
 int FSL_DMA_MR_EIE ; 
 int FSL_DMA_MR_EOLNIE ; 
 int FSL_DMA_MR_EOTIE ; 
 int FSL_DMA_MR_PRC_RM ; 
 int /*<<< orphan*/  set_mr (struct fsldma_chan*,int) ; 

__attribute__((used)) static void dma_init(struct fsldma_chan *chan)
{
	/* Reset the channel */
	set_mr(chan, 0);

	switch (chan->feature & FSL_DMA_IP_MASK) {
	case FSL_DMA_IP_85XX:
		/* Set the channel to below modes:
		 * EIE - Error interrupt enable
		 * EOLNIE - End of links interrupt enable
		 * BWC - Bandwidth sharing among channels
		 */
		set_mr(chan, FSL_DMA_MR_BWC | FSL_DMA_MR_EIE
			| FSL_DMA_MR_EOLNIE);
		break;
	case FSL_DMA_IP_83XX:
		/* Set the channel to below modes:
		 * EOTIE - End-of-transfer interrupt enable
		 * PRC_RM - PCI read multiple
		 */
		set_mr(chan, FSL_DMA_MR_EOTIE | FSL_DMA_MR_PRC_RM);
		break;
	}
}