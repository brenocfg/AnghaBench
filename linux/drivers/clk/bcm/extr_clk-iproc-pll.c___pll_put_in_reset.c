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
struct iproc_pll_reset_ctrl {scalar_t__ offset; int /*<<< orphan*/  p_reset_shift; int /*<<< orphan*/  reset_shift; } ;
struct iproc_pll_ctrl {int flags; struct iproc_pll_reset_ctrl reset; } ;
struct iproc_pll {scalar_t__ control_base; struct iproc_pll_ctrl* ctrl; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int IPROC_CLK_PLL_RESET_ACTIVE_LOW ; 
 int /*<<< orphan*/  iproc_pll_write (struct iproc_pll*,scalar_t__,scalar_t__,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void __pll_put_in_reset(struct iproc_pll *pll)
{
	u32 val;
	const struct iproc_pll_ctrl *ctrl = pll->ctrl;
	const struct iproc_pll_reset_ctrl *reset = &ctrl->reset;

	val = readl(pll->control_base + reset->offset);
	if (ctrl->flags & IPROC_CLK_PLL_RESET_ACTIVE_LOW)
		val |= BIT(reset->reset_shift) | BIT(reset->p_reset_shift);
	else
		val &= ~(BIT(reset->reset_shift) | BIT(reset->p_reset_shift));
	iproc_pll_write(pll, pll->control_base, reset->offset, val);
}