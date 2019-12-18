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
struct clk {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 scalar_t__ clk_disable_unprepare ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*) ; 
 int devm_add_action_or_reset (struct device*,void (*) (void*),struct clk*) ; 
 struct clk* devm_clk_get (struct device*,char*) ; 

__attribute__((used)) static int devm_clk_get_enable(struct device *dev, char *id)
{
	struct clk *clk;
	int ret;

	clk = devm_clk_get(dev, id);
	if (IS_ERR(clk)) {
		ret = PTR_ERR(clk);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get %s", id);
		return ret;
	}

	ret = clk_prepare_enable(clk);
	if (ret) {
		dev_err(dev, "failed to enable %s", id);
		return ret;
	}

	ret = devm_add_action_or_reset(dev,
				       (void(*)(void *))clk_disable_unprepare,
				       clk);
	if (ret) {
		dev_err(dev, "failed to add reset action on %s", id);
		return ret;
	}

	return 0;
}