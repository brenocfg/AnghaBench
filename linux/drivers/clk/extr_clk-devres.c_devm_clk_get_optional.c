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
 int /*<<< orphan*/  ENOENT ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct clk* devm_clk_get (struct device*,char const*) ; 

struct clk *devm_clk_get_optional(struct device *dev, const char *id)
{
	struct clk *clk = devm_clk_get(dev, id);

	if (clk == ERR_PTR(-ENOENT))
		return NULL;

	return clk;
}