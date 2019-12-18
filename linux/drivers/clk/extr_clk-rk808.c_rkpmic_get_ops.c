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
struct clk_ops {int dummy; } ;

/* Variables and functions */
#define  RK809_ID 129 
#define  RK817_ID 128 
 struct clk_ops const rk808_clkout2_ops ; 
 struct clk_ops const rk817_clkout2_ops ; 

__attribute__((used)) static const struct clk_ops *rkpmic_get_ops(long variant)
{
	switch (variant) {
	case RK809_ID:
	case RK817_ID:
		return &rk817_clkout2_ops;
	/*
	 * For the default case, it match the following PMIC type.
	 * RK805_ID
	 * RK808_ID
	 * RK818_ID
	 */
	default:
		return &rk808_clkout2_ops;
	}
}