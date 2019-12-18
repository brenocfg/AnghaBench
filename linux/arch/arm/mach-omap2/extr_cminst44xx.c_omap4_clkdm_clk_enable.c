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
struct clockdomain {int flags; } ;

/* Variables and functions */
 int CLKDM_CAN_FORCE_WAKEUP ; 
 int omap4_clkdm_wakeup (struct clockdomain*) ; 

__attribute__((used)) static int omap4_clkdm_clk_enable(struct clockdomain *clkdm)
{
	if (clkdm->flags & CLKDM_CAN_FORCE_WAKEUP)
		return omap4_clkdm_wakeup(clkdm);

	return 0;
}