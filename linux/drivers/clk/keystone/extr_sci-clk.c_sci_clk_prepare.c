#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sci_clk {int flags; int /*<<< orphan*/  clk_id; int /*<<< orphan*/  dev_id; TYPE_1__* provider; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {int (* get_clock ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  sci; TYPE_2__* ops; } ;

/* Variables and functions */
 int SCI_CLK_ALLOW_FREQ_CHANGE ; 
 int SCI_CLK_INPUT_TERMINATION ; 
 int SCI_CLK_SSC_ENABLE ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 struct sci_clk* to_sci_clk (struct clk_hw*) ; 

__attribute__((used)) static int sci_clk_prepare(struct clk_hw *hw)
{
	struct sci_clk *clk = to_sci_clk(hw);
	bool enable_ssc = clk->flags & SCI_CLK_SSC_ENABLE;
	bool allow_freq_change = clk->flags & SCI_CLK_ALLOW_FREQ_CHANGE;
	bool input_termination = clk->flags & SCI_CLK_INPUT_TERMINATION;

	return clk->provider->ops->get_clock(clk->provider->sci, clk->dev_id,
					     clk->clk_id, enable_ssc,
					     allow_freq_change,
					     input_termination);
}