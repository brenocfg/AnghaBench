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
struct clk_onecell_data {unsigned int clk_num; int /*<<< orphan*/ * clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct clk_onecell_data*) ; 
 struct clk_onecell_data* kzalloc (int,int /*<<< orphan*/ ) ; 

struct clk_onecell_data *mtk_alloc_clk_data(unsigned int clk_num)
{
	int i;
	struct clk_onecell_data *clk_data;

	clk_data = kzalloc(sizeof(*clk_data), GFP_KERNEL);
	if (!clk_data)
		return NULL;

	clk_data->clks = kcalloc(clk_num, sizeof(*clk_data->clks), GFP_KERNEL);
	if (!clk_data->clks)
		goto err_out;

	clk_data->clk_num = clk_num;

	for (i = 0; i < clk_num; i++)
		clk_data->clks[i] = ERR_PTR(-ENOENT);

	return clk_data;
err_out:
	kfree(clk_data);

	return NULL;
}