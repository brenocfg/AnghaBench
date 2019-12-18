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
struct clk_rpmh {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_rpmh_bcm_send_cmd (struct clk_rpmh*,int) ; 
 struct clk_rpmh* to_clk_rpmh (struct clk_hw*) ; 

__attribute__((used)) static void clk_rpmh_bcm_unprepare(struct clk_hw *hw)
{
	struct clk_rpmh *c = to_clk_rpmh(hw);

	clk_rpmh_bcm_send_cmd(c, false);
}