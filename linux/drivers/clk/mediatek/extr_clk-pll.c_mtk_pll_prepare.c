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
typedef  int u32 ;
struct mtk_clk_pll {scalar_t__ base_addr; TYPE_1__* data; scalar_t__ pwr_addr; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int en_mask; int flags; int rst_bar_mask; } ;

/* Variables and functions */
 int CON0_ISO_EN ; 
 int CON0_PWR_ON ; 
 int HAVE_RST_BAR ; 
 scalar_t__ REG_CON0 ; 
 int /*<<< orphan*/  __mtk_pll_tuner_enable (struct mtk_clk_pll*) ; 
 int readl (scalar_t__) ; 
 struct mtk_clk_pll* to_mtk_clk_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtk_pll_prepare(struct clk_hw *hw)
{
	struct mtk_clk_pll *pll = to_mtk_clk_pll(hw);
	u32 r;

	r = readl(pll->pwr_addr) | CON0_PWR_ON;
	writel(r, pll->pwr_addr);
	udelay(1);

	r = readl(pll->pwr_addr) & ~CON0_ISO_EN;
	writel(r, pll->pwr_addr);
	udelay(1);

	r = readl(pll->base_addr + REG_CON0);
	r |= pll->data->en_mask;
	writel(r, pll->base_addr + REG_CON0);

	__mtk_pll_tuner_enable(pll);

	udelay(20);

	if (pll->data->flags & HAVE_RST_BAR) {
		r = readl(pll->base_addr + REG_CON0);
		r |= pll->data->rst_bar_mask;
		writel(r, pll->base_addr + REG_CON0);
	}

	return 0;
}