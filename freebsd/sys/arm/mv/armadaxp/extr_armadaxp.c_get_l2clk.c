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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ count_l2clk () ; 

uint32_t
get_l2clk(void)
{
	static uint32_t	l2clk_freq = 0;

	/* If get_l2clk is called first time get L2CLK value from register */
	if (l2clk_freq == 0)
		l2clk_freq = count_l2clk();

	return (l2clk_freq);
}