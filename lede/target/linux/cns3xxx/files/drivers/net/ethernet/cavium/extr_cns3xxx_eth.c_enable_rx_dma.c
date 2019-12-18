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
struct sw {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  fs_dma_ctrl0; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enable_rx_dma(struct sw *sw)
{
	__raw_writel(0x1, &sw->regs->fs_dma_ctrl0);
}