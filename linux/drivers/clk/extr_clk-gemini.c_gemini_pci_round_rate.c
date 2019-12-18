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

__attribute__((used)) static long gemini_pci_round_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long *prate)
{
	/* We support 33 and 66 MHz */
	if (rate < 48000000)
		return 33000000;
	return 66000000;
}