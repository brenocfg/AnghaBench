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
typedef  int /*<<< orphan*/  u8 ;
struct clk_hw {int dummy; } ;
struct cdce706_hw_data {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct cdce706_hw_data* to_hw_data (struct clk_hw*) ; 

__attribute__((used)) static int cdce706_clkin_set_parent(struct clk_hw *hw, u8 index)
{
	struct cdce706_hw_data *hwd = to_hw_data(hw);

	hwd->parent = index;
	return 0;
}