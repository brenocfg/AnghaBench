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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sam9x60_pll {int id; int div; scalar_t__ mul; int /*<<< orphan*/  lock; TYPE_1__* characteristics; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ upll; } ;

/* Variables and functions */
 void* FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PMC_PLL_ACR ; 
 int PMC_PLL_ACR_DEFAULT ; 
 int PMC_PLL_ACR_UTMIBG ; 
 int PMC_PLL_ACR_UTMIVR ; 
 int /*<<< orphan*/  PMC_PLL_CTRL0 ; 
 int /*<<< orphan*/  PMC_PLL_CTRL0_DIV_MSK ; 
 int PMC_PLL_CTRL0_ENLOCK ; 
 int PMC_PLL_CTRL0_ENPLL ; 
 int PMC_PLL_CTRL0_ENPLLCK ; 
 int /*<<< orphan*/  PMC_PLL_CTRL1 ; 
 int /*<<< orphan*/  PMC_PLL_CTRL1_MUL_MSK ; 
 int /*<<< orphan*/  PMC_PLL_UPDT ; 
 int /*<<< orphan*/  PMC_PLL_UPDT_UPDATE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sam9x60_pll_ready (struct regmap*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct sam9x60_pll* to_sam9x60_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sam9x60_pll_prepare(struct clk_hw *hw)
{
	struct sam9x60_pll *pll = to_sam9x60_pll(hw);
	struct regmap *regmap = pll->regmap;
	unsigned long flags;
	u8 div;
	u16 mul;
	u32 val;

	spin_lock_irqsave(pll->lock, flags);
	regmap_write(regmap, PMC_PLL_UPDT, pll->id);

	regmap_read(regmap, PMC_PLL_CTRL0, &val);
	div = FIELD_GET(PMC_PLL_CTRL0_DIV_MSK, val);

	regmap_read(regmap, PMC_PLL_CTRL1, &val);
	mul = FIELD_GET(PMC_PLL_CTRL1_MUL_MSK, val);

	if (sam9x60_pll_ready(regmap, pll->id) &&
	    (div == pll->div && mul == pll->mul)) {
		spin_unlock_irqrestore(pll->lock, flags);
		return 0;
	}

	/* Recommended value for PMC_PLL_ACR */
	val = PMC_PLL_ACR_DEFAULT;
	regmap_write(regmap, PMC_PLL_ACR, val);

	regmap_write(regmap, PMC_PLL_CTRL1,
		     FIELD_PREP(PMC_PLL_CTRL1_MUL_MSK, pll->mul));

	if (pll->characteristics->upll) {
		/* Enable the UTMI internal bandgap */
		val |= PMC_PLL_ACR_UTMIBG;
		regmap_write(regmap, PMC_PLL_ACR, val);

		udelay(10);

		/* Enable the UTMI internal regulator */
		val |= PMC_PLL_ACR_UTMIVR;
		regmap_write(regmap, PMC_PLL_ACR, val);

		udelay(10);
	}

	regmap_update_bits(regmap, PMC_PLL_UPDT,
			   PMC_PLL_UPDT_UPDATE, PMC_PLL_UPDT_UPDATE);

	regmap_write(regmap, PMC_PLL_CTRL0,
		     PMC_PLL_CTRL0_ENLOCK | PMC_PLL_CTRL0_ENPLL |
		     PMC_PLL_CTRL0_ENPLLCK | pll->div);

	regmap_update_bits(regmap, PMC_PLL_UPDT,
			   PMC_PLL_UPDT_UPDATE, PMC_PLL_UPDT_UPDATE);

	while (!sam9x60_pll_ready(regmap, pll->id))
		cpu_relax();

	spin_unlock_irqrestore(pll->lock, flags);

	return 0;
}