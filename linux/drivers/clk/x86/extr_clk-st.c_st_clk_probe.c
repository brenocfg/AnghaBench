#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct st_clk_data {scalar_t__ base; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ CLKDRVSTR2 ; 
 int /*<<< orphan*/  CLK_GATE_SET_TO_DISABLE ; 
 int EINVAL ; 
 scalar_t__ MISCCLKCNTL1 ; 
 int /*<<< orphan*/  OSCCLKENB ; 
 int /*<<< orphan*/  OSCOUT1CLK25MHZ ; 
 size_t ST_CLK_25M ; 
 size_t ST_CLK_48M ; 
 size_t ST_CLK_GATE ; 
 size_t ST_CLK_MUX ; 
 TYPE_1__* clk_hw_register_fixed_rate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* clk_hw_register_gate (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* clk_hw_register_mux (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_oscout1_parents ; 
 int /*<<< orphan*/  clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct st_clk_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_hw_register_clkdev (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__** hws ; 

__attribute__((used)) static int st_clk_probe(struct platform_device *pdev)
{
	struct st_clk_data *st_data;

	st_data = dev_get_platdata(&pdev->dev);
	if (!st_data || !st_data->base)
		return -EINVAL;

	hws[ST_CLK_48M] = clk_hw_register_fixed_rate(NULL, "clk48MHz", NULL, 0,
						     48000000);
	hws[ST_CLK_25M] = clk_hw_register_fixed_rate(NULL, "clk25MHz", NULL, 0,
						     25000000);

	hws[ST_CLK_MUX] = clk_hw_register_mux(NULL, "oscout1_mux",
		clk_oscout1_parents, ARRAY_SIZE(clk_oscout1_parents),
		0, st_data->base + CLKDRVSTR2, OSCOUT1CLK25MHZ, 3, 0, NULL);

	clk_set_parent(hws[ST_CLK_MUX]->clk, hws[ST_CLK_48M]->clk);

	hws[ST_CLK_GATE] = clk_hw_register_gate(NULL, "oscout1", "oscout1_mux",
		0, st_data->base + MISCCLKCNTL1, OSCCLKENB,
		CLK_GATE_SET_TO_DISABLE, NULL);

	devm_clk_hw_register_clkdev(&pdev->dev, hws[ST_CLK_GATE], "oscout1",
				    NULL);

	return 0;
}