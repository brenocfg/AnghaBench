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
 scalar_t__ IS_ERR (struct clk*) ; 
 struct clk* clk_get (struct device*,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

struct clk *s3c_cpufreq_clk_get(struct device *dev, const char *name)
{
	struct clk *clk;

	clk = clk_get(dev, name);
	if (IS_ERR(clk))
		pr_err("failed to get clock '%s'\n", name);

	return clk;
}