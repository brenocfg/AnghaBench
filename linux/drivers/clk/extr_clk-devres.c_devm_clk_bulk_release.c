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
struct clk_bulk_devres {int /*<<< orphan*/  clks; int /*<<< orphan*/  num_clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_bulk_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devm_clk_bulk_release(struct device *dev, void *res)
{
	struct clk_bulk_devres *devres = res;

	clk_bulk_put(devres->num_clks, devres->clks);
}