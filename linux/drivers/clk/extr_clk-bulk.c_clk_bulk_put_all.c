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
struct clk_bulk_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct clk_bulk_data*) ; 
 int /*<<< orphan*/  clk_bulk_put (int,struct clk_bulk_data*) ; 
 int /*<<< orphan*/  kfree (struct clk_bulk_data*) ; 

void clk_bulk_put_all(int num_clks, struct clk_bulk_data *clks)
{
	if (IS_ERR_OR_NULL(clks))
		return;

	clk_bulk_put(num_clks, clks);

	kfree(clks);
}