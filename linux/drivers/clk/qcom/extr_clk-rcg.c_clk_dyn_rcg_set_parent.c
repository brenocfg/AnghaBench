#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct freq_tbl {int /*<<< orphan*/  src; scalar_t__ pre_div; int /*<<< orphan*/  m; int /*<<< orphan*/  n; int /*<<< orphan*/  member_0; } ;
struct clk_hw {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  regmap; } ;
struct clk_dyn_rcg {TYPE_2__* s; TYPE_3__* p; TYPE_4__* mn; int /*<<< orphan*/ * md_reg; TYPE_1__ clkr; int /*<<< orphan*/ * ns_reg; int /*<<< orphan*/  bank_reg; } ;
struct TYPE_9__ {int /*<<< orphan*/  width; } ;
struct TYPE_8__ {int /*<<< orphan*/  pre_div_width; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent_map; } ;

/* Variables and functions */
 int configure_bank (struct clk_dyn_rcg*,struct freq_tbl*) ; 
 int /*<<< orphan*/  md_to_m (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_m_to_n (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ns_to_pre_div (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_find_src_index (struct clk_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reg_to_bank (struct clk_dyn_rcg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_dyn_rcg* to_clk_dyn_rcg (struct clk_hw*) ; 

__attribute__((used)) static int clk_dyn_rcg_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_dyn_rcg *rcg = to_clk_dyn_rcg(hw);
	u32 ns, md, reg;
	int bank;
	struct freq_tbl f = { 0 };
	bool banked_mn = !!rcg->mn[1].width;
	bool banked_p = !!rcg->p[1].pre_div_width;

	regmap_read(rcg->clkr.regmap, rcg->bank_reg, &reg);
	bank = reg_to_bank(rcg, reg);

	regmap_read(rcg->clkr.regmap, rcg->ns_reg[bank], &ns);

	if (banked_mn) {
		regmap_read(rcg->clkr.regmap, rcg->md_reg[bank], &md);
		f.m = md_to_m(&rcg->mn[bank], md);
		f.n = ns_m_to_n(&rcg->mn[bank], ns, f.m);
	}

	if (banked_p)
		f.pre_div = ns_to_pre_div(&rcg->p[bank], ns) + 1;

	f.src = qcom_find_src_index(hw, rcg->s[bank].parent_map, index);
	return configure_bank(rcg, &f);
}