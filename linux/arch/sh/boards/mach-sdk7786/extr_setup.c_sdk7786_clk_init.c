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
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  MODE_PIN9 ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int clk_register (int /*<<< orphan*/ *) ; 
 int clk_set_rate (struct clk*,int) ; 
 int /*<<< orphan*/  clkdev_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sdk7786_pcie_cl ; 
 int /*<<< orphan*/  sdk7786_pcie_clk ; 
 scalar_t__ test_mode_pin (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sdk7786_clk_init(void)
{
	struct clk *clk;
	int ret;

	/*
	 * Only handle the EXTAL case, anyone interfacing a crystal
	 * resonator will need to provide their own input clock.
	 */
	if (test_mode_pin(MODE_PIN9))
		return -EINVAL;

	clk = clk_get(NULL, "extal");
	if (IS_ERR(clk))
		return PTR_ERR(clk);
	ret = clk_set_rate(clk, 33333333);
	clk_put(clk);

	/*
	 * Setup the FPGA clocks.
	 */
	ret = clk_register(&sdk7786_pcie_clk);
	if (unlikely(ret)) {
		pr_err("FPGA clock registration failed\n");
		return ret;
	}

	clkdev_add(&sdk7786_pcie_cl);

	return 0;
}