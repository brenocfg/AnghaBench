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
struct sam9x60_pll {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; TYPE_1__* characteristics; int /*<<< orphan*/  id; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ upll; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_PLL_ACR ; 
 int PMC_PLL_ACR_UTMIBG ; 
 int PMC_PLL_ACR_UTMIVR ; 
 int /*<<< orphan*/  PMC_PLL_CTRL0 ; 
 int PMC_PLL_CTRL0_ENPLL ; 
 int PMC_PLL_CTRL0_ENPLLCK ; 
 int /*<<< orphan*/  PMC_PLL_UPDT ; 
 int PMC_PLL_UPDT_UPDATE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct sam9x60_pll* to_sam9x60_pll (struct clk_hw*) ; 

__attribute__((used)) static void sam9x60_pll_unprepare(struct clk_hw *hw)
{
	struct sam9x60_pll *pll = to_sam9x60_pll(hw);
	unsigned long flags;

	spin_lock_irqsave(pll->lock, flags);

	regmap_write(pll->regmap, PMC_PLL_UPDT, pll->id);

	regmap_update_bits(pll->regmap, PMC_PLL_CTRL0,
			   PMC_PLL_CTRL0_ENPLLCK, 0);

	regmap_update_bits(pll->regmap, PMC_PLL_UPDT,
			   PMC_PLL_UPDT_UPDATE, PMC_PLL_UPDT_UPDATE);

	regmap_update_bits(pll->regmap, PMC_PLL_CTRL0, PMC_PLL_CTRL0_ENPLL, 0);

	if (pll->characteristics->upll)
		regmap_update_bits(pll->regmap, PMC_PLL_ACR,
				   PMC_PLL_ACR_UTMIBG | PMC_PLL_ACR_UTMIVR, 0);

	regmap_update_bits(pll->regmap, PMC_PLL_UPDT,
			   PMC_PLL_UPDT_UPDATE, PMC_PLL_UPDT_UPDATE);

	spin_unlock_irqrestore(pll->lock, flags);
}