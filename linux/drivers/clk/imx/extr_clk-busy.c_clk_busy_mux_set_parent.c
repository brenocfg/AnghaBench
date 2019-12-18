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
typedef  int /*<<< orphan*/  u8 ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw; } ;
struct clk_busy_mux {int /*<<< orphan*/  shift; int /*<<< orphan*/  reg; TYPE_2__ mux; TYPE_1__* mux_ops; } ;
struct TYPE_3__ {int (* set_parent ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int clk_busy_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct clk_busy_mux* to_clk_busy_mux (struct clk_hw*) ; 

__attribute__((used)) static int clk_busy_mux_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_busy_mux *busy = to_clk_busy_mux(hw);
	int ret;

	ret = busy->mux_ops->set_parent(&busy->mux.hw, index);
	if (!ret)
		ret = clk_busy_wait(busy->reg, busy->shift);

	return ret;
}