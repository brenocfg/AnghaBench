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
struct imx_pll14xx_rate_table {int mdiv; int pdiv; int kdiv; } ;

/* Variables and functions */
 int KDIV_MASK ; 
 int KDIV_SHIFT ; 
 int MDIV_MASK ; 
 int MDIV_SHIFT ; 
 int PDIV_MASK ; 
 int PDIV_SHIFT ; 

__attribute__((used)) static inline bool clk_pll1443x_mpk_change(const struct imx_pll14xx_rate_table *rate,
					  u32 pll_div_ctl0, u32 pll_div_ctl1)
{
	u32 old_mdiv, old_pdiv, old_kdiv;

	old_mdiv = (pll_div_ctl0 >> MDIV_SHIFT) & MDIV_MASK;
	old_pdiv = (pll_div_ctl0 >> PDIV_SHIFT) & PDIV_MASK;
	old_kdiv = (pll_div_ctl1 >> KDIV_SHIFT) & KDIV_MASK;

	return rate->mdiv != old_mdiv || rate->pdiv != old_pdiv ||
		rate->kdiv != old_kdiv;
}