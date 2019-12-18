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
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_sys (char*,int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_get (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  twd_clk ; 
 int /*<<< orphan*/  twd_timer_rate ; 

__attribute__((used)) static void twd_get_clock(struct device_node *np)
{
	int err;

	if (np)
		twd_clk = of_clk_get(np, 0);
	else
		twd_clk = clk_get_sys("smp_twd", NULL);

	if (IS_ERR(twd_clk)) {
		pr_err("smp_twd: clock not found %d\n", (int) PTR_ERR(twd_clk));
		return;
	}

	err = clk_prepare_enable(twd_clk);
	if (err) {
		pr_err("smp_twd: clock failed to prepare+enable: %d\n", err);
		clk_put(twd_clk);
		return;
	}

	twd_timer_rate = clk_get_rate(twd_clk);
}