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
 unsigned long ACSR ; 
 unsigned long* hss_mult ; 
 scalar_t__ pxa3xx_is_ring_osc_forced () ; 

__attribute__((used)) static unsigned long clk_pxa3xx_system_bus_get_rate(struct clk_hw *hw,
					    unsigned long parent_rate)
{
	unsigned long acsr = ACSR;
	unsigned int hss = (acsr >> 14) & 0x3;

	if (pxa3xx_is_ring_osc_forced())
		return parent_rate;
	return parent_rate / 48 * hss_mult[hss];
}