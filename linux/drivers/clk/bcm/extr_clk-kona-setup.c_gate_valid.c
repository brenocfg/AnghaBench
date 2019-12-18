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
struct bcm_clk_gate {int /*<<< orphan*/  hw_sw_sel_bit; int /*<<< orphan*/  en_bit; int /*<<< orphan*/  status_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bit_posn_valid (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ gate_is_hw_controllable (struct bcm_clk_gate*) ; 
 scalar_t__ gate_is_sw_controllable (struct bcm_clk_gate*) ; 

__attribute__((used)) static bool gate_valid(struct bcm_clk_gate *gate, const char *field_name,
			const char *clock_name)
{
	if (!bit_posn_valid(gate->status_bit, "gate status", clock_name))
		return false;

	if (gate_is_sw_controllable(gate)) {
		if (!bit_posn_valid(gate->en_bit, "gate enable", clock_name))
			return false;

		if (gate_is_hw_controllable(gate)) {
			if (!bit_posn_valid(gate->hw_sw_sel_bit,
						"gate hw/sw select",
						clock_name))
				return false;
		}
	} else {
		BUG_ON(!gate_is_hw_controllable(gate));
	}

	return true;
}