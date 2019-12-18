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
struct clk_fixup_mux {TYPE_2__ mux; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_parent ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 struct clk_fixup_mux* to_clk_fixup_mux (struct clk_hw*) ; 

__attribute__((used)) static u8 clk_fixup_mux_get_parent(struct clk_hw *hw)
{
	struct clk_fixup_mux *fixup_mux = to_clk_fixup_mux(hw);

	return fixup_mux->ops->get_parent(&fixup_mux->mux.hw);
}