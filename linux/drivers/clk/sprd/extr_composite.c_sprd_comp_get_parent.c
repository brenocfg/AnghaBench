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
struct sprd_comp {int /*<<< orphan*/  mux; int /*<<< orphan*/  common; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct sprd_comp* hw_to_sprd_comp (struct clk_hw*) ; 
 int /*<<< orphan*/  sprd_mux_helper_get_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 sprd_comp_get_parent(struct clk_hw *hw)
{
	struct sprd_comp *cc = hw_to_sprd_comp(hw);

	return sprd_mux_helper_get_parent(&cc->common, &cc->mux);
}