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
struct clk_pfd {int idx; scalar_t__ reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ CLR ; 
 struct clk_pfd* to_clk_pfd (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int clk_pfd_enable(struct clk_hw *hw)
{
	struct clk_pfd *pfd = to_clk_pfd(hw);

	writel_relaxed(1 << ((pfd->idx + 1) * 8 - 1), pfd->reg + CLR);

	return 0;
}