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
typedef  int /*<<< orphan*/  u16 ;
struct clk_syscon {int reset; int /*<<< orphan*/  res_reg; int /*<<< orphan*/  res_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  syscon_resetreg_lock ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void syscon_block_reset_enable(struct clk_syscon *sclk)
{
	unsigned long iflags;
	u16 val;

	/* Not all blocks support resetting */
	if (!sclk->res_reg)
		return;
	spin_lock_irqsave(&syscon_resetreg_lock, iflags);
	val = readw(sclk->res_reg);
	val |= BIT(sclk->res_bit);
	writew(val, sclk->res_reg);
	spin_unlock_irqrestore(&syscon_resetreg_lock, iflags);
	sclk->reset = true;
}