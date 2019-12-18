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
struct scmi_clk {int /*<<< orphan*/  id; TYPE_2__* handle; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* clk_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct scmi_clk* to_scmi_clk (struct clk_hw*) ; 

__attribute__((used)) static void scmi_clk_disable(struct clk_hw *hw)
{
	struct scmi_clk *clk = to_scmi_clk(hw);

	clk->handle->clk_ops->disable(clk->handle, clk->id);
}