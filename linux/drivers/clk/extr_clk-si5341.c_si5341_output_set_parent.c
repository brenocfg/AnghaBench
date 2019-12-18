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
typedef  scalar_t__ u8 ;
struct clk_si5341_output {TYPE_1__* data; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ num_synth; } ;

/* Variables and functions */
 int EINVAL ; 
 int si5341_output_reparent (struct clk_si5341_output*,scalar_t__) ; 
 struct clk_si5341_output* to_clk_si5341_output (struct clk_hw*) ; 

__attribute__((used)) static int si5341_output_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_si5341_output *output = to_clk_si5341_output(hw);

	if (index >= output->data->num_synth)
		return -EINVAL;

	return si5341_output_reparent(output, index);
}