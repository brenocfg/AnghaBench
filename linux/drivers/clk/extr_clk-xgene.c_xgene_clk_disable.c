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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ reg_clk_offset; scalar_t__ csr_reg; int /*<<< orphan*/  reg_clk_mask; scalar_t__ reg_csr_offset; int /*<<< orphan*/  reg_csr_mask; } ;
struct xgene_clk {scalar_t__ lock; TYPE_1__ param; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct xgene_clk* to_xgene_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  xgene_clk_read (scalar_t__) ; 
 int /*<<< orphan*/  xgene_clk_write (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xgene_clk_disable(struct clk_hw *hw)
{
	struct xgene_clk *pclk = to_xgene_clk(hw);
	unsigned long flags = 0;
	u32 data;

	if (pclk->lock)
		spin_lock_irqsave(pclk->lock, flags);

	if (pclk->param.csr_reg) {
		pr_debug("%s clock disabled\n", clk_hw_get_name(hw));
		/* First put the CSR in reset */
		data = xgene_clk_read(pclk->param.csr_reg +
					pclk->param.reg_csr_offset);
		data |= pclk->param.reg_csr_mask;
		xgene_clk_write(data, pclk->param.csr_reg +
					pclk->param.reg_csr_offset);

		/* Second disable the clock */
		data = xgene_clk_read(pclk->param.csr_reg +
					pclk->param.reg_clk_offset);
		data &= ~pclk->param.reg_clk_mask;
		xgene_clk_write(data, pclk->param.csr_reg +
					pclk->param.reg_clk_offset);
	}

	if (pclk->lock)
		spin_unlock_irqrestore(pclk->lock, flags);
}