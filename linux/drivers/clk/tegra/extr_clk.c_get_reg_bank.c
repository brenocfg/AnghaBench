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
struct tegra_clk_periph_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int periph_banks ; 
 struct tegra_clk_periph_regs const* periph_regs ; 

const struct tegra_clk_periph_regs *get_reg_bank(int clkid)
{
	int reg_bank = clkid / 32;

	if (reg_bank < periph_banks)
		return &periph_regs[reg_bank];
	else {
		WARN_ON(1);
		return NULL;
	}
}