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
typedef  int /*<<< orphan*/  u32 ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prcc_pclk_ops ; 
 struct clk* clk_reg_prcc (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 

struct clk *clk_reg_prcc_pclk(const char *name,
			      const char *parent_name,
			      resource_size_t phy_base,
			      u32 cg_sel,
			      unsigned long flags)
{
	return clk_reg_prcc(name, parent_name, phy_base, cg_sel, flags,
			&clk_prcc_pclk_ops);
}