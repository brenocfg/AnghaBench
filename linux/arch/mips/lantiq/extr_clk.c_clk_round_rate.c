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
struct clk {unsigned long* rates; long rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_good (struct clk*) ; 
 scalar_t__ unlikely (int) ; 

long clk_round_rate(struct clk *clk, unsigned long rate)
{
	if (unlikely(!clk_good(clk)))
		return 0;
	if (clk->rates && *clk->rates) {
		unsigned long *r = clk->rates;

		while (*r && (*r != rate))
			r++;
		if (!*r) {
			return clk->rate;
		}
	}
	return rate;
}