#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* init; } ;
struct tegra_dfll {int /*<<< orphan*/  dfll_clk; TYPE_2__* dev; TYPE_4__ dfll_clk_hw; int /*<<< orphan*/  output_clock_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_register (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  clk_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 TYPE_1__ dfll_clk_init_data ; 
 int of_clk_add_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_src_simple_get ; 

__attribute__((used)) static int dfll_register_clk(struct tegra_dfll *td)
{
	int ret;

	dfll_clk_init_data.name = td->output_clock_name;
	td->dfll_clk_hw.init = &dfll_clk_init_data;

	td->dfll_clk = clk_register(td->dev, &td->dfll_clk_hw);
	if (IS_ERR(td->dfll_clk)) {
		dev_err(td->dev, "DFLL clock registration error\n");
		return -EINVAL;
	}

	ret = of_clk_add_provider(td->dev->of_node, of_clk_src_simple_get,
				  td->dfll_clk);
	if (ret) {
		dev_err(td->dev, "of_clk_add_provider() failed\n");

		clk_unregister(td->dfll_clk);
		return ret;
	}

	return 0;
}