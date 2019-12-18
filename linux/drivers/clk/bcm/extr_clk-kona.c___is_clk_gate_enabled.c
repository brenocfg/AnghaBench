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
typedef  int u32 ;
struct ccu_data {int dummy; } ;
struct bcm_clk_gate {int status_bit; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int __ccu_read (struct ccu_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gate_exists (struct bcm_clk_gate*) ; 

__attribute__((used)) static bool
__is_clk_gate_enabled(struct ccu_data *ccu, struct bcm_clk_gate *gate)
{
	u32 bit_mask;
	u32 reg_val;

	/* If there is no gate we can assume it's enabled. */
	if (!gate_exists(gate))
		return true;

	bit_mask = 1 << gate->status_bit;
	reg_val = __ccu_read(ccu, gate->offset);

	return (reg_val & bit_mask) != 0;
}