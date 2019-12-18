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
struct ep93xx_dma_desc {int /*<<< orphan*/  size; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct ep93xx_dma_chan {int buffer; scalar_t__ regs; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 scalar_t__ DMA_MEM_TO_DEV ; 
 scalar_t__ M2P_BASE0 ; 
 scalar_t__ M2P_BASE1 ; 
 scalar_t__ M2P_MAXCNT0 ; 
 scalar_t__ M2P_MAXCNT1 ; 
 int /*<<< orphan*/  chan2dev (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ep93xx_dma_chan_direction (int /*<<< orphan*/ *) ; 
 struct ep93xx_dma_desc* ep93xx_dma_get_active (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void m2p_fill_desc(struct ep93xx_dma_chan *edmac)
{
	struct ep93xx_dma_desc *desc;
	u32 bus_addr;

	desc = ep93xx_dma_get_active(edmac);
	if (!desc) {
		dev_warn(chan2dev(edmac), "M2P: empty descriptor list\n");
		return;
	}

	if (ep93xx_dma_chan_direction(&edmac->chan) == DMA_MEM_TO_DEV)
		bus_addr = desc->src_addr;
	else
		bus_addr = desc->dst_addr;

	if (edmac->buffer == 0) {
		writel(desc->size, edmac->regs + M2P_MAXCNT0);
		writel(bus_addr, edmac->regs + M2P_BASE0);
	} else {
		writel(desc->size, edmac->regs + M2P_MAXCNT1);
		writel(bus_addr, edmac->regs + M2P_BASE1);
	}

	edmac->buffer ^= 1;
}