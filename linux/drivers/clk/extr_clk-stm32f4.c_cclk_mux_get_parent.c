#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_parent ) (struct clk_hw*) ;} ;

/* Variables and functions */
 TYPE_1__ clk_mux_ops ; 
 int /*<<< orphan*/  stub1 (struct clk_hw*) ; 

__attribute__((used)) static u8 cclk_mux_get_parent(struct clk_hw *hw)
{
	return clk_mux_ops.get_parent(hw);
}