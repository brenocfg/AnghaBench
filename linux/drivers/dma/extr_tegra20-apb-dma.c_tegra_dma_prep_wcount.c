#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_dma_channel_regs {int wcount; int csr; } ;
struct tegra_dma_channel {TYPE_2__* tdma; } ;
struct TYPE_4__ {TYPE_1__* chip_data; } ;
struct TYPE_3__ {scalar_t__ support_separate_wcount_reg; } ;

/* Variables and functions */

__attribute__((used)) static void tegra_dma_prep_wcount(struct tegra_dma_channel *tdc,
	struct tegra_dma_channel_regs *ch_regs, u32 len)
{
	u32 len_field = (len - 4) & 0xFFFC;

	if (tdc->tdma->chip_data->support_separate_wcount_reg)
		ch_regs->wcount = len_field;
	else
		ch_regs->csr |= len_field;
}