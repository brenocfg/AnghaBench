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

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  meson_clk_pll_init (struct clk_hw*) ; 
 scalar_t__ meson_clk_pll_wait_lock (struct clk_hw*) ; 

__attribute__((used)) static int meson_clk_pcie_pll_enable(struct clk_hw *hw)
{
	meson_clk_pll_init(hw);

	if (meson_clk_pll_wait_lock(hw))
		return -EIO;

	return 0;
}