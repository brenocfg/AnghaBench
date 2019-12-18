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
struct s2mps11_clk {int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; TYPE_1__* iodev; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap_pmic; } ;

/* Variables and functions */
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct s2mps11_clk* to_s2mps11_clk (struct clk_hw*) ; 

__attribute__((used)) static int s2mps11_clk_prepare(struct clk_hw *hw)
{
	struct s2mps11_clk *s2mps11 = to_s2mps11_clk(hw);

	return regmap_update_bits(s2mps11->iodev->regmap_pmic,
				 s2mps11->reg,
				 s2mps11->mask, s2mps11->mask);
}