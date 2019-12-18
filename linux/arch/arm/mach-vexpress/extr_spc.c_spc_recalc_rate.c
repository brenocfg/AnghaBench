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
struct clk_spc {int /*<<< orphan*/  cluster; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long EIO ; 
 struct clk_spc* to_clk_spc (struct clk_hw*) ; 
 scalar_t__ ve_spc_get_performance (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned long spc_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct clk_spc *spc = to_clk_spc(hw);
	u32 freq;

	if (ve_spc_get_performance(spc->cluster, &freq))
		return -EIO;

	return freq * 1000;
}