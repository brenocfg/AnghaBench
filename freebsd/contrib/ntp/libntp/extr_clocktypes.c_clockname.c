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
struct clktype {int code; char const* abbrev; } ;

/* Variables and functions */
 struct clktype* clktypes ; 

const char *
clockname(
	int num
	)
{
	register struct clktype *clk;
  
	for (clk = clktypes; clk->code != -1; clk++) {
		if (num == clk->code)
			return (clk->abbrev);
	}
	return (NULL);
}