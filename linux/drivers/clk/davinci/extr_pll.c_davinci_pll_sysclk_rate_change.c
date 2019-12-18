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
struct notifier_block {int dummy; } ;
struct davinci_pllen_clk {scalar_t__ base; } ;
struct clk_notifier_data {int /*<<< orphan*/  clk; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
 scalar_t__ PLLCMD ; 
 int PLLCMD_GOSET ; 
 scalar_t__ PLLSTAT ; 
 int PLLSTAT_GOSTAT ; 
#define  POST_RATE_CHANGE 129 
#define  PRE_RATE_CHANGE 128 
 struct clk_hw* __clk_get_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_parent (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 struct davinci_pllen_clk* to_davinci_pllen_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int davinci_pll_sysclk_rate_change(struct notifier_block *nb,
					  unsigned long flags, void *data)
{
	struct clk_notifier_data *cnd = data;
	struct clk_hw *hw = __clk_get_hw(clk_get_parent(cnd->clk));
	struct davinci_pllen_clk *pll = to_davinci_pllen_clk(hw);
	u32 pllcmd, pllstat;

	switch (flags) {
	case POST_RATE_CHANGE:
		/* apply the changes */
		pllcmd = readl(pll->base + PLLCMD);
		pllcmd |= PLLCMD_GOSET;
		writel(pllcmd, pll->base + PLLCMD);
		/* fallthrough */
	case PRE_RATE_CHANGE:
		/* Wait until for outstanding changes to take effect */
		do {
			pllstat = readl(pll->base + PLLSTAT);
		} while (pllstat & PLLSTAT_GOSTAT);
		break;
	}

	return NOTIFY_OK;
}