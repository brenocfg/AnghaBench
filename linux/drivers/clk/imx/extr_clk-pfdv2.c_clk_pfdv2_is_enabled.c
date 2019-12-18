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
struct clk_pfdv2 {int gate_bit; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct clk_pfdv2* to_clk_pfdv2 (struct clk_hw*) ; 

__attribute__((used)) static int clk_pfdv2_is_enabled(struct clk_hw *hw)
{
	struct clk_pfdv2 *pfd = to_clk_pfdv2(hw);

	if (readl_relaxed(pfd->reg) & (1 << pfd->gate_bit))
		return 0;

	return 1;
}