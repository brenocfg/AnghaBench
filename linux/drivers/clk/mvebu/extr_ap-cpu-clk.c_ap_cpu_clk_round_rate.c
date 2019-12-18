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
 int /*<<< orphan*/  APN806_MAX_DIVIDER ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ap_cpu_clk_round_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long *parent_rate)
{
	int divider = *parent_rate / rate;

	divider = min(divider, APN806_MAX_DIVIDER);

	return *parent_rate / divider;
}