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
struct rockchip_pll_rate_table {int nr; int no; int nf; int nb; } ;
struct rockchip_clk_pll {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ RK3066_PLLCON (int) ; 
 int RK3066_PLLCON0_NR_MASK ; 
 int RK3066_PLLCON0_NR_SHIFT ; 
 int RK3066_PLLCON0_OD_MASK ; 
 int RK3066_PLLCON0_OD_SHIFT ; 
 int RK3066_PLLCON1_NF_MASK ; 
 int RK3066_PLLCON1_NF_SHIFT ; 
 int RK3066_PLLCON2_NB_MASK ; 
 int RK3066_PLLCON2_NB_SHIFT ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void rockchip_rk3066_pll_get_params(struct rockchip_clk_pll *pll,
					struct rockchip_pll_rate_table *rate)
{
	u32 pllcon;

	pllcon = readl_relaxed(pll->reg_base + RK3066_PLLCON(0));
	rate->nr = ((pllcon >> RK3066_PLLCON0_NR_SHIFT)
				& RK3066_PLLCON0_NR_MASK) + 1;
	rate->no = ((pllcon >> RK3066_PLLCON0_OD_SHIFT)
				& RK3066_PLLCON0_OD_MASK) + 1;

	pllcon = readl_relaxed(pll->reg_base + RK3066_PLLCON(1));
	rate->nf = ((pllcon >> RK3066_PLLCON1_NF_SHIFT)
				& RK3066_PLLCON1_NF_MASK) + 1;

	pllcon = readl_relaxed(pll->reg_base + RK3066_PLLCON(2));
	rate->nb = ((pllcon >> RK3066_PLLCON2_NB_SHIFT)
				& RK3066_PLLCON2_NB_MASK) + 1;
}