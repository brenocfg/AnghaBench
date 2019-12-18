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
typedef  int u64 ;
typedef  int u32 ;
struct clk_hw {int dummy; } ;
struct berlin2_avpll_channel {int index; int flags; scalar_t__ base; } ;

/* Variables and functions */
 int BERLIN2_AVPLL_BIT_QUIRK ; 
 int BIT (int) ; 
 scalar_t__ VCO_CTRL11 ; 
 scalar_t__ VCO_CTRL12 ; 
 scalar_t__ VCO_CTRL13 ; 
 scalar_t__ VCO_CTRL14 ; 
 scalar_t__ VCO_CTRL15 ; 
 scalar_t__ VCO_CTRL30 ; 
 int VCO_DPLL_CH1_ENABLE ; 
 int VCO_SYNC1_MASK ; 
 scalar_t__ VCO_SYNC1n (int) ; 
 int VCO_SYNC2_MASK ; 
 scalar_t__ VCO_SYNC2n (int) ; 
 int* div_av1 ; 
 int* div_hdmi ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int readl_relaxed (scalar_t__) ; 
 struct berlin2_avpll_channel* to_avpll_channel (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
berlin2_avpll_channel_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct berlin2_avpll_channel *ch = to_avpll_channel(hw);
	u32 reg, div_av2, div_av3, divider = 1;
	u64 freq = parent_rate;

	reg = readl_relaxed(ch->base + VCO_CTRL30);
	if ((reg & (VCO_DPLL_CH1_ENABLE << ch->index)) == 0)
		goto skip_div;

	/*
	 * Fch = (Fref * sync2) /
	 *    (sync1 * div_hdmi * div_av1 * div_av2 * div_av3)
	 */

	reg = readl_relaxed(ch->base + VCO_SYNC1n(ch->index));
	/* BG2/BG2CDs SYNC1 reg on AVPLL_B channel 1 is shifted by 4 */
	if (ch->flags & BERLIN2_AVPLL_BIT_QUIRK && ch->index == 0)
		reg >>= 4;
	divider = reg & VCO_SYNC1_MASK;

	reg = readl_relaxed(ch->base + VCO_SYNC2n(ch->index));
	freq *= reg & VCO_SYNC2_MASK;

	/* Channel 8 has no dividers */
	if (ch->index == 7)
		goto skip_div;

	/*
	 * HDMI divider start at VCO_CTRL11, bit 7; MSB is enable, lower 2 bit
	 * determine divider.
	 */
	reg = readl_relaxed(ch->base + VCO_CTRL11) >> 7;
	reg = (reg >> (ch->index * 3));
	if (reg & BIT(2))
		divider *= div_hdmi[reg & 0x3];

	/*
	 * AV1 divider start at VCO_CTRL11, bit 28; MSB is enable, lower 2 bit
	 * determine divider.
	 */
	if (ch->index == 0) {
		reg = readl_relaxed(ch->base + VCO_CTRL11);
		reg >>= 28;
	} else {
		reg = readl_relaxed(ch->base + VCO_CTRL12);
		reg >>= (ch->index-1) * 3;
	}
	if (reg & BIT(2))
		divider *= div_av1[reg & 0x3];

	/*
	 * AV2 divider start at VCO_CTRL12, bit 18; each 7 bits wide,
	 * zero is not a valid value.
	 */
	if (ch->index < 2) {
		reg = readl_relaxed(ch->base + VCO_CTRL12);
		reg >>= 18 + (ch->index * 7);
	} else if (ch->index < 7) {
		reg = readl_relaxed(ch->base + VCO_CTRL13);
		reg >>= (ch->index - 2) * 7;
	} else {
		reg = readl_relaxed(ch->base + VCO_CTRL14);
	}
	div_av2 = reg & 0x7f;
	if (div_av2)
		divider *= div_av2;

	/*
	 * AV3 divider start at VCO_CTRL14, bit 7; each 4 bits wide.
	 * AV2/AV3 form a fractional divider, where only specfic values for AV3
	 * are allowed. AV3 != 0 divides by AV2/2, AV3=0 is bypass.
	 */
	if (ch->index < 6) {
		reg = readl_relaxed(ch->base + VCO_CTRL14);
		reg >>= 7 + (ch->index * 4);
	} else {
		reg = readl_relaxed(ch->base + VCO_CTRL15);
	}
	div_av3 = reg & 0xf;
	if (div_av2 && div_av3)
		freq *= 2;

skip_div:
	do_div(freq, divider);
	return (unsigned long)freq;
}