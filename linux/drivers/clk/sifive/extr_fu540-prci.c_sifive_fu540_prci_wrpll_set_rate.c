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
struct clk_hw {int dummy; } ;
struct __prci_wrpll_data {int /*<<< orphan*/  (* disable_bypass ) (struct __prci_data*) ;int /*<<< orphan*/  c; int /*<<< orphan*/  (* enable_bypass ) (struct __prci_data*) ;} ;
struct __prci_data {int dummy; } ;
struct __prci_clock {struct __prci_data* pd; struct __prci_wrpll_data* pwd; } ;

/* Variables and functions */
 int /*<<< orphan*/  __prci_wrpll_write_cfg (struct __prci_data*,struct __prci_wrpll_data*,int /*<<< orphan*/ *) ; 
 struct __prci_clock* clk_hw_to_prci_clock (struct clk_hw*) ; 
 int /*<<< orphan*/  stub1 (struct __prci_data*) ; 
 int /*<<< orphan*/  stub2 (struct __prci_data*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrpll_calc_max_lock_us (int /*<<< orphan*/ *) ; 
 int wrpll_configure_for_rate (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

__attribute__((used)) static int sifive_fu540_prci_wrpll_set_rate(struct clk_hw *hw,
					    unsigned long rate,
					    unsigned long parent_rate)
{
	struct __prci_clock *pc = clk_hw_to_prci_clock(hw);
	struct __prci_wrpll_data *pwd = pc->pwd;
	struct __prci_data *pd = pc->pd;
	int r;

	r = wrpll_configure_for_rate(&pwd->c, rate, parent_rate);
	if (r)
		return r;

	if (pwd->enable_bypass)
		pwd->enable_bypass(pd);

	__prci_wrpll_write_cfg(pd, pwd, &pwd->c);

	udelay(wrpll_calc_max_lock_us(&pwd->c));

	if (pwd->disable_bypass)
		pwd->disable_bypass(pd);

	return 0;
}