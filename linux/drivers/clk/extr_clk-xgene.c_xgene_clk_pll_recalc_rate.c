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
typedef  unsigned long u32 ;
struct xgene_clk_pll {int version; scalar_t__ type; scalar_t__ pll_offset; scalar_t__ reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long CLKF_RD (unsigned long) ; 
 int CLKOD_RD (unsigned long) ; 
 unsigned long CLKR_RD (unsigned long) ; 
 int N_DIV_RD (unsigned long) ; 
 scalar_t__ PLL_TYPE_PCP ; 
 unsigned long SC_N_DIV_RD (unsigned long) ; 
 scalar_t__ SC_OUTDIV2 (unsigned long) ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned long,unsigned long,int) ; 
 struct xgene_clk_pll* to_xgene_clk_pll (struct clk_hw*) ; 
 unsigned long xgene_clk_read (scalar_t__) ; 

__attribute__((used)) static unsigned long xgene_clk_pll_recalc_rate(struct clk_hw *hw,
				unsigned long parent_rate)
{
	struct xgene_clk_pll *pllclk = to_xgene_clk_pll(hw);
	unsigned long fref;
	unsigned long fvco;
	u32 pll;
	u32 nref;
	u32 nout;
	u32 nfb;

	pll = xgene_clk_read(pllclk->reg + pllclk->pll_offset);

	if (pllclk->version <= 1) {
		if (pllclk->type == PLL_TYPE_PCP) {
			/*
			* PLL VCO = Reference clock * NF
			* PCP PLL = PLL_VCO / 2
			*/
			nout = 2;
			fvco = parent_rate * (N_DIV_RD(pll) + 4);
		} else {
			/*
			* Fref = Reference Clock / NREF;
			* Fvco = Fref * NFB;
			* Fout = Fvco / NOUT;
			*/
			nref = CLKR_RD(pll) + 1;
			nout = CLKOD_RD(pll) + 1;
			nfb = CLKF_RD(pll);
			fref = parent_rate / nref;
			fvco = fref * nfb;
		}
	} else {
		/*
		 * fvco = Reference clock * FBDIVC
		 * PLL freq = fvco / NOUT
		 */
		nout = SC_OUTDIV2(pll) ? 2 : 3;
		fvco = parent_rate * SC_N_DIV_RD(pll);
	}
	pr_debug("%s pll recalc rate %ld parent %ld version %d\n",
		 clk_hw_get_name(hw), fvco / nout, parent_rate,
		 pllclk->version);

	return fvco / nout;
}