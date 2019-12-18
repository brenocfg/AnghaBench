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
struct clk_lookup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct clk_lookup* clk_find (char const*,char const*) ; 
 int /*<<< orphan*/  clocks_mutex ; 
 int /*<<< orphan*/  devm_clk_match_clkdev ; 
 int /*<<< orphan*/  devm_clkdev_release ; 
 int devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk_lookup*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void devm_clk_release_clkdev(struct device *dev, const char *con_id,
			     const char *dev_id)
{
	struct clk_lookup *cl;
	int rval;

	mutex_lock(&clocks_mutex);
	cl = clk_find(dev_id, con_id);
	mutex_unlock(&clocks_mutex);

	WARN_ON(!cl);
	rval = devres_release(dev, devm_clkdev_release,
			      devm_clk_match_clkdev, cl);
	WARN_ON(rval);
}