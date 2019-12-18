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
struct ep93xx_dma_chan {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ M2P_CONTROL ; 
 int /*<<< orphan*/  M2P_CONTROL_NFBINT ; 
 int /*<<< orphan*/  M2P_CONTROL_STALLINT ; 
 scalar_t__ ep93xx_dma_advance_active (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  m2p_fill_desc (struct ep93xx_dma_chan*) ; 
 int /*<<< orphan*/  m2p_set_control (struct ep93xx_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void m2p_hw_submit(struct ep93xx_dma_chan *edmac)
{
	u32 control = readl(edmac->regs + M2P_CONTROL);

	m2p_fill_desc(edmac);
	control |= M2P_CONTROL_STALLINT;

	if (ep93xx_dma_advance_active(edmac)) {
		m2p_fill_desc(edmac);
		control |= M2P_CONTROL_NFBINT;
	}

	m2p_set_control(edmac, control);
}