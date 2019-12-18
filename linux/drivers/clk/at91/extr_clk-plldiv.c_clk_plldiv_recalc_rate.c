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
struct clk_plldiv {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_MCKR ; 
 unsigned int AT91_PMC_PLLADIV2 ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_plldiv* to_clk_plldiv (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_plldiv_recalc_rate(struct clk_hw *hw,
					    unsigned long parent_rate)
{
	struct clk_plldiv *plldiv = to_clk_plldiv(hw);
	unsigned int mckr;

	regmap_read(plldiv->regmap, AT91_PMC_MCKR, &mckr);

	if (mckr & AT91_PMC_PLLADIV2)
		return parent_rate / 2;

	return parent_rate;
}