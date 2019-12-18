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
struct iproc_pll {int dummy; } ;
struct iproc_clk {struct iproc_pll* pll; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int __pll_enable (struct iproc_pll*) ; 
 struct iproc_clk* to_iproc_clk (struct clk_hw*) ; 

__attribute__((used)) static int iproc_pll_enable(struct clk_hw *hw)
{
	struct iproc_clk *clk = to_iproc_clk(hw);
	struct iproc_pll *pll = clk->pll;

	return __pll_enable(pll);
}