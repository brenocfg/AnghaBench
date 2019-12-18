#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct mn {int /*<<< orphan*/  width; } ;
struct clk_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  regmap; } ;
struct clk_dyn_rcg {scalar_t__ bank_reg; scalar_t__* ns_reg; scalar_t__* md_reg; TYPE_2__* p; TYPE_1__ clkr; struct mn* mn; } ;
struct TYPE_4__ {int /*<<< orphan*/  pre_div_width; } ;

/* Variables and functions */
 unsigned long calc_rate (unsigned long,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ md_to_m (struct mn*,scalar_t__) ; 
 scalar_t__ ns_m_to_n (struct mn*,scalar_t__,scalar_t__) ; 
 scalar_t__ ns_to_pre_div (TYPE_2__*,scalar_t__) ; 
 int reg_to_bank (struct clk_dyn_rcg*,scalar_t__) ; 
 scalar_t__ reg_to_mnctr_mode (struct mn*,scalar_t__) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 struct clk_dyn_rcg* to_clk_dyn_rcg (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
clk_dyn_rcg_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct clk_dyn_rcg *rcg = to_clk_dyn_rcg(hw);
	u32 m, n, pre_div, ns, md, mode, reg;
	int bank;
	struct mn *mn;
	bool banked_p = !!rcg->p[1].pre_div_width;
	bool banked_mn = !!rcg->mn[1].width;

	regmap_read(rcg->clkr.regmap, rcg->bank_reg, &reg);
	bank = reg_to_bank(rcg, reg);

	regmap_read(rcg->clkr.regmap, rcg->ns_reg[bank], &ns);
	m = n = pre_div = mode = 0;

	if (banked_mn) {
		mn = &rcg->mn[bank];
		regmap_read(rcg->clkr.regmap, rcg->md_reg[bank], &md);
		m = md_to_m(mn, md);
		n = ns_m_to_n(mn, ns, m);
		/* Two NS registers means mode control is in NS register */
		if (rcg->ns_reg[0] != rcg->ns_reg[1])
			reg = ns;
		mode = reg_to_mnctr_mode(mn, reg);
	}

	if (banked_p)
		pre_div = ns_to_pre_div(&rcg->p[bank], ns);

	return calc_rate(parent_rate, m, n, mode, pre_div);
}