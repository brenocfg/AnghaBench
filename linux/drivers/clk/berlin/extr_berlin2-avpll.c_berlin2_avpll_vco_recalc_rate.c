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
typedef  size_t u64 ;
typedef  size_t u32 ;
struct clk_hw {int dummy; } ;
struct berlin2_avpll_vco {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ VCO_CTRL1 ; 
 size_t VCO_FBDIV_MASK ; 
 size_t VCO_FBDIV_SHIFT ; 
 size_t VCO_REFDIV_MASK ; 
 size_t VCO_REFDIV_SHIFT ; 
 int /*<<< orphan*/  do_div (size_t,size_t) ; 
 size_t readl_relaxed (scalar_t__) ; 
 struct berlin2_avpll_vco* to_avpll_vco (struct clk_hw*) ; 
 size_t* vco_refdiv ; 

__attribute__((used)) static unsigned long
berlin2_avpll_vco_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct berlin2_avpll_vco *vco = to_avpll_vco(hw);
	u32 reg, refdiv, fbdiv;
	u64 freq = parent_rate;

	/* AVPLL VCO frequency: Fvco = (Fref / refdiv) * fbdiv */
	reg = readl_relaxed(vco->base + VCO_CTRL1);
	refdiv = (reg & VCO_REFDIV_MASK) >> VCO_REFDIV_SHIFT;
	refdiv = vco_refdiv[refdiv];
	fbdiv = (reg & VCO_FBDIV_MASK) >> VCO_FBDIV_SHIFT;
	freq *= fbdiv;
	do_div(freq, refdiv);

	return (unsigned long)freq;
}