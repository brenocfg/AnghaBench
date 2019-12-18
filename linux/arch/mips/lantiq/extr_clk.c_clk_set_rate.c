#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  con_id; int /*<<< orphan*/  dev_id; } ;
struct clk {unsigned long* rates; unsigned long rate; TYPE_1__ cl; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_good (struct clk*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	if (unlikely(!clk_good(clk)))
		return 0;
	if (clk->rates && *clk->rates) {
		unsigned long *r = clk->rates;

		while (*r && (*r != rate))
			r++;
		if (!*r) {
			pr_err("clk %s.%s: trying to set invalid rate %ld\n",
				clk->cl.dev_id, clk->cl.con_id, rate);
			return -1;
		}
	}
	clk->rate = rate;
	return 0;
}