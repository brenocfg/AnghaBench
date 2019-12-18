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
typedef  int u32 ;
struct clk_hw {int dummy; } ;
struct berlin2_avpll_channel {int index; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ VCO_CTRL10 ; 
 int VCO_POWERUP_CH1 ; 
 int readl_relaxed (scalar_t__) ; 
 struct berlin2_avpll_channel* to_avpll_channel (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int berlin2_avpll_channel_enable(struct clk_hw *hw)
{
	struct berlin2_avpll_channel *ch = to_avpll_channel(hw);
	u32 reg;

	reg = readl_relaxed(ch->base + VCO_CTRL10);
	reg |= VCO_POWERUP_CH1 << ch->index;
	writel_relaxed(reg, ch->base + VCO_CTRL10);

	return 0;
}