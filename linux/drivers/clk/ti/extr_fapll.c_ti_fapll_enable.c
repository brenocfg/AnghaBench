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
struct fapll_data {int /*<<< orphan*/  base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAPLL_MAIN_PLLEN ; 
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_fapll_wait_lock (struct fapll_data*) ; 
 struct fapll_data* to_fapll (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_fapll_enable(struct clk_hw *hw)
{
	struct fapll_data *fd = to_fapll(hw);
	u32 v = readl_relaxed(fd->base);

	v |= FAPLL_MAIN_PLLEN;
	writel_relaxed(v, fd->base);
	ti_fapll_wait_lock(fd);

	return 0;
}