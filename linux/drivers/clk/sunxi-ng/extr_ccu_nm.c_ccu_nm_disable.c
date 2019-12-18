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
struct clk_hw {int dummy; } ;
struct ccu_nm {int /*<<< orphan*/  enable; int /*<<< orphan*/  common; } ;

/* Variables and functions */
 void ccu_gate_helper_disable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ccu_nm* hw_to_ccu_nm (struct clk_hw*) ; 

__attribute__((used)) static void ccu_nm_disable(struct clk_hw *hw)
{
	struct ccu_nm *nm = hw_to_ccu_nm(hw);

	return ccu_gate_helper_disable(&nm->common, nm->enable);
}