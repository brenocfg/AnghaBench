#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct of_phandle_args {unsigned int* args; } ;
struct clk_hw {int dummy; } ;
struct clk_si5341 {unsigned int num_outputs; unsigned int num_synth; TYPE_3__* i2c_client; struct clk_hw hw; TYPE_2__* synth; TYPE_1__* clk; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct clk_hw hw; } ;
struct TYPE_4__ {struct clk_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct clk_hw* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 

__attribute__((used)) static struct clk_hw *
of_clk_si5341_get(struct of_phandle_args *clkspec, void *_data)
{
	struct clk_si5341 *data = _data;
	unsigned int idx = clkspec->args[1];
	unsigned int group = clkspec->args[0];

	switch (group) {
	case 0:
		if (idx >= data->num_outputs) {
			dev_err(&data->i2c_client->dev,
				"invalid output index %u\n", idx);
			return ERR_PTR(-EINVAL);
		}
		return &data->clk[idx].hw;
	case 1:
		if (idx >= data->num_synth) {
			dev_err(&data->i2c_client->dev,
				"invalid synthesizer index %u\n", idx);
			return ERR_PTR(-EINVAL);
		}
		return &data->synth[idx].hw;
	case 2:
		if (idx > 0) {
			dev_err(&data->i2c_client->dev,
				"invalid PLL index %u\n", idx);
			return ERR_PTR(-EINVAL);
		}
		return &data->hw;
	default:
		dev_err(&data->i2c_client->dev, "invalid group %u\n", group);
		return ERR_PTR(-EINVAL);
	}
}