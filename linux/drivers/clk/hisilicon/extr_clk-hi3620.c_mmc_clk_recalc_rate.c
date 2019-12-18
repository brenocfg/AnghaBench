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
struct clk_hw {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long mmc_clk_recalc_rate(struct clk_hw *hw,
		       unsigned long parent_rate)
{
	switch (parent_rate) {
	case 26000000:
		return 13000000;
	case 180000000:
		return 25000000;
	case 360000000:
		return 50000000;
	case 720000000:
		return 100000000;
	case 1440000000:
		return 180000000;
	default:
		return parent_rate;
	}
}