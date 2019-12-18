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
struct ep93xx_dma_chan {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ M2M_CONTROL ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void m2m_hw_shutdown(struct ep93xx_dma_chan *edmac)
{
	/* Just disable the channel */
	writel(0, edmac->regs + M2M_CONTROL);
}