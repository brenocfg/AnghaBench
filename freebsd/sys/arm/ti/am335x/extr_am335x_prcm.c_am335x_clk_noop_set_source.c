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
struct ti_clock_dev {int dummy; } ;
typedef  int /*<<< orphan*/  clk_src_t ;

/* Variables and functions */

__attribute__((used)) static int
am335x_clk_noop_set_source(struct ti_clock_dev *clkdev, clk_src_t clksrc)
{

	return (0);
}