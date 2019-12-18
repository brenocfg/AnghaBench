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
struct clk_creg_data {int /*<<< orphan*/  en_mask; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC18XX_CREG_CREG0 ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_creg_data* to_clk_creg (struct clk_hw*) ; 

__attribute__((used)) static int clk_creg_enable(struct clk_hw *hw)
{
	struct clk_creg_data *creg = to_clk_creg(hw);

	return regmap_update_bits(creg->reg, LPC18XX_CREG_CREG0,
				  creg->en_mask, creg->en_mask);
}