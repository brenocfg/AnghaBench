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
struct device {int dummy; } ;
struct clk_bulk_data {int /*<<< orphan*/  id; int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_bulk_put (int,struct clk_bulk_data*) ; 
 int /*<<< orphan*/ * clk_get (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __clk_bulk_get(struct device *dev, int num_clks,
			  struct clk_bulk_data *clks, bool optional)
{
	int ret;
	int i;

	for (i = 0; i < num_clks; i++)
		clks[i].clk = NULL;

	for (i = 0; i < num_clks; i++) {
		clks[i].clk = clk_get(dev, clks[i].id);
		if (IS_ERR(clks[i].clk)) {
			ret = PTR_ERR(clks[i].clk);
			clks[i].clk = NULL;

			if (ret == -ENOENT && optional)
				continue;

			if (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to get clk '%s': %d\n",
					clks[i].id, ret);
			goto err;
		}
	}

	return 0;

err:
	clk_bulk_put(i, clks);

	return ret;
}