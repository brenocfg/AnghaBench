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
typedef  int u8 ;
typedef  int u32 ;
struct clk_hw {int dummy; } ;
struct __prci_data {int dummy; } ;
struct __prci_clock {struct __prci_data* pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRCI_CLKMUXSTATUSREG_OFFSET ; 
 int PRCI_CLKMUXSTATUSREG_TLCLKSEL_STATUS_MASK ; 
 int __prci_readl (struct __prci_data*,int /*<<< orphan*/ ) ; 
 struct __prci_clock* clk_hw_to_prci_clock (struct clk_hw*) ; 
 unsigned long div_u64 (unsigned long,int) ; 

__attribute__((used)) static unsigned long sifive_fu540_prci_tlclksel_recalc_rate(struct clk_hw *hw,
							    unsigned long parent_rate)
{
	struct __prci_clock *pc = clk_hw_to_prci_clock(hw);
	struct __prci_data *pd = pc->pd;
	u32 v;
	u8 div;

	v = __prci_readl(pd, PRCI_CLKMUXSTATUSREG_OFFSET);
	v &= PRCI_CLKMUXSTATUSREG_TLCLKSEL_STATUS_MASK;
	div = v ? 1 : 2;

	return div_u64(parent_rate, div);
}