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
struct clk_hw {int dummy; } ;
struct clk_hisi_phase {int mask; int shift; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int hisi_phase_regval_to_degrees (struct clk_hisi_phase*,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct clk_hisi_phase* to_clk_hisi_phase (struct clk_hw*) ; 

__attribute__((used)) static int hisi_clk_get_phase(struct clk_hw *hw)
{
	struct clk_hisi_phase *phase = to_clk_hisi_phase(hw);
	u32 regval;

	regval = readl(phase->reg);
	regval = (regval & phase->mask) >> phase->shift;

	return hisi_phase_regval_to_degrees(phase, regval);
}