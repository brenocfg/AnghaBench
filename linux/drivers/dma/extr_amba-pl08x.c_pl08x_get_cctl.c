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
typedef  int u32 ;
struct pl08x_dma_chan {TYPE_1__* cd; } ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;
struct TYPE_2__ {scalar_t__ single; } ;

/* Variables and functions */
 int PL080_CONTROL_DB_SIZE_SHIFT ; 
 int PL080_CONTROL_DWIDTH_SHIFT ; 
 int PL080_CONTROL_SB_SIZE_SHIFT ; 
 int PL080_CONTROL_SWIDTH_SHIFT ; 
 int pl08x_burst (int) ; 
 int pl08x_cctl (int) ; 
 int pl08x_width (int) ; 

__attribute__((used)) static u32 pl08x_get_cctl(struct pl08x_dma_chan *plchan,
	enum dma_slave_buswidth addr_width, u32 maxburst)
{
	u32 width, burst, cctl = 0;

	width = pl08x_width(addr_width);
	if (width == ~0)
		return ~0;

	cctl |= width << PL080_CONTROL_SWIDTH_SHIFT;
	cctl |= width << PL080_CONTROL_DWIDTH_SHIFT;

	/*
	 * If this channel will only request single transfers, set this
	 * down to ONE element.  Also select one element if no maxburst
	 * is specified.
	 */
	if (plchan->cd->single)
		maxburst = 1;

	burst = pl08x_burst(maxburst);
	cctl |= burst << PL080_CONTROL_SB_SIZE_SHIFT;
	cctl |= burst << PL080_CONTROL_DB_SIZE_SHIFT;

	return pl08x_cctl(cctl);
}