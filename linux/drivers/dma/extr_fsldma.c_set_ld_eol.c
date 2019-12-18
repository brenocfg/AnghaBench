#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct fsldma_chan {int feature; } ;
struct TYPE_2__ {int /*<<< orphan*/  next_ln_addr; } ;
struct fsl_desc_sw {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_DMA (struct fsldma_chan*,int,int) ; 
 int DMA_TO_CPU (struct fsldma_chan*,int /*<<< orphan*/ ,int) ; 
 int FSL_DMA_EOL ; 
 int FSL_DMA_IP_83XX ; 
 int FSL_DMA_IP_MASK ; 
 int FSL_DMA_SNEN ; 

__attribute__((used)) static void set_ld_eol(struct fsldma_chan *chan, struct fsl_desc_sw *desc)
{
	u64 snoop_bits;

	snoop_bits = ((chan->feature & FSL_DMA_IP_MASK) == FSL_DMA_IP_83XX)
		? FSL_DMA_SNEN : 0;

	desc->hw.next_ln_addr = CPU_TO_DMA(chan,
		DMA_TO_CPU(chan, desc->hw.next_ln_addr, 64) | FSL_DMA_EOL
			| snoop_bits, 64);
}