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
struct scpi_clk_data {unsigned int clk_num; struct scpi_clk** clk; } ;
struct clk_hw {int dummy; } ;
struct scpi_clk {unsigned int id; struct clk_hw hw; } ;
struct of_phandle_args {unsigned int* args; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct clk_hw* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk_hw *
scpi_of_clk_src_get(struct of_phandle_args *clkspec, void *data)
{
	struct scpi_clk *sclk;
	struct scpi_clk_data *clk_data = data;
	unsigned int idx = clkspec->args[0], count;

	for (count = 0; count < clk_data->clk_num; count++) {
		sclk = clk_data->clk[count];
		if (idx == sclk->id)
			return &sclk->hw;
	}

	return ERR_PTR(-EINVAL);
}